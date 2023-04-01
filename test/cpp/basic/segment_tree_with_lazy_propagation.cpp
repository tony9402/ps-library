#include<bits/stdc++.h>

using namespace std;

[[segment_tree_with_lazy_propagation]]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M, K; cin >> N >> M >> K;
    SegmentLazy<long long> tree(N);
    for(int i = 0; i < N; ++i) {
        long long x; cin >> x;
        tree.putItem(i, x);
    }
    tree.build();
    for(int i = 0; i < M + K; ++i){
        long long a, b, c, d; cin >> a >> b >> c;
        --b; --c;
        if(a == 1) {
            cin >> d;
            tree.update(b, c, d);
        }
        else cout << tree.query(b, c) << '\n';
    }
    return 0;
}