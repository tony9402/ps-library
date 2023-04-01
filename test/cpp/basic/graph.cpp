#include<bits/stdc++.h>

using namespace std;

[[graph]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, V; cin >> N >> M >> V;
    Graph<int> G(N);
    for(int i = 0; i < M; ++i){
        int u, v; cin >> u >> v;
        G.addEdge(u, v); G.addEdge(v, u);
    }
    for(int i = 1; i <= N; ++i) sort(G[i].begin(), G[i].end());

    vector<int> dfs_visited(N + 1);
    function<void(int)> dfs = [&](int cur) -> void {
        cout << cur << ' ';
        dfs_visited[cur] = 1;
        for(int nxt : G[cur]) if(!dfs_visited[nxt]) dfs(nxt);
    };
    dfs(V); cout << '\n';
    vector<int> bfs_visited(N + 1);
    function<void(int)> bfs = [&](int S) -> void {
        queue<int> Q({S});
        bfs_visited[S] = 1;
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            cout << cur << ' ';
            for(int nxt : G[cur]) {
                if(bfs_visited[nxt]) continue;
                Q.emplace(nxt);
                bfs_visited[nxt] = 1;
            }
        }
    };
    bfs(V);

    return 0;
}