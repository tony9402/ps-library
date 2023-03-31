/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/11377
 * Test : Accepted
 * Last Updated : 2023.04.01 12:52 AM (KST)
 */
struct Dinic {
    struct Edge {
        int to, c, f;
        Edge* r;
        Edge() { Edge(-1, 0); }
        Edge(int _to, int _c) :to(_to), c(_c), f(0), r(nullptr) { }
        int spare() { return c - f; }
        void setRev(Edge* rev) { r = rev; }
    };

    vector<vector<Edge*>> graph;
    vector<int> level, work;
    int src, snk, asrc, asnk;

    Dinic() { }
    void init(int N) {
        src = N + 1; snk = src + 1; asrc = snk + 1; asnk = asrc + 1;
        N += 5;
        graph.resize(N); level.resize(N); work.resize(N);
    }
    void clear() { graph.clear(); level.clear(); work.clear(); }

    bool bfs(int s, int e) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int t = q.front(); q.pop();

            for (auto i : graph[t]) {
                if (i->spare() > 0 && level[i->to] == -1) {
                    level[i->to] = level[t] + 1;
                    q.push(i->to);
                }
            }
        }
        return level[e] != -1;
    }

    int dfs(int s, int e, int f) {
        if (s == e)return f;

        for (int& i = work[s]; i < (int)graph[s].size(); i++) {
            Edge* now = graph[s][i];
            if (level[now->to] == level[s] + 1 && now->spare() > 0) {
                int ret = dfs(now->to, e, min(f, now->spare()));
                if (ret > 0) {
                    now->f += ret;
                    now->r->f -= ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    int Flow(int s, int e) {
        int flow = 0;
        while (bfs(s, e)) {
            fill(work.begin(), work.end(), 0);
            while (1) {
                int ret = dfs(s, e, 0x3f3f3f3f);
                if (ret == 0)break;
                flow += ret;
            }
        }
        return flow;
    }

    Edge* addEdge(int u, int v, int c, bool directed = true, bool Unique = false) {
        if (Unique) {
            for (auto i : graph[u]) {
                if (i->to == v) {
                    i->c += c;
                    if (!directed)return i;
                    break;
                }
            }
            if (!directed) {
                for (auto i : graph[v]) {
                    if (i->to == u) {
                        i->c += c;
                        return i;
                    }
                }
            }
        }

        Edge* uv = new Edge(v, c);
        Edge* vu = new Edge(u, directed ? 0 : c);
        uv->setRev(vu); vu->setRev(uv);
        graph[u].push_back(uv);
        graph[v].push_back(vu);

        return uv;
    }

    Edge* addLREdge(int u, int v, int lower, int upper) {
        if (lower) {
            addEdge(asrc, v, lower);
            addEdge(u, asnk, lower);
        }

        return addEdge(u, v, upper - lower);
    }
};