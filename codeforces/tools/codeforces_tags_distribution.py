import json
import operator

# Original version by tau0 on codeforces
# Go the URL below on your browser and download the file to the same directory as this script
# https://codeforces.com/api/problemset.problems

data = json.load(open("problemset.problems"))

counter = dict()
problems = data["result"]["problems"]
for problem in problems:
    if "tags" in problem:
        for tag in problem["tags"]:
            if not tag in counter:
                counter[tag] = 0
            counter[tag] += 1
            

sorted_x = sorted(counter.items(), key=operator.itemgetter(1), reverse=True)

for line in sorted_x:
    print(line[0] + ' ' + str(line[1]))