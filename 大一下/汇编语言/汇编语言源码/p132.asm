assume cs:b,ds:a,ss:c

a segment
  dw 0123H,0456H,0789H,0abcH,0defH,0fedH,0cbaH,0987H
a ends

c segment
  dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
c ends

b segment
d:    mov ax,c
      mov ss,ax
      mov sp,20h	;����ջ��ss:spָ��c:20
      
      mov ax,a
      mov ds,ax		;ϣ����ds:bx����a���е����ݣ�dsָ��a��

      mov bx,0		;ds:bxָ��a���еĵ�һ����Ԫ
      mov cx,8
    s:push [bx]
      add bx,2
      loop s		;���Ͻ�a���е�0~15��Ԫ�е�8����������������ջ

      mov bx,0
      mov cx,8
   s0:pop [bx]
      add bx,2
      loop s0		;����ʹ8�������������γ�ջ���͵�a�ε�0~15��Ԫ��

      mov ax,4c00h
      int 21h
b ends
end d
