/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/10891
 * Test : Accepted
 * Last Updated : 2025.03.05 08:40 AM (KST)
 * Tag : bcc
 */
[[graph]]

struct BCC {
    int N, dfs_id, bcc_id;
    Graph<int> G;
    vector<int> dfsn;
    vector<vector<pair<int, int>>> bcc;
    vector<int> used;
    stack<pair<int, int>> S;
    bool cactus;
    BCC(Graph<int> &_G):G(_G) {
        N = G.size();
        dfsn.resize(N + 1);
        used.resize(N + 1, -1);
        dfs_id = bcc_id = 0;
        cactus = true;
        for(int i = 1; i <= N; ++i) {
            if(dfsn[i] == 0) dfs(i, 0);
        }
    }

    int dfs(int cur, int prev) {
        int res = dfsn[cur] = ++ dfs_id;
        for(int nxt: G[cur]) {
            if(nxt == prev) continue;
            if(dfsn[cur] > dfsn[nxt]) S.emplace(cur, nxt);
            if(dfsn[nxt] > 0) res = min(res, dfsn[nxt]);
            else {
                int tmp = dfs(nxt, cur);
                res = min(res, tmp);
                if(tmp >= dfsn[cur]) {
                    vector<pair<int, int>> curBCC;
                    int cnt = 0;
                    while(!S.empty() && S.top() != make_pair(cur, nxt)) {
                        curBCC.push_back(S.top());
                        S.pop();
                    }
                    curBCC.push_back(S.top());
                    S.pop();
                    if(curBCC.size() > 1) {
                        for(const auto &[u, v]: curBCC) {
                            if(used[u] == -1) {
                                used[u] = 1;
                                ++cnt;
                            }
                            if(used[v] == -1) {
                                used[v] = 1;
                                ++cnt;
                            }
                        }
                        if(cnt != curBCC.size()) cactus = false;
                    }
                    ++ bcc_id;
                    bcc.push_back(curBCC);
                }
            }
        }
        return res;
    }
    vector<int> cut_vertex() {
        vector<int> cnt(N + 1), last(N + 1, -1);
        for(int i = 0; i < (int)bcc.size(); ++i) {
            for(auto [u, v]: bcc[i]) {
                if(last[u] < i) ++ cnt[u], last[u] = i;
                if(last[v] < i) ++ cnt[v], last[v] = i;
            }
        }
        vector<int> vertex;
        for(int i = 1; i <= N; ++i) {
            if(cnt[i] > 1) vertex.push_back(i);
        }
        return vertex;
    }
    vector<pair<int, int>> cut_edge() {
        vector<pair<int, int>> edges;
        for(int i = 0; i < (int)bcc.size(); ++i) {
            if(bcc[i].size() > 1) continue;
            auto [u, v] = bcc[i][0];
            edges.emplace_back(min(u, v), max(u, v));
        }
        return edges;
    }
};
