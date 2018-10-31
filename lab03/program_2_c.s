; program_2_c.s
; Performing some computations on FP values with data dependencies

; Used registers:
; - r1, r2, r3: loop accumulators (starting from the end)
; - f1, f2, f6, f7, f11, f12: temporary storage for operands from v1, v2
; - f3, f4, f5, f8, f9, f10, f13, f14, f15: temporary storage for the results of mul, div and add

; Algorithm:
; - Load the registers f1, f2, f6, f7, f11, f12 with values from v1, v2
; - Perform the required operations saving the results in f3, f4, f5, f8, f9, f10, f13, f14, f15
; - Store the values of f3, f4, f5, f8, f9, f10, f13, f14, f15 into v3, v4, v5
; - Loop for 10 times

; Optimizations:
; - Loop from the end
; - Loop unrolled 3 times
; - Reorganization of instructions related to different iterations

        .data

v1:     .double 81.4724, 15.7613, 65.5741, 70.6046, 43.8744, 27.6025, 75.1267, 84.0717, 35.1660,  7.5854
        .double 90.5792, 97.0593,  3.5712,  3.1833, 38.1558, 67.9703, 25.5095, 25.4282, 83.0829,  5.3950
        .double 12.6987, 95.7167, 84.9129, 27.6923, 76.5517, 65.5098, 50.5957, 81.4285, 58.5264, 53.0798

v2:     .double 16.2182, 45.0542, 10.6653, 43.1414, 85.3031, 41.7267, 78.0252, 23.4780, 54.7009, 92.9386
        .double 79.4285,  8.3821, 96.1898, 91.0648, 62.2055,  4.9654, 38.9739, 35.3159, 29.6321, 77.5713
        .double 31.1215, 22.8977,  0.4634, 18.1847, 35.0952, 90.2716, 24.1691, 82.1194, 74.4693, 48.6792

v3:     .space 240
v4:     .space 240
v5:     .space 240

        .text

main:   daddi   r1, r0, 240             ; load r1
        daddi   r2, r0, 248             ; load r2
        daddi   r3, r0, 256             ; load r3

loop:   daddi   r1, r1, -24             ; r1 update
        
        l.d     f1, v1(r1)              ; load f1
        l.d     f2, v2(r1)              ; load f2

        daddi   r2, r2, -24             ; r2 update
        mul.d   f3, f1, f2              ; f3 = f1 * f2
        
        l.d     f6, v1(r2)              ; load f6
        l.d     f7, v2(r2)              ; load f7

        daddi   r3, r3, -24             ; r3 update
        mul.d   f8, f6, f7              ; f8 = f6 * f7

        l.d     f11, v1(r3)             ; load f11
        l.d     f12, v2(r3)             ; load f12

        mul.d   f13, f11, f12           ; f13 = f11 * f12 (RAW)
        
        div.d   f4, f3, f2              ; f4 = f3 / f2
        s.d     f3, v3(r1)              ; store f3

        div.d   f9, f8, f7              ; f9 = f8 / f7
        s.d     f8, v3(r2)              ; store f8
        add.d   f5, f4, f2              ; f5 = f4 + f2
        s.d     f4, v4(r1)              ; store f4

        div.d   f14, f13, f12           ; f14 = f13 / f12
        s.d     f13, v3(r3)             ; store f13
        add.d   f10, f9, f7             ; f10 = f9 + f7
        s.d     f9, v4(r2)              ; store f9
        
        s.d     f5, v5(r1)              ; store f5
        add.d   f15, f14, f17           ; f15 = f14 + f12
        s.d     f10, v5(r2)             ; store f10
        
        s.d     f14, v4(r3)             ; store f14
        s.d     f15, v5(r3)             ; store f15
        
        bnez    r1, loop                ; loop if r1 != r2

        halt

; standard: 557 cycles, 140 RAW, 200 struct
; branch delay: 538 cycles, 130 RAW, 200 struct