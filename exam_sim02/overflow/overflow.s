                AREA    |.overflow|, CODE, READONLY
                    
overflow        PROC
                EXPORT  overflow
                
                STMFD   SP!, {R4-R8, R10-R11, LR}   ; Backup registers on the stack
                
                LDR     R4, =0                      ; R4 = 0
                LDR     R5, =0                      ; R5 = 0
                LDR     R6, =2                      ; R6 = 2
                
loop            LDR     R7, [R0, R4, LSL #2]        ; R7 = V[R4]
                ADDS    R5, R5, R7                  ; R5 = R5 + R7
                
                BVS     overflow_set
                BCS     carry_set
                
                ADD     R4, R4, #1                  ; Increment R4
                CMP     R4, R1                      ; R4 == R1
                
                BNE     loop                        ; Loop if not equal
                B       return
                
overflow_set    LDR     R6, =0                      ; Overflow produced
                B       return

carry_set       LDR     R6, =1                      ; Carry produced

return          MOV     R0, R6                      ; Return R6
                
                LDMFD   SP!, {R4-R8, R10-R11, LR}   ; Restore registers from the stack
                BX      LR
                
                ENDP
                
                END
