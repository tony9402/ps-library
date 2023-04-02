#include<bits/stdc++.h>

using namespace std;

[[2d_segment_tree]]
template<typename T> T Segment2D<T>::merge(T a, T b) { return a + b; }

Segment2D<long long> tree;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q; cin >> N >> Q;
    tree.setSize(N, N);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j) {
            long long x; cin >> x;
            tree.putItem(i, j, x);
        }
    }
    tree.build();
    
    while(~--Q) {
        int t; cin >> t;
        if(t == 1) {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            cout << tree.query(y1 - 1, x1 - 1, y2 - 1, x2 - 1) << '\n';
        }
        else {
            int y, x;
            long long v;
            cin >> y >> x >> v;
            tree.update(y - 1, x - 1, v);
        }
    }

    return 0;
}