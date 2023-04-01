#include<bits/stdc++.h>

using namespace std;

[[persistent_segment_tree]]
PST<int> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q; cin >> N >> Q;
    const int base = 1000000000;
    tree.setting(base * 2 + 10);
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        tree.update(i, x + base + 1, 1, true);
    }
    for (int i = 0; i < Q; ++i) {
        int l, r, k; cin >> l >> r >> k;
        cout << tree.kth(l - 1, r, k) - base - 1 << '\n';
    }
}