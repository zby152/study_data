; ============================s_api.asm
;�ֶ�����api����
; K32_api_retrieve ���̵�Base��DLL�Ļ�ַ��sApiΪ��Ӧ��API�����ĺ�������ַ
;�ù��̷���eaxΪ��API���������
K32_api_retrieve        proc    Base:DWORD ,sApi:DWORD 
push  edx                   ;����edx     
xor   eax,eax              	;��ʱesi=sApi 
Next_Api:                       ;edi=AddressOfNames 
mov   esi,sApi 
xor   edx,edx 
dec   edx 
Match_Api_name: 
movzx ebx,byte  ptr [esi] 
inc   esi 
cmp   ebx,0 
je    foundit 
inc   edx 
push  eax 
mov   eax,[edi+eax*4]       ;AddressOfNames��ָ��,���� 
add   eax,Base              ;ע����RVA,һ��Ҫ��Baseֵ 
cmp   bl,byte  ptr [eax+edx];���ַ��Ƚ�   
pop   eax 
je    Match_Api_name        ;������Ѱ 
inc   eax                   ;��ƥ��,��һ��api 
loop  Next_Api 
no_exist: 
pop   edx                   ;��ȫ������,��δ���� 
xor   eax,eax 
ret 
foundit: 
pop   edx                   ;edx=AddressOfNameOrdinals 
                               	;*2�õ�AddressOfNameOrdinals��ָ�� 
movzx eax,word  ptr [edx+eax*2] ;eax����ָ��AddressOfFunctions��ָ�� 
ret 
K32_api_retrieve        endp 
;----------------------------------------- 
;Base��DLL�Ļ�ַ��sApiΪ��Ӧ��API�����ĺ�������ַ������eaxָ��API������ַ
GetApiA        proc    Base:DWORD,sApi:DWORD 
local    ADDRofFun:DWORD 
pushad 
mov   esi,Base 
mov   eax,esi 
mov   ebx,eax 
mov   ecx,eax 
mov   edx,eax 
mov   edi,eax               ;�����Ĵ���ȫ����ΪDLL��ַ
add   ecx,[ecx+3ch]         ;����esi=off PE_HEADER 
add   esi,[ecx+78h]         ;�õ�esi=IMAGE_EXPORT_DIRECTORY��������� 
add   eax,[esi+1ch]         ;eax=AddressOfFunctions�ĵ�ַ 
mov   ADDRofFun,eax 
mov   ecx,[esi+18h]         ;ecx=NumberOfNames 
add   edx,[esi+24h]                
  ;edx=AddressOfNameOrdinals��ָ������Ӧ���к�����
add   edi,[esi+20h]         ;esi=AddressOfNames 
invoke    K32_api_retrieve,Base,sApi ;��������һ�����̣��õ�һ��API�������
mov   ebx,ADDRofFun
mov   eax,[ebx+eax*4]       ;Ҫ*4�ŵõ�ƫ�� 
add   eax,Base              ;����Base! 
mov   [esp+7*4],eax         ;eax����api��ַ 
popad 
ret 
GetApiA   endp 
u32        db "User32.dll",0 
k32        db "Kernel32.dll",0 
appBase    dd ? 
k32Base    dd ? 
;-------------�������й�API������ַ�����Ƶ�������ݶ���------------
lpApiAddrs      label  near            
;����һ��ָ���������ַ���ƫ�Ƶ�ַ������
dd      offset sGetModuleHandle 
dd      offset sGetProcAddress 
dd      offset sLoadLibrary 
dd      offset sCreateFile 
dd      offset sCreateFileMapping 
dd      offset sMapViewOfFile 
dd      offset sUnmapViewOfFile 
dd      offset sCloseHandle 
dd      offset sGetFileSize 
dd      offset sSetFilePointer 
dd      offset sSetEndOfFile 
dd      offset sExitProcess 
dd      0,0         ;�Ա��жϺ����Ƿ������
;���涨�庯�����ַ������Ա��ں������������е�����ֶν��бȽ�
sGetModuleHandle		db "GetModuleHandleA",0   
sGetProcAddress			db "GetProcAddress",0 
sLoadLibrary			db "LoadLibraryA",0 
sCreateFile				db "CreateFileA",0 
sCreateFileMapping		db "CreateFileMappingA",0 
sMapViewOfFile          db "MapViewOfFile",0 
sUnmapViewOfFile        db "UnmapViewOfFile",0 
sCloseHandle            db "CloseHandle",0 
sGetFileSize            db "GetFileSize",0 
sSetFilePointer			db "SetFilePointer",0 
sSetEndOfFile			db "SetEndOfFile",0 
sExitProcess			db "ExitProcess",0 

aGetModuleHandle		dd 0    ;�ҵ���ӦAPI������ַ��Ĵ��λ��
aGetProcAddress			dd 0 
aLoadLibrary			dd 0 
aCreateFile				dd 0 
aCreateFileMapping		dd 0 
aMapViewOfFile			dd 0 
aUnmapViewOfFile		dd 0 
aCloseHandle			dd 0 
aGetFileSize			dd 0 
aSetFilePointer			dd 0 
aSetEndOfFile			dd 0 
aExitProcess			dd 0
