/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/


ORG 0000H  //伪指令ORG 程序起始地址为0000H
	JMP START// JMP无条件跳转指令 跳转至START
	START: MOV A,#00H //将立即数00H装入寄存器A中
	       MOV P2,A//将A中的内容装入P2中
		   JMP $//  $代表当前的地址,那JMP $"就是跳转到当前的地址， 所以它是一个死循环，不继续执行下面的程序了。
			   END// 伪指令 结束
				
	