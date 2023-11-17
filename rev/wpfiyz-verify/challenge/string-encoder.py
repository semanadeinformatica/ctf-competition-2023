#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from random import randint

str_to_compile = "SINFCTF2023{m4ybe_we_sh0uld_no7_u5e_7his_auth3nt1c4tor}"
mask = [randint(-128, 127) for _ in range(len(str_to_compile) + 1)]
alist = []
alen = len(str_to_compile) + 1

print('  char mask[] = {', end='')
for i, num in enumerate(mask):
    if i != 0:
        print(', ', end='')
    print(num, end='')
print('};')

for i, c in enumerate(str_to_compile):
    alist.append((ord(c) - 20 * i) % 128)
alist += [(-20 * (i + 1)) % 128]
    
for i, a in enumerate(alist):
    alist[(i) % alen] = (alist[(i) % alen] ^ mask[i])

last_a = alist[0]
for i, a in enumerate(alist[1:]):
    alist[i] = (last_a ^ (a - 23) + 128) % 256 - 128
    last_a = a
#alist[-1] = (last_a ^ -23 + 128) % 256 - 128

print('char S01[] = {', end='')
for i, a in enumerate(alist):
    if i != 0:
        print(', ', end='')
    print(a, end='')
print('};')