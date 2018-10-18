; program_2.s
; Parity bit computation

; Used registers:
; - r1: accumulator for loop1
; - r2: accumulator for loop2
; - r3: current byte
; - r4: working byte
; - r5: current parity bit
; - r6: parity bit sum

; Algorithm:
; - The byte is stored into r3 and r4
; - An and operation with 00000001 and r4 is computed and stored in r5, to isolate the LSB
; - The result is put in xor with the calculated parity bit in r6, so that if the LSB is 1 it changes its value
; - The working byte is shifted right arithmetically by one position
; - The operation is repeated 7 times (loop2)
; - If the calculated parity bit is 1 (odd), an or is performed between the original byte and 10000000, to set the MSB to 1
; - If the calculated parity bit is 0 (even), an and is performed between the original byte and 01111111, to set the MSB to 0
; - The operation is repeated for every element in the vector (loop1)

; Optimizations:
; - Vector scans from the end to the top, with loop decrement at the beginning

        .data

vector: .byte   0x1c, 0x1b, 0x78, 0x76, 0x15, 0x33, 0x0f, 0x40
        .byte   0x64, 0x72, 0x0a, 0x0f, 0x4a, 0x79, 0x6a, 0x04
        .byte   0x3c, 0x22, 0x6b, 0x48, 0x73, 0x2f, 0x7b, 0x09
        .byte   0x75, 0x3a, 0x29, 0x4b, 0x12, 0x3a, 0x50, 0x4d
        .byte   0x39, 0x53, 0x2e, 0x60, 0x7e, 0x4d, 0x68, 0x69
        .byte   0x65, 0x3d, 0x4f, 0x2c, 0x02, 0x1f, 0x63, 0x4a
        .byte   0x62, 0x01, 0x7f, 0x69, 0x0b, 0x3e, 0x23, 0x24
        .byte   0x66, 0x6c, 0x5f, 0x7f, 0x2c, 0x06, 0x67, 0x67
        .byte   0x0c, 0x1b, 0x59, 0x20, 0x2c, 0x39, 0x39, 0x1d
        .byte   0x24, 0x0c, 0x58, 0x32, 0x05, 0x3d, 0x6d, 0x43
        .byte   0x6c, 0x3f, 0x32, 0x21, 0x7e, 0x44, 0x24, 0x6d
        .byte   0x32, 0x38, 0x5b, 0x34, 0x61, 0x48, 0x2a, 0x09
        .byte   0x6e, 0x66, 0x63, 0xe0

        .text

main:   daddi   r1, r0, 100             ; r1 = 100

loop1:  daddi   r1, r1, -1              ; decrement r1
        lbu     r3, vector(r1)          ; load value
        
        daddi   r2, r0, 7               ; r2 = 7
        daddi   r4, r3, 0               ; r4 = r3
        daddi   r6, r0, 0               ; r6 = 0

loop2:  daddi   r2, r2, -1              ; decrement r2
        andi    r5, r4, 0x01            ; r5 = r4 and 00000001
        xor     r6, r6, r5              ; r6 = r6 xor r5
        dsrl    r4, r4, 1               ; shift by 1
        bnez    r2, loop2               ; loop 2

        beqz    r6, even                ; branch for even parity

odd:    ori     r3, r3, 0x80            ; set MSB to 1
        j       next                    ; skip even case

even:   andi    r3, r3, 0x7f            ; set MSB to 0

next:   sb      r3, vector(r1)          ; store value
        bnez    r1, loop1               ; loop 1

        halt