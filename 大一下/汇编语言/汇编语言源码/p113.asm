assume cs:code
code segment
	mov ax,0ffffh
	mov ds,ax	;����(ds)=0ffffh
	
	mov dx,0	;��ʼ���ۼӼĴ�����(dx)=0
	
	mov al,ds:[0]
	mov ah,0 	;(ax)=((ds)*16+0)=(0ffff0h)
	add dx,ax	;��dx�м���0ffffh:0��Ԫ����ֵ

	mov al,ds:[1]
	mov ah,0 	;(ax)=((ds)*16+1)=(0ffff1h)
	add dx,ax	;��dx�м���0ffffh:1��Ԫ����ֵ

	mov al,ds:[2]
	mov ah,0 	;(ax)=((ds)*16+2)=(0ffff2h)
	add dx,ax	;��dx�м���0ffffh:2��Ԫ����ֵ

	mov al,ds:[3]
	mov ah,0 	;(ax)=((ds)*16+3)=(0ffff3h)
	add dx,ax	;��dx�м���0ffffh:3��Ԫ����ֵ

	mov al,ds:[4]
	mov ah,0 	;(ax)=((ds)*16+4)=(0ffff4h)
	add dx,ax	;��dx�м���0ffffh:4��Ԫ����ֵ

	mov al,ds:[5]
	mov ah,0 	;(ax)=((ds)*16+5)=(0ffff5h)
	add dx,ax	;��dx�м���0ffffh:5��Ԫ����ֵ

	mov al,ds:[6]
	mov ah,0 	;(ax)=((ds)*16+6)=(0ffff6h)
	add dx,ax	;��dx�м���0ffffh:6��Ԫ����ֵ

	mov al,ds:[7]
	mov ah,0 	;(ax)=((ds)*16+7)=(0ffff7h)
	add dx,ax	;��dx�м���0ffffh:7��Ԫ����ֵ

	mov al,ds:[8]
	mov ah,0 	;(ax)=((ds)*16+8)=(0ffff8h)
	add dx,ax	;��dx�м���0ffffh:8��Ԫ����ֵ

	mov al,ds:[9]
	mov ah,0 	;(ax)=((ds)*16+9)=(0ffff9h)
	add dx,ax	;��dx�м���0ffffh:9��Ԫ����ֵ

	mov al,ds:[0ah]
	mov ah,0 	;(ax)=((ds)*16+0ah)=(0ffffah)
	add dx,ax	;��dx�м���0ffffh:0ah��Ԫ����ֵ

	mov al,ds:[0bh]
	mov ah,0 	;(ax)=((ds)*16+0bh)=(0ffffbh)
	add dx,ax	;��dx�м���0ffffh:0bh��Ԫ����ֵ

	mov ax,4c00h	;���򷵻�
	int 21h
code ends
end 