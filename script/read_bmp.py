#!/usr/bin/python
# encoding: utf-8

import sys

def read_smallend(ori):
    res_str = ""
    for i in range(0, len(ori)):
        tmp = hex(ord(ori[i]))
        tmp = tmp[tmp.index("x")+1:]
        res_str = tmp.rjust(2, "0") + res_str
    return int(res_str, 16)

def main():
    in_file = open(sys.argv[1], 'rb')
    chunk = in_file.read(1)
    print "%c" % (chunk)
    chunk = in_file.read(1)
    print "%c" % (chunk)

    chunk = in_file.read(4)
    file_size = read_smallend(chunk)
    print "file size: %d" % (file_size)

    # empty for 4 bytes
    in_file.seek(4, 1)

    chunk = in_file.read(4)
    bmp_offset = read_smallend(chunk)
    print "bmp offset: %d" % (bmp_offset)

    in_file.seek(14, 1)
    chunk = in_file.read(2)
    pixel_size = read_smallend(chunk)
    print "pixel size: %d" % (pixel_size)

    in_file.seek(bmp_offset)
    for i in range(0, 4):
        chunk = in_file.read(1)

    #start read bmp

    in_file.close()

if __name__ == '__main__':
    main()
