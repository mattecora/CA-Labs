; program_2.s
; Performing some computations on FP values with data dependencies

; Used registers:
; - r1: target value for the loop
; - r2: loop accumulator
; - f1, f2: temporary storage for operands from v1, v2
; - f3, f4, f5: temporary storage for the results of mul, div and add

; Algorithm:
; - Load the registers f1, f2 with values from v1, v2
; - Perform the required operations saving the results in f3, f4, f5
; - Store the values of f3, f4, f5 into v3, v4, v5
; - Loop for 30 times

; Optimizations:
; - No optimizations

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
        daddi   r2, r0, 0               ; load r2

loop:   l.d     f1, v1(r2)              ; load f1
        l.d     f2, v2(r2)              ; load f2

        mul.d   f3, f1, f2              ; f3 = f1 * f2
        div.d   f4, f3, f2              ; f4 = f3 / f2
        add.d   f5, f4, f2              ; f5 = f4 + f2

        s.d     f3, v3(r2)              ; store f3
        s.d     f4, v4(r2)              ; store f4
        s.d     f5, v5(r2)              ; store f5

        daddi   r2, r2, 8               ; increment r2
        bne     r1, r2, loop            ; loop if r1 != r2

        halt

; 966 cycles, 1140 RAW, 60 struct