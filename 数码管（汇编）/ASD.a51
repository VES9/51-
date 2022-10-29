/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/
D EQU P0
	W EQU P2

ORG 0000H//伪指令ORG 程序起始地址为0000H
	JMP START// JMP无条件跳转指令 跳转至START
	START:LCALL DISPALY
	      AJMP START
	
  DISPALY:MOV A,#0xC0
	      MOV D,A
		  MOV B,#0x01
		  MOV W,B
		  LCALL DELAY300MS

          MOV A,#0xF9
	      MOV D,A
		  MOV B,#0x02
		  MOV W,B
		  LCALL DELAY300MS
		
		  MOV A,#0xA4
	      MOV D,A
		  MOV B,#0x04
		  MOV W,B
		  LCALL DELAY300MS
		  
		  MOV A,#0xB0
	      MOV D,A
		  MOV B,#0x08
		  MOV W,B
		  LCALL DELAY300MS
		  
		  MOV A,#0x99
	      MOV D,A
		  MOV B,#0x10
		  MOV W,B
		  LCALL DELAY300MS
		  
		  MOV A,#0x92
	      MOV D,A
		  MOV B,#0x20
		  MOV W,B
		  LCALL DELAY300MS
		  
		  MOV A,#0x82
	      MOV D,A
		  MOV B,#0x40
		  MOV W,B
		  LCALL DELAY300MS
		  
		  MOV A,#0xF8
	      MOV D,A
		  MOV B,#0x80
		  MOV W,B
		  LCALL DELAY300MS
	      RET
	
DELAY300MS:			;@12.000MHz
		 NOP
		 NOP
		 NOP
		 PUSH 30H
		 PUSH 31H
		 PUSH 32H
		 MOV 30H,#11
		 MOV 31H,#242
		 MOV 32H,#124
     NEXT:
		 DJNZ 32H,NEXT
		 DJNZ 31H,NEXT
		 DJNZ 30H,NEXT
		 POP 32H
		 POP 31H
		 POP 30H
		 RET

	DELAY://DELAY函数

    DEL50:MOV R7,#200//将立即数200送入寄存器R7中
	DEL1: MOV R6,#125//将立即数125送入寄存器R6中
	DEL2: DJNZ R6,DEL2//DJNZ 减一不为0条件指令，若减一不为零，跳转至DEL2，减一为零，顺序执行
	      DJNZ R7,DEL1//
	RET//子程序的返回指令，ret指令是从堆栈中退出pc的高8位和低8位字节，把堆栈指针减2，从pc值处开始继续执行程序。
	
	
	JMP $// $代表当前的地址,那JMP $"就是跳转到当前的地址， 所以它是一个死循环，不继续执行下面的程序了。
	END//伪指令 结束
	