#include<bits/stdc++.h>

using namespace std;

[[splay_tree]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;

        vector<long long> V(N + 1), W;
        for (int i = 1; i <= N; ++i) {
            cin >> V[i];
            W.push_back(V[i]);
        }
        sort(W.begin(), W.end());
        W.erase(unique(W.begin(), W.end()), W.end());

        vector<vector<int>> G(N + 1);
        for (int i = 1; i <= N; ++i) {
            V[i] = lower_bound(W.begin(), W.end(), V[i]) - W.begin();
            G[V[i]].push_back(i);
        }

        int id = 0;

        for (int i = 0; i < (int) G.size(); ++i) {
            for (int x: G[i]) {
                V[x] = ++id;
            }
        }

        SplayTree<long long> tree(N, V);

        for (int i = 1; i <= N; ++i) {
            int x = tree[i];
            cout << x << " ";
            tree.flip(i, x);
        }
        cout << '\n';
    }

    return 0;
}