from AES import *

"""
明文输入改变1位，密文输出平均改变多少位？
"""
def count_differences(str1, str2):
    """ 计算两个字符串之间不同字符的数量。 """
    return sum(c1 != c2 for c1, c2 in zip(str1, str2))


def test_input_changes_m(initial_string):
    """统计密文修改"""
    total_differences = 0
    total_tests = 0
    key = '00012001710198aeda79171460153594'

    for i in range(len(initial_string)):
        for hex_digit in '0123456789abcdef':
            # 一次只改变一个字符
            modified_string = initial_string[:i] + hex_digit + initial_string[i + 1:]

            # 对两个字符串应用'encode'函数
            encoded_initial = encode(key, initial_string)
            encoded_modified = encode(key, modified_string)

            # 计算输出中的差异
            total_differences += count_differences(encoded_initial, encoded_modified)
            total_tests += 1

    return total_differences / total_tests


# 生成初始的128位16进制字符串
initial_hex_string = '0001000101a198afda78173486153566'

# 计算输出变化的平均位数
average_changes = test_input_changes_m(initial_hex_string)
print("在输入修改一位的情况下，输出的平均位数变化是:", average_changes)
