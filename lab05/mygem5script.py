"""

This script executes a program with gem5's system call emulation mode.

Basic usage:
    path/to/gem5.opt ./this-script.py -c ./path/to/executable 
            --directory=output-directory

The output for the simulation is placed in output-directory including these files:
    config.ini, config.json --- system configuration 

    program.out, program.err --- the output of the executable program

    stats.txt --- statistics from the simulation
The default output directory is m5out.

To modify the cpu parameters, you can edit the create_cpu() function below to 
change the configurations of its CPUs. 

"""

# Generic python libraries
import optparse
import os
import os.path
import sys

# Interface to m5 simulation, implementing in gem5/src
import m5
from m5.defines import buildEnv
from m5.objects import *
from m5.util import addToPath, fatal

# Utilities included with m5 for configuring common simulations
# from gem5/configs/common
import Options
import Simulation
from Caches import *
import MemConfig

# My values
configs = {
    "basic": {
        "fetchWidth": 2,
        "decodeWidth": 2,
        "renameWidth": 2,
        "dispatchWidth": 2,
        "wbWidth": 2,
        "commitWidth": 2
    },
    "x2": {
        "fetchWidth": 4,
        "decodeWidth": 4,
        "renameWidth": 4,
        "dispatchWidth": 4,
        "wbWidth": 4,
        "commitWidth": 4
    },
    "x4": {
        "fetchWidth": 8,
        "decodeWidth": 8,
        "renameWidth": 8,
        "dispatchWidth": 8,
        "wbWidth": 8,
        "commitWidth": 8
    },
    "custom": {
        "fetchWidth": 8,
        "decodeWidth": 8,
        "renameWidth": 8,
        "dispatchWidth": 8,
        "wbWidth": 8,
        "commitWidth": 8
    }
}

def eprint(*args):
    sys.stderr.write("".join(args))
    sys.stderr.write("\n")

def main(options):
    process = create_process(options)
    run_one_simulation(options, process, options.my_config, options.my_bpred)

def create_cpu(options, cpu_id, config, bpred):
    # DerivO3CPU is the configurable out-of-order CPU model supplied by gem5
    the_cpu = DerivO3CPU(cpu_id=cpu_id)
    icache = L1_ICache(size=options.l1i_size, assoc=options.l1i_assoc)
    dcache = L1_DCache(size=options.l1d_size, assoc=options.l1d_assoc)
    
    # ****************************
    # CHANGE HERE THE CPU CONFIGURATION PARAMETERS
    # ****************************

    # ****************************
    # - FETCH STAGE
    # ****************************
    the_cpu.fetchWidth = config["fetchWidth"]
    the_cpu.fetchBufferSize = 8
    the_cpu.fetchQueueSize = 8

    # ****************************
    # - DECODE STAGE
    # ****************************
    the_cpu.decodeWidth = config["decodeWidth"]
    
    # ****************************
    # - RENAME STAGE
    # ****************************
    the_cpu.numIQEntries = 4 
    the_cpu.numROBEntries = 4 
    the_cpu.renameWidth = config["renameWidth"]

    # ****************************
    # - DISPATCH/ISSUE STAGE 
    # ****************************
    the_cpu.dispatchWidth = config["dispatchWidth"]
    the_cpu.issueWidth = 2
    the_cpu.LQEntries = 8
    the_cpu.SQEntries = 8

    # ****************************
    # - EXECUTE STAGE 
    # ****************************

    # ****************************
    # -- BPU SELECTION
    # ****************************
    
    if bpred == "LocalBP":
        my_predictor = LocalBP()
        my_predictor.localPredictorSize = 32
        my_predictor.BTBEntries = 256
        the_cpu.branchPred = my_predictor
    elif bpred == "TournamentBP":
        my_predictor = TournamentBP()
        my_predictor.localPredictorSize = 32
        my_predictor.localHistoryTableSize = 256
        my_predictor.globalPredictorSize = 64
        my_predictor.choicePredictorSize = 64
        my_predictor.BTBEntries = 256
        the_cpu.branchPred = my_predictor
    elif bpred == "BiModeBP":
        my_predictor = BiModeBP()
        my_predictor.globalPredictorSize = 64
        my_predictor.choicePredictorSize = 64
        my_predictor.BTBEntries = 256
        the_cpu.branchPred = my_predictor

    # ********************************
    # -- FUNTIONAL UNITS DEFINITION  
    # ********************************

    class MyInt_ALU(IntALU): # 1 integer unit, default latency 1cc 
        count = 1
    class MyFP_ALU(FP_ALU): # it contains 3 different FP units with different latencies (opLat)
        opList = [ OpDesc(opClass='FloatAdd', opLat=10),
               OpDesc(opClass='FloatCmp', opLat=10),
               OpDesc(opClass='FloatCvt', opLat=10) ]
        count = 1
    class MyFP_MultDiv(FP_MultDiv): # it contains 3 different FP units with different latencies 
        opList = [ OpDesc(opClass='FloatMult', opLat=14),
               OpDesc(opClass='FloatDiv', opLat=24, pipelined=False),
               OpDesc(opClass='FloatSqrt', opLat=48, pipelined=False) ]
        count = 1
    class MyFunctionalUnits(FUPool):
        FUList = [
            MyInt_ALU(), IntMultDiv(), MyFP_ALU(), MyFP_MultDiv(),
            SIMD_Unit(), RdWrPort(), IprPort(),
        ]

    the_cpu.fuPool = MyFunctionalUnits()

    # ****************************
    # - WRITE STAGE  
    # ****************************
    the_cpu.wbWidth = config["wbWidth"]
    
    # ****************************
    # - COMMIT STAGE  
    # ****************************
    the_cpu.commitWidth = config["commitWidth"]
    the_cpu.squashWidth =  2
    
    the_cpu[cpu_id].addPrivateSplitL1Caches(icache, dcache, None, None)
    the_cpu[cpu_id].createInterruptController()
    return the_cpu

def create_process(options):
    # process = LiveProcess()
    process = Process()
    process.executable = os.path.realpath(options.cmd)
    if options.options != "":
        process.cmd = [options.cmd] + options.options.split()
    else:
        process.cmd = [options.cmd]

    if options.input != "":
        process.input = options.input
    if options.output != "":
        process.output = options.output
    if options.errout != "":
        process.errout = options.errout
    
    return process

def run_one_simulation(options, process, config_name, bpred_name):
    the_dir = os.path.join(options.directory)
    if not os.path.exists(the_dir):
        os.makedirs(the_dir)
    pid = os.fork()
    if pid == 0:
        # in child
        os.chdir(the_dir)
        run_system_with_cpu(process, options, os.path.realpath("."),
            real_cpu_create_function=lambda cpu_id: create_cpu(options, cpu_id, configs[config_name], bpred_name)
        )
        sys.exit(0)
    else:
        # in parent
        exited_pid, exit_status = os.waitpid(pid, 0)
        # Check whether child reached exit(0)
        if os.WIFEXITED(exit_status) and os.WEXITSTATUS(exit_status) != 0:
            eprint("Child did not exit normally")

def run_system_with_cpu(
        process, options, output_dir,
        warmup_cpu_class=None,
        warmup_instructions=0,
        real_cpu_create_function=lambda cpu_id: DerivO3CPU(cpu_id=cpu_id)):
    # Override the -d outdir --outdir option to gem5
    m5.options.outdir = output_dir
    m5.core.setOutputDir(m5.options.outdir)

    m5.stats.reset()

    max_tick = options.abs_max_tick
    if options.rel_max_tick:
        max_tick = options.rel_max_tick
    elif options.maxtime:
        max_tick = int(options.maxtime * 1000 * 1000 * 1000 * 1000)

    eprint("Simulating until tick=%s" %  (max_tick))

    real_cpus = [real_cpu_create_function(0)]
    mem_mode = real_cpus[0].memory_mode()

    if warmup_cpu_class:
        warmup_cpus = [warmup_cpu_class(cpu_id=0)]
        warmup_cpus[0].max_insts_any_thread = warmup_instructions
    else:
        warmup_cpus = real_cpus

    system = System(cpu = warmup_cpus,
                    mem_mode = mem_mode,
                    mem_ranges = [AddrRange(options.mem_size)],
                    cache_line_size = options.cacheline_size)
    system.multi_thread = False
    system.voltage_domain = VoltageDomain(voltage = options.sys_voltage)
    system.clk_domain = SrcClockDomain(clock =  options.sys_clock,
                                       voltage_domain = system.voltage_domain)
    system.cpu_voltage_domain = VoltageDomain()
    system.cpu_clk_domain = SrcClockDomain(clock = options.cpu_clock,
                                           voltage_domain =
                                           system.cpu_voltage_domain)
    system.cache_line_size = options.cacheline_size
    if warmup_cpu_class:
        for cpu in real_cpus:
            cpu.clk_domain = system.cpu_clk_domain
            cpu.workload = process
            cpu.system = system
            cpu.switched_out = True
            cpu.createThreads()
        system.switch_cpus = real_cpus

    for cpu in system.cpu:
        cpu.clk_domain = system.cpu_clk_domain
        cpu.workload = process
        if options.prog_interval:
            cpu.progress_interval = options.prog_interval
        cpu.createThreads()

    MemClass = Simulation.setMemClass(options)
    system.membus = SystemXBar()
    system.system_port = system.membus.slave
    system.cpu[0].connectAllPorts(system.membus)
    MemConfig.config_mem(options, system)
    root = Root(full_system = False, system = system)

    m5.options.outdir = output_dir
    m5.instantiate(None) # None == no checkpoint
    if warmup_cpu_class:
        eprint("Running warmup with warmup CPU class (%d instrs.)" % (warmup_instructions))
    eprint("Starting simulation")
    exit_event = m5.simulate(max_tick)
    if warmup_cpu_class:
        max_tick -= m5.curTick()
        m5.stats.reset()
        debug_print("Finished warmup; running real simulation")
        m5.switchCpus(system, real_cpus)
        exit_event = m5.simulate(max_tick)
    eprint("Done simulation @ tick = %s: %s" % (m5.curTick(), exit_event.getCause()))
    m5.stats.dump()

def get_options():
    parser = optparse.OptionParser()
    Options.addCommonOptions(parser)
    Options.addSEOptions(parser)

    # base output directory to use.
    # This takes precedence over gem5's built-in outdir option
    parser.add_option("--directory", type="str", default="m5out")

    # Set the configuration to run
    parser.add_option("--my-config", type="str", default="basic")

    # Set the branch predictor to use
    parser.add_option("--my-bpred", type="str", default="LocalBP")

    parser.set_defaults(
        # output='./program.out',
        # errout='./program.err',
        cpu_type='DerivO3CPU',
        mem_size=64 * 1024 * 1024,
        caches = True
    )

    (options, args) = parser.parse_args()

    if not options.directory:
        eprint("You must set --directory to the name of an output directory to create")
        sys.exit(1)

    # Some features are not supported by this script, but are added to parser by
    # Options.addSEOptions and Options.addCommonOptions

    # I check for these here to avoid confusion
    # If you are failing an assertion here, removing the assertion will not make the option work.
    assert(not options.smt)
    assert(options.num_cpus == 1)
    # assert(not options.fastmem)
    assert(not options.standard_switch)
    assert(not options.repeat_switch)
    assert(not options.take_checkpoints)
    assert(not options.fast_forward)
    assert(not options.maxinsts)
    assert(not options.l2cache)

    if args:
        print ("Error: script doesn't take any positional X XXX XXX arguments")
        sys.exit(1)

    return options

main(get_options())
