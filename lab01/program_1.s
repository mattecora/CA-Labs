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

vector: .word   55,	65,	15,	75,	53,	41,	13,	32,	99,	41
        .word   56,	48,	47,	80,	92,	20,	14,	67,	17,	55
        .word   51,	5,	11,	56,	78,	49,	44,	34,	100,	71
        .word   8,	40,	63,	97,	37,	23,	100,	44,	40,	94
        .word   5,	38,	79,	62,	51,	33,	71,	21,	20,	88
        .word   14,	55,	2,	71,	44,	23,	89,	3,	98,	72
        .word   3,	15,	48,	71,	59,	4,	25,	85,	47,	9
        .word   51,	97,	91,	92,	5,	37,	23,	56,	75,	99
        .word   16,	43,	19,	34,	58,	55,	3,	23,	84,	38
        .word   29,	5,	80,	85,	93,	93,	39,	88,	63,	88
result: .space  8

        .text

main:   daddi	r2, r0, 0                       ; r2 = 0
        daddi	r3, r0, 800                     ; r3 = 800
        daddi	r4, r0, 0xffffffffffffffff      ; r4 = int_min

loop:   ld	r1, vector(r2)                  ; r1 = mem[vector + r2]
        slt	r5, r4, r1                      ; set r5 if r4 < r1
        beqz	r5, next                        ; if r5 == 0 then don't update

        dadd	r4, r1, r0                      ; set the new max in r4

next:   daddi	r2, r2, 8                       ; r2 = r2 + 8
        bne	r2, r3, loop                    ; jump if r2 != r3

        sd	r4, result(r0)                  ; memory[result] = r4
        halt