ans = open("ans.txt", "r").readlines()
out = open("out.txt", "r").readlines()

for i in range(len(ans)):
    if (ans[i].strip() != out[i].strip()):
        print(i + 1, ans[i].strip(), out[i].strip())