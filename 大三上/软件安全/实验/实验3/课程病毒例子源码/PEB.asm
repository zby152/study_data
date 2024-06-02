; #########################################################################
      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive
; #########################################################################
      include \masm32\include\windows.inc

      include \masm32\include\user32.inc
      include \masm32\include\kernel32.inc
      includelib \masm32\lib\user32.lib
      includelib \masm32\lib\kernel32.lib
; #########################################################################
    .data
        szTitle db "Kernel32映像基地址搜索",0
        szMsg1   db 256 dup(0)
        fmt     db "Kernel32.dll的ImageBase是: %X",0

    .code
start:
    pushad
    assume fs:nothing
find_kernel32:
     push  esi
     xor   eax,eax
     mov   eax,fs:[eax+30h]      ; eax指向PEB结构
     test   eax,eax              ;是否为9x,9x的PEB结构不一样
     js     find_kernel32_9x
find_kernel32_nt:
     mov   eax,[eax+0ch]       ; eax指向PEB_LDR_DATA结构
     mov   esi,[eax+1ch]       ;指向动态链接库
     lodsd                            ;将 ESI 指向的数据载入到 EAX, 执行后 ESI 自动变化
     mov  eax,[eax+8h]         ;eax中为kernel32.dll基地址
     jmp  find_kernel32_finished
find_kernel32_9x:
     mov  eax,[eax+34h]
     lea   eax,[eax+7ch]
     mov  eax,[eax+3ch]
 find_kernel32_finished:

     invoke  wsprintf,offset szMsg1,offset fmt, eax
     invoke MessageBoxA,0,offset szMsg1, offset szTitle,1040h
     popad;
     invoke ExitProcess,0

 ;         invoke MessageBoxA,0,offset szMsg1, offset szTitle,1040h
 ;         invoke MessageBoxA,0,offset szMsg2, offset szTitle,1040h
 ;         invoke ExitProces

end start
