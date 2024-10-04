from sm4 import sm4
import random


def str2num(s):
    b = s.encode()
    return int.from_bytes(b, byteorder="little", signed=False)


def read_file(p):
    res = []
    for i in range(0, len(p), 16):
        j = min(len(p), i + 16)
        res.append(int.from_bytes(p[i:j], byteorder="little", signed=False))
    return res, len(p) % 16


def read_file_STE(p):
    res = []

    i = 0
    while i < len(p) - 32:
        res.append(int.from_bytes(p[i: i + 16], byteorder="little", signed=False))
        i += 16
    remainder = len(p) % 16
    remainder = 16 if remainder == 0 else remainder
    res.append(int.from_bytes(p[i: i + remainder], byteorder="little", signed=False))
    res.append(int.from_bytes(p[i + remainder: i + remainder + 16], byteorder="little", signed=False))
    return res, remainder % 16


def write_file(f, res, padding=False):
    for num in res[:-1]:
        bin_num = num.to_bytes(16, byteorder='little')
        f.write(bin_num)
    num = res[-1]
    bin_num = num.to_bytes(16, byteorder='little')
    if padding:
        bin_num = bin_num.replace(b"\x00", b"")
    f.write(bin_num)


def write_file_STE(f, res, remainder):
    for num in res[:-2]:
        bin_num = num.to_bytes(16, byteorder='little')
        f.write(bin_num)
    num = res[-2]
    remainder = 16 if remainder == 0 else remainder
    bin_num = num.to_bytes(remainder, byteorder='little')
    f.write(bin_num)
    num = res[-1]
    bin_num = num.to_bytes(16, byteorder='little')
    f.write(bin_num)


def EN_ECB_PAD(messages, remainder, keys):
    num_keys = str2num(keys)

    if remainder != 0:
        temp = messages[-1]
        temp = temp.to_bytes(16, byteorder='little')
        messages[-1] = int.from_bytes(temp, byteorder="little", signed=False)
    Sm4 = sm4(num_keys)
    res = []
    for message in messages:
        res.append(Sm4.encryption(message))
    return res


def DE_ECB_PAD(messages, remainder, keys):
    num_keys = str2num(keys)

    Sm4 = sm4(num_keys)
    res = []
    for message in messages:
        res.append(Sm4.decryption(message))
    # write_file(target_path, res, True)
    return res


def EN_CBC_PAD(messages, remainder, keys):
    IV = random.randint(0, 2 ** 128 - 1)
    num_keys = str2num(keys)
    if remainder != 0:
        temp = messages[-1]
        temp = temp.to_bytes(16, byteorder='little')
        messages[-1] = int.from_bytes(temp, byteorder="little", signed=False)
    Sm4 = sm4(num_keys)
    res = [IV]
    for message in messages:
        res.append(Sm4.encryption(message ^ res[-1]))
    # write_file(target_path, res)
    return res


def DE_CBC_PAD(messages, remainder, keys):
    num_keys = str2num(keys)
    # messages, remainder = read_file(file_path)
    Sm4 = sm4(num_keys)
    res = []
    for i, message in enumerate(messages[1:]):
        res.append(Sm4.decryption(message) ^ messages[i])
    # write_file(target_path, res, True)
    return res


def EN_ECB_STE(messages, remainder, keys):
    num_keys = str2num(keys)

    Sm4 = sm4(num_keys)
    res=[]
    for message in messages[:-1]:
        res.append(Sm4.encryption(message))
    if remainder == 0:
        res.append(Sm4.encryption(messages[-1]))
    else:
        inv_remainder = 16 - remainder
        temp = res[-1]
        temp_high = temp >> (inv_remainder * 8)
        temp_low = (temp & (2 ** (inv_remainder * 8) - 1))
        res[-1] = temp_high
        temp_low = temp_low << (remainder * 8)
        ls_c = Sm4.encryption(temp_low ^ messages[-1])
        res.append(ls_c)
    # write_file_STE(target_path, res, remainder)
    return res, remainder


def DE_ECB_STE(messages, remainder, keys):
    num_keys = str2num(keys)
    Sm4 = sm4(num_keys)
    # messages, remainder = read_file_STE(file_path)
    res = []
    for message in messages[:-2]:
        res.append(Sm4.decryption(message))
    temp = Sm4.decryption(messages[-1])
    inv_remainder = 16 - remainder
    temp_high = temp >> (remainder * 8)
    temp_low = (temp & (2 ** (remainder * 8) - 1))
    temp = messages[-2]
    temp = (temp << (inv_remainder * 8)) ^ temp_high
    temp = Sm4.decryption(temp)
    res.append(temp)
    res.append(temp_low)
    # write_file(target_path, res, True)
    return res, remainder


def EN_CBC_STE(messages, remainder, keys):
    num_keys = str2num(keys)

    Sm4 = sm4(num_keys)
    IV = random.randint(0, 2 ** 128 - 1)
    res = [IV]
    for message in messages[:-1]:
        res.append(Sm4.encryption(message ^ res[-1]))
    if remainder == 0:
        res.append(Sm4.encryption(messages[-1] ^ res[-1]))
    else:
        inv_remainder = 16 - remainder
        temp = res[-1]
        temp_high = temp >> (inv_remainder * 8)
        temp_low = (temp & (2 ** (inv_remainder * 8) - 1))
        res[-1] = temp_high
        temp_low = temp_low << (remainder * 8)
        ls_c = Sm4.encryption(temp_low ^ messages[-1])
        res.append(ls_c)
    # write_file_STE(target_path, res, remainder)
    return res, remainder


def DE_CBC_STE(messages, remainder, keys):
    num_keys = str2num(keys)
    # messages, remainder = read_file_STE(file_path)
    Sm4 = sm4(num_keys)
    res = []
    for i, message in enumerate(messages[1:-2]):
        res.append(Sm4.decryption(message) ^ messages[i])
    temp = Sm4.decryption(messages[-1])
    inv_remainder = 16 - remainder
    temp_high = temp >> (remainder * 8)
    temp_low = (temp & (2 ** (remainder * 8) - 1))
    temp = messages[-2]
    temp = (temp << (inv_remainder * 8)) ^ temp_high
    temp = Sm4.decryption(temp) ^ messages[-3]
    res.append(temp)
    res.append(temp_low)
    # write_file(target_path, res, True)
    return res, remainder


if __name__ == "__main__":
    EN_CBC_PAD("1.txt", "encryption4.bin", "acacaacz")

    DE_CBC_STE("encryption4.bin", "res4.txt", "acacaacz")
