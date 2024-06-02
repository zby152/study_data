assume cs:code

stack segment
 db 128 dup (0)
stack ends

code segment
start:mov ax,stack
	mov ss,ax
	mov sp,128

	push cs
	pop ds
	mov si,offset int9

	mov ax,0
	mov es,ax
	mov di,204h
	mov cx,offset int9end - offset int9
	cld
	rep movsb	

	push es:[9*4]
	pop es:[200h]
	push es:[9*4+2]
	pop es:[202h]   ;����ԭ����int 9�ж�����

	cli
	mov word ptr es:[9*4],204h
        mov word ptr es:[9*4+2],0
	sti
	
	mov ax,4c00h
	int 21h

   ;---����������Ҫ��װ�� int 9 �жϴ������---------------------

 int9:
	push ax
	push bx
	push cx
	push es
        
	in al,60h

	pushf        
        call dword ptr cs:[200h] 

        cmp al,1eh 
	jne int9ret

  check:in al,60h
        cmp al,9eh
        jne check

	mov ax,0b800h
	mov es,ax
        mov bx,0
	mov cx,2000
        mov al,'A'
int9s:	
        mov es:[bx],al  ;��ɫ���� +1 
	add bx,2
	loop int9s

int9ret:pop es
	pop cx
	pop bx
	pop ax
	iret
int9end:nop

code ends
end start
