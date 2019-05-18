	;AREA |.text|, CODE, READONLY
	AREA RESET, CODE, READONLY
	;EXPORT main
	THUMB
	ENTRY
start
main
	B loadarray
loadarray ;moves array from program memory to data memory
	LDR R3, =ARR        ;load base address of array in program memory into R3
	LDR R4, =0x20000000 ;load new base address of array into R3, in data memory
	MOV R6, #0          ;current element index to be copied
loaditeration ;moves a single element of array from program -> data memory
	CMP R6, #12         ;if R5 >= 12, array has been copied, so jump to sort
	BGE sort            ;once the array has been copied, sort the array
	LDR  R7, [R3, R6, LSL #2]  ;load first element of arr into R7, left shifting as word-addressing
	STRB R7, [R4, R6]  ;storing this element in data memory
	ADD R6, R6, #1      ;incrementing index
	B loaditeration
sort
	LDR R3, =0x20000000 ;load base address of array into R3
	MOV R4, #0          ;setting iteration number to 0
	MOV R5, #0          ;setting iteration position to 0
iteration
	CMP R4, #11        ;if R4 is greater than or equal to 12, stop program execution
	BGE done           ;jumping to the end of the program
	ADD R4, R4, #1     ;incrementing R4		
	MOV R5,     #0     ;setting R5 back to 0
position
	CMP   R5, #11        ;if R5 is greater than or equal to 11, stop program execution
	BGE   position_done  ;11 is used because comparing element i and i+1: hence i+1=12 when i=1
	ADD   R6, R5, #1     ;compute R5+1, the address of the element to compare against, in R6 
	LDRSB R7, [R3, R5]   ;load data at position R5 from the array into R7
	LDRSB R8, [R3, R6]   ;load data at position R5+1 from the array into R8
	CMP   R7, R8         ;only swap when R7 > R8
	BLE   swapped        ;so skip swap and jump to next step of loop 
	STRB  R8, [R3, R5]   ;store R7 into array position R5
	STRB  R7, [R3, R6]   ;store R8 into array position R6
swapped
	ADD   R5, R5, #1     ;incrementing R5
	B   position         ;this iteration of the inner loop is done
position_done
	B iteration        ;this iteration of the outer loop is done
done
	NOP
	MOV      r0, #0x18      ; angel_SWIreason_ReportException
    LDR      r1, =0x20026   ; ADP_Stopped_ApplicationExit
    SVC      #0xAB          ; ARM semihosting (formerly SWI)
	
	
	
ARR DCD 12,11,10,9,8,7,6,5,4,3,2,1
	
	ALIGN
	END
