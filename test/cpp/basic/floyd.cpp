#include<bits/stdc++.h>

using namespace std;

[[floyd]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    Floyd<int> G(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G.minEdge(--u, --v, w);
    }
    G.floyd();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(G.INF == G[i][j]) cout<<0<<' ';
            else cout<<G[i][j]<<' ';
        }
        cout<<'\n';
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            auto t = G.GetPath(i, j);
            cout<<(int)t.size();
            for(int k=0;k<(int)t.size();++k){
                cout<<' '<<t[k]+1;
            }
            cout<<'\n';
        }
    }
}