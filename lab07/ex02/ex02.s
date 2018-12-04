; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200
Price_list_Size EQU     28*4*2

                AREA    HEAP, READWRITE, ALIGN=3
__heap_base

Price_list_RW   SPACE   Price_list_Size         ; will contain the sorted data

Heap_Mem        SPACE   Heap_Size - Price_list_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF
                
                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]

Num_items       EQU     28

;               RESULT = 424975F

;               ################
;               # SORT SECTION #
;               ################

;               Registers for sorting:
;               - r0: external loop index
;               - r1: base register for RO
;               - r2: base register for RW
;               - r3: external value
;               - r4: external price
;               - r5: internal loop index
;               - r6: internal value
;               - r7: internal price
;               - r10: used for target address computation

;               Algorithm for sorting: insertion sort
                
                LDR     R0, =1                      ; External loop index in R0
                LDR     R1, =Price_list             ; Base register for RO in R1
                LDR     R2, =Price_list_RW          ; Base register for RW in R2
                
                LDRD    R3, R4, [R1]                ; Load the first value and price
                STRD    R3, R4, [R2]                ; Store the first value and price in RW
                
SortLoop1       ADD     R10, R1, R0, LSL #3         ; Compute target address in R10 (R1 + R0*8)
                LDRD    R3, R4, [R10]               ; Load external value and the price in R3-R4
                MOV     R5, R0                      ; Internal loop index in R5
                
SortLoop2       SUB     R5, R5, #1                  ; Consider the previous element
                ADD     R10, R2, R5, LSL #3         ; Compute target address in R10 (R2 + R5*8)
                LDRD    R6, R7, [R10]               ; Load the previous value and the price in R6-R7
                
                ADD     R5, R5, #1                  ; Consider the following element
                ADD     R10, R2, R5, LSL #3         ; Compute target address in R10 (R2 + R5*8)
                CMP     R3, R6                      ; Compare values
                
                ;       Greater or equal
                BGE     NextSortLoop1               ; Break
                
                ;       Lower
                STRD    R6, R7, [R10]               ; Store the internal value and its price in the following cells
                SUBS    R5, R5, #1                  ; Decrement iternal index by 1
                BGE     SortLoop2

NextSortLoop1   STRD    R3, R4, [R10]               ; Store the external value and its price in the target cells
                ADD     R0, R0, #1                  ; Increment external index by 1
                CMP     R0, #Num_items
                BLT     SortLoop1

;               ###################
;               # COMPUTE SECTION #
;               ###################

                ;       General initialization
                LDRB    R0, Item_num                ; Set R0 to Item_num
                LDR     R1, =Item_list              ; Base register for Item_list in R1
                LDR     R9, =Price_list_RW          ; Base register for Price_list_RW in R9
                LDR     R10, =0                     ; Initial price to zero
                
                ;       Items loop initialization
ItemsLoop       LDR     R2, =0                      ; Left bound to zero
                LDR     R3, =(Num_items-1)          ; Right bound to Num_items - 1
                LDRD    R4, R5, [R1]                ; Load item in R4 and quantity in R5
                
                ;       Compute the middle
SearchLoop      ADD     R6, R2, R3                  ; R6 = R2 + R3
                ASR     R6, R6, #1                  ; R6 = R6 / 2
                
                ;       Load value and compare
                ADD     R7, R9, R6, LSL #3          ; Compute address for val and price in R7 (R9 + R6*8)
                LDRD    R7, R8, [R7]                ; Load val in R7 and price in R8
                CMP     R4, R7                      ; Compare item and val
                
                ;       Equals
                MULEQ   R8, R5, R8                  ; Compute price for the product (R5*R8)
                ADDEQ   R10, R10, R8                ; Update total price
                BEQ     NextSearchLoop              ; Break
                
                ;       Greater (HI)
                ADDHI   R2, R6, #1                  ; Update left bound (middle+1)
                
                ;       Lower (LO)
                SUBLO   R3, R6, #1                  ; Update right bound (middle-1)
                
                ;       Check search loop condition
                CMP     R2, R3
                BLE     SearchLoop                  ; Branch if first <= last (signeds)
                
                ;       Item is not present
                LDR     R10, =0                     ; Set total price to zero
                B       InfLoop                     ; Terminate
                
                ;       Check item loop condition
NextSearchLoop  ADD     R1, R1, #8                  ; Update R1 (R1 = R1+8)
                SUBS    R0, R0, #1                  ; Update R0 (R0 = R0-1)
                BNE     ItemsLoop                   ; Branch if Z = 1
				
InfLoop         B       InfLoop
                ENDP

                ;       Literal pool

Price_list      DCD     0x007,  1210,   0x01E,  11,     0x039,  112,    0x018,  138
                DCD     0x047,  2627,   0x010,  228,    0x02D,  410,    0x03E,  661
                DCD     0x025,  240,    0x027,  112,    0x012,  7,      0x01B,  34
                DCD     0x045,  1112,   0x006,  315,    0x01A,  2222,   0x016,  722
                DCD     0x042,  230,    0x004,  120,    0x036,  3211,   0x02C,  2245
                DCD     0x031,  840,    0x022,  223,    0x033,  945,    0x017,  1217
                DCD     0x03C,  719,    0x00A,  245,    0x023,  1249,   0x04A,  265

Item_list       DCD     0x022,  14,     0x006,  431,    0x03E,  1210,   0x017,  56342 

Item_num        DCB     4

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit                

                END
