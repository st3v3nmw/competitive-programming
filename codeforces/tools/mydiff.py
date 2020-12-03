#!/usr/bin/python3

import sys

ans = open(sys.argv[1], "r").readlines()
stdout = open(sys.argv[2], "r").readlines()
stderr = open(sys.argv[3], "r").readlines()

fails = []
for i in range(len(stdout)):
    if i > len(ans):
        fails.append(('_', stdout[i].strip()))
    if ans[i].strip() != stdout[i].strip():
        fails.append((ans[i].strip(), stdout[i].strip()))

if len(fails) > 0 or len(stdout) == 0:
    print('\33[31m' + "WRONG ANSWER\n", '\x1b[0m')
    for fail in fails:
        print(fail[0], '=>', fail[1])
else:
    print('\33[32m' + 'Testcases Passed!' + '\x1b[0m')

if len(stderr) > 0:
    print('\33[31m' + '\n' + "STDERR" + '\x1b[0m')
    for line in stderr:
        print(line, end="")
