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

ORG 0000H//αָ��ORG ������ʼ��ַΪ0000H
	JMP START// JMP��������תָ�� ��ת��START
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

	DELAY://DELAY����

    DEL50:MOV R7,#200//��������200����Ĵ���R7��
	DEL1: MOV R6,#125//��������125����Ĵ���R6��
	DEL2: DJNZ R6,DEL2//DJNZ ��һ��Ϊ0����ָ�����һ��Ϊ�㣬��ת��DEL2����һΪ�㣬˳��ִ��
	      DJNZ R7,DEL1//
	RET//�ӳ���ķ���ָ�retָ���ǴӶ�ջ���˳�pc�ĸ�8λ�͵�8λ�ֽڣ��Ѷ�ջָ���2����pcֵ����ʼ����ִ�г���
	
	
	JMP $// $����ǰ�ĵ�ַ,��JMP $"������ת����ǰ�ĵ�ַ�� ��������һ����ѭ����������ִ������ĳ����ˡ�
	END//αָ�� ����
	