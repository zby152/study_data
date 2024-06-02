;============================disLen.asm 
lea    eax,[ebp+u32] 
push   eax 
call   dword ptr [ebp+aLoadLibrary]  ;导入user32.dll链接库
test   eax,eax 
jnz    @g1       
@g1: 
    lea    EDX,[EBP+sMessageBoxA] 
push   edx 
push   eax 
mov    eax,dword ptr [ebp+aGetProcAddress]  ;获取MessageBoxA函数的地址
call   eax 
mov    [ebp+aMessageBoxA],eax 
;----------------------------------------- 
mov    ebx,VirusLen 
mov    ecx,8 
cld 
lea    edi,[ebp+val]
L1: 
rol    ebx,4 
call   binToAscii 
loop   L1 
push   40h+1000h 
lea    eax,[ebp+sztit] 
push   eax 
lea    eax,[ebp+CopyRight] 
push   eax 
push   0 
call   [ebp+aMessageBoxA] 
jmp    _where 
;----------------------------------------- 
binToAscii    proc  near       ;此函数用来将二进制转换为字符
mov    eax,ebx
and    eax,0fh
add    al,30h
cmp    al,39h
 	jbe    @f
add    al,7
 @@: 
stosb 
ret 
binToAscii    endp
