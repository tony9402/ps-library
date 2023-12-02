/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/2252
 * Test : 
 * Last Updated : 2023.11.29 17.40 PM (KST)
 */
[[graph]]

vector<int> topological_sorting(Graph<int> &G) {
    int N = (int)G.size();
    vector<int> ind(N + 1);
    for(int i = 1; i <= N; ++i) {
        for(int nxt : G[i]) {
            ++ ind[nxt];
        }
    }

    queue<int> Q;
    vector<int> res;
    for(int i = 1; i <= N; ++i) {
        if(ind[i] == 0) Q.push(i);
    }
    while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        res.push_back(cur);
        for(int nxt: G[cur]) {
            if (--ind[nxt] == 0) {
                Q.push(nxt);
            }
        }
    } 
    return res;
}