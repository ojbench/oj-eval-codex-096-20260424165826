// Portable C++11 implementation without non-standard headers
#include <iostream>
#include <vector>
#include <cstring>
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

    // Use fixed-size arrays for parent/depth since 1..1000
    const int MAXV = 1005;
    static int parent[MAXV];
    static int depth[MAXV];
    for (int i = 0; i < MAXV; ++i) { parent[i] = -1; depth[i] = -1; }

    // Recursive builder
    struct Builder {
        const vector<int>& pre;
        int n;
        int idx;
        int* parent;
        int* depth;
        Builder(const vector<int>& pre_, int* p_, int* d_) : pre(pre_), n((int)pre_.size()), idx(0), parent(p_), depth(d_) {}
        void build(int par, int dep) {
            if (idx >= n) return;
            int val = pre[idx++];
            if (val == -1) return;
            parent[val] = par;
            depth[val] = dep;
            build(val, dep+1);
            build(val, dep+1);
        }
    };

    Builder B(pre, parent, depth);
    B.build(-1, 0);

    for (auto &qr : queries) {
        int a = qr.first, b = qr.second;
        // If a or b not present in tree
        if (a <= 0 || a >= MAXV || b <= 0 || b >= MAXV || depth[a] == -1 || depth[b] == -1) {
            cout << 0 << '\n';
            continue;
        }
        int da = depth[a], db = depth[b];
        int pa = parent[a], pb = parent[b];
        cout << ((da == db && pa != -1 && pb != -1 && pa != pb) ? 1 : 0) << '\n';
    }

    return 0;
}
