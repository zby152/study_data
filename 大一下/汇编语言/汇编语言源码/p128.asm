assume cs:codesg
codesg segment
	dw 0123H,0456H,0789H,0abcH,0defH,0fedH,0cbaH,0987H
	dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  	
				;��dw����8���������ݣ��ڳ�����غ󣬽�ȡ��8���ֵ�
			    	;�ڴ�ռ䣬�����8�����ݡ������ں���ĳ����н����
			    	;�ռ䵱��ջ��ʹ�á�
  start: mov ax,cs		
	 mov ss,ax
	 mov sp,30h		;����ջ��ss:spָ��cs:30

	 mov bx,0
	 mov cx,8
      s: push cs:[bx]
	 add bx,2
	 loop s			;���Ͻ������0~15��Ԫ�е�8����������������ջ

	 mov bx,0
	 mov cx,8
     s0: pop cs:[bx]
	 add bx,2
	 loop s0		;�������γ�ջ8���������ݵ������0~15��Ԫ��
	 mov ax,4c00h
	 int 21h
codesg ends
end start			;ָ������������start��