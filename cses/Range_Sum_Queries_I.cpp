#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ull unsigned long long

class Node {
    public:
        Node(ull from, ull to) {
            Node::from = from;
            Node::to = to;
            left = nullptr;
            right = nullptr;
        }

        ull val, from, to;
        shared_ptr<Node> left, right;
};

class SegmentTree {
    public:
        SegmentTree(vector<ull> v) {
            root = build(v, 0, v.size() - 1);
        }

        shared_ptr<Node> build(const vector<ull>& v, ull from, ull to) {
            if (from > to)
                return nullptr;
            shared_ptr<Node> result(new Node(from, to));
            if (from == to)
                result->val = v[from];
            else {
                ull m = (from + to) / 2;
                result->left = build(v, from, m);
                result->right = build(v, m + 1, to);
                if (result->left != nullptr)
                    result->val += result->left->val;
                if (result->right != nullptr)
                    result->val += result->right->val;
            }

            return result;
        }

        ull query(ull from, ull to) {
            return query(root, from, to);
        }

        ull query(shared_ptr<Node> tree, ull from, ull to) {
            if (tree == nullptr) return 0;
            if (from <= tree->from && to >= tree->to) return tree->val;
            if (tree->to < from || to < tree->from) return 0;
            return query(tree->left, from, to) + query(tree->right, from, to);
        }

        shared_ptr<Node> root;
};

int main() {
    uint n, q, l, r;
    cin >> n >> q;
    vector<ull> v(n);
    for (uint d = 0; d < n; d++)
        cin >> v[d];
    SegmentTree st(v);
    for (ull i = 0; i < q; i++) {
        cin >> l >> r;
        cout << st.query(l - 1, r - 1) << eol;
    }
}