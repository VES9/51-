ORG 0000H
LJMP MAIN
ORG 001BH
LJMP INT
ORG 0100H
MAIN:
     MOV TMOD,#10H
	 MOV TH1,#0D8H
	 MOV TL1,#0F0H
	 MOV R2,#200
	 SETB EA
	 SETB ET1
	 SETB TR1
	 SJMP $
INT:
     DJNZ R2,NEXT
	    
	 CPL P1.0
	 MOV R2,#200
NEXT:MOV TH1,#0D8H
	 MOV TL1,#0F0H

;	 SETB TR1
	 RETI
	 END


	