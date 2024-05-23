#include<bits/stdc++.h>

using namespace std;

[[min_cost_max_flow]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    while(cin >> N >> M) {
        MinCostMaxFlow<int> flow(2 * N + 1);
        flow.addEdge(1, N + 1, 2, 0);
        flow.addEdge(N, N + N, 2, 0);
        for(int i = 2; i < N; ++i) flow.addEdge(i, N + i, 1, 0);
        for(int i = 0; i < M; ++i) {
            int u, v, w; cin >> u >> v >> w;
            flow.addEdge(N + u, v, 1, w);
        }
        flow.addEdge(flow.src, 1, 2, 0);
        flow.addEdge(N + N, flow.snk, 2, 0);
        auto [ans, _] = flow.flow();
        cout << ans << '\n';
    }
    return 0;
}
