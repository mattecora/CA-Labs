                AREA    |.divisible|, CODE, READONLY
                    
divisible       PROC
                EXPORT  divisible
                
                STMFD   SP!, {R4-R8, R10-R11, LR}   ; Backup registers on the stack
                
                SDIV    R4, R0, R1                  ; R4 = R0/R1
                MUL     R5, R4, R1                  ; R5 = R4*R1
                SUB     R0, R0, R5                  ; R0 = R0-R5
                
                LDMFD   SP!, {R4-R8, R10-R11, LR}   ; Restore registers from the stack
                BX      LR
                
                ENDP
                
                END
