assume cs:code
code segment
	mov ax,0ffffh
	mov ds,ax		;(ds)=0ffffh
	mov ax,0020h
	mov es,ax		;(es)=0020h
	mov bx,0		;(bx)=0,��ʱds:bxָ��ffff:0��es:bxָ��0020:0
	mov cx,12		;(cx)=12��ѭ��12��
s:	mov dl,[bx]		;(dl)=((ds)*16+(bx))����ffff:bx�е���������dl	
	mov es:[bx],dl		;((es)*16+(bx))=(dl)����dl����������0020:bx
	inc bx			;(bx)=(bx)+1
	loop s

	mov ax,4c00h
	int 21h
code ends
end 