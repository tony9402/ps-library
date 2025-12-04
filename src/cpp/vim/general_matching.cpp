/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/15737
 * Test : Accepted
 * Last Updated : 2023.05.23 05:08 AM (KST)
 * Tag : general_matching, gm
 */
[[graph]]

struct GeneralMatching {
    int N, cnt;
    Graph<int> G;

    vector<int> par, visited, prv, match, chk;
    queue<int> Q;

    GeneralMatching(Graph<int> G): G(G) { 
        N = (int)G.size() - 1;
        cnt = 0;
        par = match = prv = visited = vector<int>(N + 1);
    }

    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    int lca(int u, int v) {
        ++cnt;
        while(visited[u] != cnt) {
            if(u) {
                visited[u] = cnt;
                u = find(prv[match[u]]);
            }
            swap(u, v);
        }
        return u;
    }
    void blossom(int u, int v, int root) {
        while(find(u) != root) {
            prv[u] = v;
            par[u] = par[match[u]] = root;
            v = match[u];
            if(chk[v] & 1) {
                Q.push(v);
                chk[v] = 2;
            }
            u = prv[v];
        }
    }
    bool argument(int start) {
        iota(par.begin(), par.end(), 0);
        chk = vector<int>(N + 1, 0);
        queue<int> Q({start}); chk[start] = 2;
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for(int nxt : G[cur]) {
                if(chk[nxt] == 0) {
                    prv[nxt] = cur;
                    chk[nxt] = 1;
                    Q.push(match[nxt]);
                    chk[match[nxt]] = 2;
                    if(!match[nxt]) {
                        while(cur) {
                            cur = match[prv[nxt]];
                            match[nxt] = prv[nxt];
                            match[match[nxt]] = nxt;
                            nxt = cur;
                        }
                        return true;
                    }
                }
                else if(chk[nxt] == 2) {
                    int l = lca(cur, nxt);
                    blossom(cur, nxt, l);
                    blossom(nxt, cur, l);
                }
            }
        }
        return false;
    }
    int go() {
        int ret = 0;
        for(int i = 1; i <= N; ++i) {
            if(!match[i]) ret += argument(i);
        }
        return ret;
    }
};
