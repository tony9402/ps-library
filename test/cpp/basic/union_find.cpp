#include<bits/stdc++.h>

using namespace std;

[[union_find]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    UnionFind uf(N + 1);
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        if (a) cout << (uf.same(b, c) ? "YES" : "NO") << '\n';
        else uf.merge(b, c);
    }
    return 0;
}