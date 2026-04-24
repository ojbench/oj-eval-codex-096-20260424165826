#include <bits/stdc++.h>
using namespace std;

// Build tree from extended preorder where -1 indicates null.
// We only need parent and depth for each value.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    if (!(cin >> Q)) return 0;
    vector<pair<int,int>> queries(Q);
    for (int i = 0; i < Q; ++i) cin >> queries[i].first >> queries[i].second;

    // Read the remainder of the line as the preorder sequence (could be many numbers)
    vector<int> pre;
    int x;
    while (cin >> x) pre.push_back(x);

    // Build using an index passed by reference via lambda
    unordered_map<int,int> parent; // value -> parent value (0 if root)
    unordered_map<int,int> depth;  // value -> depth
    parent.reserve(1024);
    depth.reserve(1024);

    function<void(int,int,int&,int)> build = [&](int par, int dep, int& idx, int n){
        if (idx >= n) return; // safety
        int val = pre[idx++];
        if (val == -1) return; // null
        parent[val] = par;
        depth[val] = dep;
        // left
        build(val, dep+1, idx, n);
        // right
        build(val, dep+1, idx, n);
    };

    int idx = 0;
    build(0, 0, idx, (int)pre.size());

    for (auto &qr : queries) {
        int a = qr.first, b = qr.second;
        auto ita = depth.find(a), itb = depth.find(b);
        if (ita == depth.end() || itb == depth.end()) {
            cout << 0 << '\n';
            continue;
        }
        int da = ita->second, db = itb->second;
        int pa = parent[a], pb = parent[b];
        cout << ((da == db && pa != 0 && pb != 0 && pa != pb) ? 1 : 0) << '\n';
    }

    return 0;
}

