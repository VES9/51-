ORG 0000H
LJMP MAIN
ORG 0003H
LJMP K0
ORG 0013H
LJMP K1
ORG 0030H
	
	MAIN:MOV SP,#30H	;���ö�ջ����ջ�ռ䣩��ԭ�ȵ�Ƭ���ϵ�ʱ��SPΪ07H�������൱�ڳ�ʼ������SPֵ��Ϊ30H
	MOV IE,#85H;1000 0101.�����ⲿ�ж�0���ⲿ�ж�1�ж�
	MOV IP,#04H;�ⲿ�ж�1Ϊ�����ȼ�
	MOV TCON,#01H;�ⲿ�ж�0Ϊ���ش���
	MOV A,#00H;��������00Hװ��A��
	
	LP1:MOV P1,A;��A�е�����װ��P1��
	LCALL DELAY;������ʱ����
	CPL A;��Aȡ��
	SJMP LP1;����LP1
	
	ORG 0100H
	K0:PUSH ACC;���Ƕ�ջ����ʾ����ǰ�Ĵ��������ݷŵ���ջ�У�ȡ������POP A
	PUSH PSW;������״̬��ѹջ
	CLR RS1;ѡ���һ�鹤���Ĵ���
	SETB RS0;
	MOV R2,#07H;��������07Hװ��R2��
	MOV A,#0FEH;1111 1110��Ϊ�Ƶ����ĳ�ʼ״̬
	
	NEXT0:MOV P1,A;��A�е�����װ��P1��
	LCALL DELAY;������ʱ����
	RL A;ѭ������ָ�ִ��һ�Σ��ۼ����е�ֵ����һλ�����λ�Ƶ����λ���������һյ��
	DJNZ R2,NEXT0;R2-1���жϸ�ֵ�Ƿ�Ϊ0����������0������ִ�У����������0��ת��NEXT0
	POP PSW;������״̬�ֳ�ջ
	POP ACC;
	RETI;�жϷ���ָ����ڴ��жϷ�������з���
	
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
		RET;�ӳ��򷵻�
		END
	
	
	
	
	
	
				