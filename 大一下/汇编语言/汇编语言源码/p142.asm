assume cs:codesg,ds:datasg
datasg segment
db 'BaSiC'
db 'iNfOrMaTiOn'
datasg ends

codesg segment
start: mov ax,datasg
       mov ds,ax		;����dsָ��datasg��

       mov bx,0			;����(bx)=0��ds:bxָ��BaSiC���ĵ�һ����ĸ

       mov cx,5			;����ѭ������5����Ϊ��BaSiC������5����ĸ
    s: mov al,[bx]		;��ASCII���ds:bx��ָ��ĵ�Ԫ��ȡ��
       and al,11011111b		;��al�е�ASCII��ĵ�5λ��Ϊ0����Ϊ��д��ĸ
       mov [bx],al		;��ת����ASCII��д��ԭ��Ԫ

       inc bx			;(bx)��1��ds:bxָ����һ����ĸ
       loop s


       mov bx,5			;����(bx)=5��ds:bxָ��iNfOrMaTiOn���ĵ�һ����ĸ

       mov cx,11		;����ѭ������11����Ϊ��iNfOrMaTiOn������11����ĸ
   s0: mov al,[bx]
       or al,00100000b		;��al�е�ASCII��ĵ�5λ��Ϊ0����ΪСд��ĸ
       mov [bx],al
       inc bx
       loop s0

       mov ax,4c00h
       int 21h
codesg ends
end start
