/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/


ORG 0000H  //αָ��ORG ������ʼ��ַΪ0000H
	JMP START// JMP��������תָ�� ��ת��START
	START: MOV A,#00H //��������00Hװ��Ĵ���A��
	       MOV P2,A//��A�е�����װ��P2��
		   JMP $//  $����ǰ�ĵ�ַ,��JMP $"������ת����ǰ�ĵ�ַ�� ��������һ����ѭ����������ִ������ĳ����ˡ�
			   END// αָ�� ����
				
	