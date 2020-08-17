from ankipandas import Collection
import networkx as nx
import matplotlib.pyplot as plt
from itertools import permutations

col = Collection("/home/stephen/.local/share/Anki2/", user="Stephen Mwangi")
data = col.notes.to_numpy()[:, 3] # API broken :(, had to downgrade to Anki 2.1.26

color_code, subjects, subjects_rank = {}, {}, {}
subjects_count = {}
with open("color-code.txt", "r") as f:
    lines = f.readlines()
    color_code['default'] = lines[0].split(',')[1].strip()
    for line in lines[1:]:
        d = line.split(',')
        for tag in d[2:]:
            color_code[tag.strip()] = d[1]
            subjects[tag.strip()] = d[0]

G = nx.Graph()
tags, node_sizes, node_colors, size_incr = [], [], [], 3

for ntags in data:
    if 'leech' in ntags:
        ntags.pop(ntags.index('leech'))
    for tag in ntags:
        if tag not in tags:
            tags.append(tag)
            try:
                node_colors.append(color_code[tag])
            except KeyError:
                print(f"Color code for the tag {tag} not found.")
                node_colors.append(color_code['default'])
            G.add_node(tag)
            node_sizes.append(0)
        node_sizes[tags.index(tag)] += size_incr

    p = list(permutations(ntags, 2))
    for pair in p:
        try:
            G[pair[0]][pair[1]]['weight'] += 1
        except KeyError:
            G.add_edge(pair[0], pair[1], weight = 1)

pr = nx.algorithms.link_analysis.pagerank_alg.pagerank(G)
sorted_pr = sorted(pr.items(), key=lambda kv: kv[1], reverse=True)

i, llen, backslash = 0, len(sorted_pr), '\n'
f = open("page-rank.txt", "w")
for i in range(llen):
    try:
        subjects_rank[subjects[sorted_pr[i][0]]] += sorted_pr[i][1] * 1000
        subjects_count[subjects[sorted_pr[i][0]]] += 1
    except KeyError:
        subjects_rank[subjects[sorted_pr[i][0]]] = sorted_pr[i][1] * 1000
        subjects_count[subjects[sorted_pr[i][0]]] = 1
    f.write(f"{i + 1} {sorted_pr[i][0]} {round(sorted_pr[i][1] * 1000, 4)}{backslash if i != llen - 1 else ''}")
    i += 1
for subject in subjects_rank:
    subjects_rank[subject] = round(subjects_rank[subject] / subjects_count[subject], 4)
f.write("\n\nAverages: " + str(sorted(subjects_rank.items(), key=lambda kv: kv[1], reverse=True)))
f.close()

fig = plt.gcf()
fig.set_size_inches(13.66, 6.43)
nx.draw(G, pos = nx.nx_pydot.graphviz_layout(G), node_size = node_sizes, with_labels = True, font_size = 7, node_color = node_colors, edge_color = "gray")
fig.savefig("knowledge-graph.png", dpi=100)
plt.show()