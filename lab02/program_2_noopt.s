; program_2_noopt.s
; Performing some computations on FP values (no optimizations)

; Used registers:
; - r1: target value for the loop
; - r2: loop accumulator
; - f1, f2, f3, f4: temporary storage for operands from v1, v2, v3, v4
; - f5, f6, f7: temporary storage for the results of mul, div and add

; Algorithm:
; - Load the registers f1, f2, f3, f4 with values from v1, v2, v3, v4
; - Perform the required operations saving the results in f5, f6, f7
; - Store the values of f5, f6, f7 into v5, v6, v7
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

v3:     .double 64.4318, 20.7742, 31.1102, 59.4896,  8.5516, 96.3089,  3.7739, 10.6762,  3.0541, 18.2922
        .double 37.8609, 30.1246, 92.3380, 26.2212, 26.2482, 54.6806, 88.5168, 65.3757, 74.4074, 23.9932
        .double 81.1580, 47.0923, 43.0207, 60.2843, 80.1015, 52.1136, 91.3287, 49.4174, 50.0022, 88.6512

v4:     .double  5.9619, 65.9605, 17.3389, 29.1984, 95.1630, 30.1455,  3.2601, 64.4765, 25.1806, 90.6308
        .double 68.1972, 51.8595, 39.0938, 43.1651, 92.0332, 70.1099, 56.1200, 37.6272, 29.0441, 87.9654
        .double  4.2431, 97.2975, 83.1380,  1.5487,  5.2677, 66.6339, 88.1867, 19.0924, 61.7091, 81.7761

v5:     .space 240
v6:     .space 240
v7:     .space 240

        .text

main:   daddui  r1, r0, 240             ; load r1
        daddui  r2, r0, 0               ; load r2

loop:   l.d     f1, v1(r2)              ; load f1
        l.d     f2, v2(r2)              ; load f2
        l.d     f3, v3(r2)              ; load f3
        l.d     f4, v4(r2)              ; load f4

        mul.d   f5, f1, f2              ; f5 = f1 * f2
        div.d   f6, f2, f3              ; f6 = f2 / f3
        add.d   f7, f1, f4              ; f7 = f1 + f4

        s.d     f5, v5(r2)              ; store f5
        s.d     f6, v6(r2)              ; store f6
        s.d     f7, v7(r2)              ; store f7

        daddui  r2, r2, 8               ; increment r2
        bne     r1, r2, loop            ; loop if r1 != r2

        halt