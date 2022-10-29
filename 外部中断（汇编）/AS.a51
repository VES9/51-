ORG 0000H
LJMP MAIN
ORG 0003H
LJMP K0
ORG 0013H
LJMP K1
ORG 0030H
	
	MAIN:MOV SP,#30H	;设置堆栈（堆栈空间），原先单片机上电时，SP为07H，这里相当于初始化，把SP值改为30H
	MOV IE,#85H;1000 0101.允许外部中断0，外部中断1中断
	MOV IP,#04H;外部中断1为高优先级
	MOV TCON,#01H;外部中断0为边沿触发
	MOV A,#00H;将立即数00H装入A中
	
	LP1:MOV P1,A;将A中的内容装入P1中
	LCALL DELAY;调用延时函数
	CPL A;将A取反
	SJMP LP1;跳到LP1
	
	ORG 0100H
	K0:PUSH ACC;这是堆栈，表示将当前寄存器的内容放到堆栈中，取出则用POP A
	PUSH PSW;将程序状态字压栈
	CLR RS1;选择第一组工作寄存器
	SETB RS0;
	MOV R2,#07H;将立即数07H装入R2中
	MOV A,#0FEH;1111 1110，为灯点亮的初始状态
	
	NEXT0:MOV P1,A;将A中的内容装入P1中
	LCALL DELAY;调用延时函数
	RL A;循环左移指令，执行一次，累加器中的值左移一位，最高位移到最低位，点亮左边一盏灯
	DJNZ R2,NEXT0;R2-1，判断该值是否为0，若果等于0，往下执行，如果不等于0，转到NEXT0
	POP PSW;将程序状态字出栈
	POP ACC;
	RETI;中断返回指令，用于从中断服务程序中返回
	
	ORG 0200H
	K1:PUSH ACC;
	PUSH PSW;
	CLR RS1;
	SETB RS0;
	MOV R2,#07H;
	MOV A,#07FH;
	
	NEXT1:
	MOV P1,A
	LCALL DELAY
	RL A
	DJNZ R2,NEXT1
	POP PSW
	POP ACC
	RETI
	
	ORG 0300H
		DELAY:MOV R3,#250
		DEL2:MOV R2,#248
		DJNZ R3,DEL2
		RET;子程序返回
		END
	
	
	
	
	
	
				