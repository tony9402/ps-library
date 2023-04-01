#include<bits/stdc++.h>

using namespace std;

[[hashing]]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, K; cin >> N >> K;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    Hashing<31, 998244353> H;
    reverse(V.begin(), V.end());
    for(int i = 0; i < N - 1; ++i) V.emplace_back(V[i]);
    H.build(V);

    function<bool(int,int)> cmp = [&](int a, int b) -> bool {
        int l = 0, r = N - 1;
        while(l < r) {
            int mid = (l + r + 1) / 2;
            long long h1 = H.get(a + 1, a + mid), h2 = H.get(b + 1, b + mid);
            if(h1 == h2) l = mid;
            else r = mid - 1;
        }
        if(l == N - 1) return false;
        return V[a + l] < V[b + l];
    };
    vector<int> idx(N-1); iota(idx.begin(), idx.end(), 1);
    stable_sort(idx.begin(), idx.end(), cmp);
    for(int i = 0; i < N; ++i) cout << V[idx[K - 1] + i] << ' ';

    return 0;
}