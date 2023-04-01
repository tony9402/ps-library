#include<bits/stdc++.h>

using namespace std;

[[range_fenwick_tree]]
FenwickRU<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    tree.setSize(N);
    for (int i = 1; i <= N; ++i) {
        long long x; cin >> x;
        tree.putItem(i, x);
    }
    for (int i = 0; i < M + K; i++) {
        long long a, b, c, d; cin >> a >> b >> c;
        if(a == 1) {
            cin >> d;
            tree.update(b,c,d);
        }
        else cout << tree.query(b, c) << '\n';
    }
}