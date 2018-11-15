# path to the gem5 folder
gem5_folder="gem5"

export PYTHONPATH=$PYTHONPATH:$gem5_folder
export PYTHONPATH=$PYTHONPATH:$gem5_folder/configs/common
export PYTHONPATH=$PYTHONPATH:$gem5_folder/configs
export PYTHONPATH=$PYTHONPATH:$gem5_folder/src/python
export PYTHONPATH=$PYTHONPATH:$gem5_folder/src/python/m5
export PYTHONPATH=$PYTHONPATH:$gem5_folder/src/sim

# set configuration
config=$2
predictor=$3

# run gem5
$gem5_folder/build/ALPHA/gem5.opt mygem5script.py --my-config=$config --my-bpred=$predictor -c $1

# ticks
ticks=$(cat m5out/stats.txt | grep "sim_ticks " | tr -s " " | cut -f 2 -d\ )

# clock domain
cdom=$(cat m5out/stats.txt | grep "system.cpu_clk_domain.clock " | tr -s " " | cut -f 2 -d\ )

# clock cycles
ccyc=$(cat m5out/stats.txt | grep "system.cpu.numCycles " | tr -s " " | cut -f 2 -d\ )

# simulated instructions
simins=$(cat m5out/stats.txt | grep "sim_insts " | tr -s " " | cut -f 2 -d\ )

# cpi
cpi=$(cat m5out/stats.txt | grep "system.cpu.cpi " | tr -s " " | cut -f 2 -d\ )

# committed instructions
comins=$(cat m5out/stats.txt | grep "system.cpu.committedInsts " | tr -s " " | cut -f 2 -d\ )

# host seconds
hsec=$(cat m5out/stats.txt | grep "host_seconds " | tr -s " " | cut -f 2 -d\ )

# misprediction ratio
bpred=$(cat m5out/stats.txt | grep "system.cpu.branchPred.condPredicted " | tr -s " " | cut -f 2 -d\ )
bpinc=$(cat m5out/stats.txt | grep "system.cpu.branchPred.condIncorrect " | tr -s " " | cut -f 2 -d\ )
bmratio=$(echo "scale=5; $bpinc/$bpred*100" | bc -l)

# btb hits
btb=$(cat m5out/stats.txt | grep "system.cpu.branchPred.BTBHits " | tr -s " " | cut -f 2 -d\ )

# show stats
echo ""
echo "Configuration:            $config"
echo "Branch predictor:         $predictor"
echo "Ticks:                    $ticks"
echo "Clock domain:             $cdom"
echo "Clock cycles:             $ccyc"
echo "Simulated instructions:   $simins"
echo "CPI:                      $cpi"
echo "Committed instructions:   $comins"
echo "Host seconds:             $hsec"
echo "Misprediction ratio:      $bmratio"
echo "BTB hits:                 $btb"