; ============================s_api.asm
;手动查找api部分
; K32_api_retrieve 过程的Base是DLL的基址，sApi为相应的API函数的函数名地址
;该过程返回eax为该API函数的序号
K32_api_retrieve        proc    Base:DWORD ,sApi:DWORD 
push  edx                   ;保存edx     
xor   eax,eax              	;此时esi=sApi 
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
mov   eax,[edi+eax*4]       ;AddressOfNames的指针,递增 
add   eax,Base              ;注意是RVA,一定要加Base值 
cmp   bl,byte  ptr [eax+edx];逐字符比较   
pop   eax 
je    Match_Api_name        ;继续搜寻 
inc   eax                   ;不匹配,下一个api 
loop  Next_Api 
no_exist: 
pop   edx                   ;若全部搜完,即未存在 
xor   eax,eax 
ret 
foundit: 
pop   edx                   ;edx=AddressOfNameOrdinals 
                               	;*2得到AddressOfNameOrdinals的指针 
movzx eax,word  ptr [edx+eax*2] ;eax返回指向AddressOfFunctions的指针 
ret 
K32_api_retrieve        endp 
;----------------------------------------- 
;Base是DLL的基址，sApi为相应的API函数的函数名地址，返回eax指向API函数地址
GetApiA        proc    Base:DWORD,sApi:DWORD 
local    ADDRofFun:DWORD 
pushad 
mov   esi,Base 
mov   eax,esi 
mov   ebx,eax 
mov   ecx,eax 
mov   edx,eax 
mov   edi,eax               ;几个寄存器全部置为DLL基址
add   ecx,[ecx+3ch]         ;现在esi=off PE_HEADER 
add   esi,[ecx+78h]         ;得到esi=IMAGE_EXPORT_DIRECTORY引出表入口 
add   eax,[esi+1ch]         ;eax=AddressOfFunctions的地址 
mov   ADDRofFun,eax 
mov   ecx,[esi+18h]         ;ecx=NumberOfNames 
add   edx,[esi+24h]                
  ;edx=AddressOfNameOrdinals，指向函数对应序列号数组
add   edi,[esi+20h]         ;esi=AddressOfNames 
invoke    K32_api_retrieve,Base,sApi ;调用另外一个过程，得到一个API函数序号
mov   ebx,ADDRofFun
mov   eax,[ebx+eax*4]       ;要*4才得到偏移 
add   eax,Base              ;加上Base! 
mov   [esp+7*4],eax         ;eax返回api地址 
popad 
ret 
GetApiA   endp 
u32        db "User32.dll",0 
k32        db "Kernel32.dll",0 
appBase    dd ? 
k32Base    dd ? 
;-------------以下是有关API函数地址和名称的相关数据定义------------
lpApiAddrs      label  near            
;定义一组指向函数名字字符串偏移地址的数组
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
dd      0,0         ;以便判断函数是否处理完毕
;下面定义函数名字符串，以便于和引出函数表中的相关字段进行比较
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

aGetModuleHandle		dd 0    ;找到相应API函数地址后的存放位置
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
