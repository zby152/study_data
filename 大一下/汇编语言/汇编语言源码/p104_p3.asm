;p104 С�� 5.3 ��Debug�и�����loopָ��ʵ�ֵ�ѭ������ ��ʵ�����5.3����
;
assume cs:code
code segment
	mov ax,0ffffh
	mov ds,ax
	mov bx,6              ;���ϣ�����ds:bxָ��ffff:6

	mov al,[bx]
	mov ah,0              ;���ϣ�����(al)=((ds*16)+(bx)),(ah)=0��

	mov dx,0              ;�ۼӼĴ�����0
	
	mov cx,3              ;ѭ��3��
s:	add dx,ax
	loop s                ;�����ۼӼ���(ax)*3

	mov ax,4c00h          ;���򷵻�
	int 21h

code ends
end