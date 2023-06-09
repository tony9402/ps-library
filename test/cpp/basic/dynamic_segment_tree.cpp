#include<bits/stdc++.h>

using namespace std;

[[dynamic_segment_tree]]
template<typename T> T DynamicSegment<T>::merge(T a, T b) { return a + b; }
DynamicSegment<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i) {
        long long x; cin >> x;
        tree.update(i, x);
    }
    for(int i = 0; i < M + K; ++i) {
        long long a, b, c; cin >> a >> b >> c;
        if(a == 1) tree.update(b, c);
        else cout << tree.query(b, c) << '\n';
    }
    return 0;
}