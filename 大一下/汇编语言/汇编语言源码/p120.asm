assume cs:code
code segment
	mov bx,0	;(bx)=0,ƫ�Ƶ�ַ��0��ʼ
	mov cx,12	;(cx)=12��ѭ��12��
s:	mov ax,0ffffh
	mov ds,ax	;(ds)=0ffffh
	mov dl,[bx]	;(dl)=((ds)*16+(bx))����ffff:bx�е���������dl
	mov ax,0020h
	mov ds,ax	;(ds)=0020h
	mov [bx],dl	;((ds)*16+(bx))=(dl)����dl����������0020:bx
	inc bx		;(bx)=(bx)+1
	loop s

	mov ax,4c00h
	int 21h
code ends
end 