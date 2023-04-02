#include<bits/stdc++.h>

using namespace std;

[[graph]]
[[dijkstra]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, V; cin >> N >> M >> V;
    Graph<pair<int, long long>> G(N);
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G.addEdge(u, {v, w});
    }
    Dijkstra<long long> dijk(G);
    auto result = dijk.dijkstra(V);
    for(int i = 1; i <= N; ++i) {
        if(result[i] == dijk.INF) cout << "INF\n";
        else cout << result[i] << '\n';
    }

    return 0;
}