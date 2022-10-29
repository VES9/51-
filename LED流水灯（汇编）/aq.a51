/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/
ORG 0000H//伪指令ORG 程序起始地址为0000H
	JMP START// JMP无条件跳转指令 跳转至START
	START:MOV A,#00H//将立即数00H送入寄存器A中
	      MOV B,#0FFH//将立即数0FFH送入寄存器B中
	      MOV P2,A//将A中的内容送入P2中
		  LCALL DELAY//调用延时函数进行延时
		  MOV P2,B//将B中的内容送入到P2中
		  LCALL DELAY//调用延时函数进行延时
		  JMP START// JMP无条件跳转指令 跳转至START，进行循环
		  
	
	DELAY://DELAY函数

    DEL50:MOV R7,#200//将立即数200送入寄存器R7中
	DEL1: MOV R6,#125//将立即数125送入寄存器R6中
	DEL2: DJNZ R6,DEL2//DJNZ 减一不为0条件指令，若减一不为零，跳转至DEL2，减一为零，顺序执行
	      DJNZ R7,DEL1//
	RET//子程序的返回指令，ret指令是从堆栈中退出pc的高8位和低8位字节，把堆栈指针减2，从pc值处开始继续执行程序。
	
	
	JMP $// $代表当前的地址,那JMP $"就是跳转到当前的地址， 所以它是一个死循环，不继续执行下面的程序了。
	END//伪指令 结束
	