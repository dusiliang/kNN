#!/usr/bin/python
# encoding: utf-8

import sys


def main():
    in_file = open(sys.argv[1], 'rb')
    chunk = in_file.read(1)
    print "%c" % (chunk)
    chunk = in_file.read(1)
    print "%c" % (chunk)

    file_size_str = ""
    for i in range(0,4):
        chunk = in_file.read(1)
        tmp = hex(ord(chunk))
        tmp = tmp[tmp.index("x")+1:]
        file_size_str = tmp.rjust(2, "0") + file_size_str
    file_size = int(file_size_str, 16)
    print file_size_str, file_size, file_size/1024
    in_file.close()

if __name__ == '__main__':
    main()
