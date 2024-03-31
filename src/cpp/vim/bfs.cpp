[[graph]]

/*
 * Problem for Testing Template :
 * Test : 
 * Last Updated : 
 * Tag : bfs
 */
struct BFS {
    Graph<int> G;
    BFS(const Graph<int> _G):G(_G) { }
    vector<int> operator()(int S) {
        vector<int> D(G.size(), -1);
        queue<int> Q({S});
        D[S] = 0;
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for(int nxt: G[cur]) {
                if(D[nxt] != -1) continue;
                D[nxt] = D[cur] + 1;
                Q.emplace(nxt);
            }
        }
        return D;
    }
};