/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/
ORG 0000H//αָ��ORG ������ʼ��ַΪ0000H
	JMP START// JMP��������תָ�� ��ת��START
	START:MOV A,#00H//��������00H����Ĵ���A��
	      MOV B,#0FFH//��������0FFH����Ĵ���B��
	      MOV P2,A//��A�е���������P2��
		  LCALL DELAY//������ʱ����������ʱ
		  MOV P2,B//��B�е��������뵽P2��
		  LCALL DELAY//������ʱ����������ʱ
		  JMP START// JMP��������תָ�� ��ת��START������ѭ��
		  
	
	DELAY://DELAY����

    DEL50:MOV R7,#200//��������200����Ĵ���R7��
	DEL1: MOV R6,#125//��������125����Ĵ���R6��
	DEL2: DJNZ R6,DEL2//DJNZ ��һ��Ϊ0����ָ�����һ��Ϊ�㣬��ת��DEL2����һΪ�㣬˳��ִ��
	      DJNZ R7,DEL1//
	RET//�ӳ���ķ���ָ�retָ���ǴӶ�ջ���˳�pc�ĸ�8λ�͵�8λ�ֽڣ��Ѷ�ջָ���2����pcֵ����ʼ����ִ�г���
	
	
	JMP $// $����ǰ�ĵ�ַ,��JMP $"������ת����ǰ�ĵ�ַ�� ��������һ����ѭ����������ִ������ĳ����ˡ�
	END//αָ�� ����
	