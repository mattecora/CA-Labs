; program_1.s
; Find the maximum in a vector of 100 elements

; Used registers:
; - r1 for saving temporary values read from the memory
; - r2 for indexing the vector
; - r3 for loop-end comparison
; - r4 for storing the current max
; - r5 for the result of the comparison r1-r4

; Algorithm:
; - The maximum is initialized at the smallest number that fits in a 64-bits register (2's complement format)
; - The maximum is compared with a value from the vector, setting a register if lower
; - If the register value is set, the maximum is updated

        .data

vector: .word   18,     0,      93,     82,     7,      -97,    -64,    38,     -21,    -4
        .word   70,     10,     96,     29,     3,      -100,   -14,    -97,    -92,    85
        .word   3,      -52,    -35,    72,     70,     -23,    -67,    -37,    -31,    80
        .word   74,     -10,    4,      -33     59,     61,     -51,    1,      -60,    -69
        .word   66,     17,     88,     -84,    25,     83,     88,     94,     -48,    -37
        .word   18,     8,      50,     -79,    96,     84,     -65,    -94,    87,     -68
        .word   -83,    -65,    90,     30,     -28,    61,     66,     31,     21,     86
        .word   57,     9,      18,     35,     -93,    -49,    -92,    -39,    86,     -21
        .word   66,     -67,    28,     97,     -49,    -24,    31,     -19,    -50,    73
        .word   -14,    -57,    54,     86,     90,     -55,    -30,    24,     36,     93
result: .space  8

        .text

main:   daddi   r2, r0, 0                       ; r2 = 0
        daddi   r3, r0, 800                     ; r3 = 800
        daddi   r4, r0, 0xffffffffffffffff      ; r4 = int_min

loop:   ld      r1, vector(r2)                  ; r1 = mem[vector + r2]
        
        slt     r5, r4, r1                      ; set r5 if r4 < r1
        movn    r4, r1, r5                      ; set the new max in r4 if r5 != 0

        daddi   r2, r2, 8                       ; r2 = r2 + 8
        bne     r2, r3, loop                    ; jump if r2 != r3

        sd      r4, result(r0)                  ; memory[result] = r4
        halt