;��̣��������������ʱ������Ļ�м���ʾ��overflow����������DOS��

;��������ǰ����ж�֪ʶ��ϸ�����������е����ϸ�ڵĴ���

assume cs:code
code segment
start:
	
	;��ش���	
	
      	mov ax,4c00h
      	int 21h

  do0:
	;��ʾ�ַ��� "overflow!"

      	mov ax,4c00h;����DOS
      	int 21h

code ends
end start
