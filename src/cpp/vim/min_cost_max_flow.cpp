/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/3640
 * Test : Accepted
 * Last Updated : 2024.05.23 12:57 PM (KST)
 * Tag : mcmf, mincostmaxflow
 */
template<typename T>
struct MinCostMaxFlow {
    struct Edge {
        int edge_id;
        int node_idx;
        int cost;
        int flow;
        T dist;
        int rev;
        Edge(int _edge_id, int _node_idx, int _cost, T _dist, int _rev):edge_id(_edge_id),node_idx(_node_idx),cost(_cost),flow(0),dist(_dist),rev(_rev) { }
        int spare() { return cost - flow; }
    };

    vector<Edge> edges;
    vector<vector<int>> G;
    vector<pair<int, int>> par;
    vector<T> dist;

    int src, snk, N;
    T INF;

    MinCostMaxFlow(int _N) { 
        src = _N + 1;
        snk = src + 1;
        N = snk;

        INF = numeric_limits<T>::max();

        G.resize(N + 1);
        par.resize(N + 1, make_pair(-1, -1));
    }
    // SPFA slf swap
    bool spfa(int s, int e) {
        vector<int> InQ(N + 1);
        dist = vector<T>(N + 1, INF);

        dist[s] = 0;
        deque<int> dq; dq.push_back(s);
        InQ[s] = 1;

        while(!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            InQ[cur] = 0;
            for(const int &x: G[cur]) {
                Edge &e = edges[x];
                if(e.spare() > 0 && dist[e.node_idx] > dist[cur] + e.dist) {
                    dist[e.node_idx] = dist[cur] + e.dist;
                    par[e.node_idx] = make_pair(cur, e.edge_id);
                    if(InQ[e.node_idx] == 0) {
                        InQ[e.node_idx] = 1;
                        if(!dq.empty() && dist[e.node_idx] > dist[dq.front()]) {
                            dq.push_back(e.node_idx);
                        }
                        else {
                            dq.push_front(e.node_idx);
                            if(dist[dq.front()] > dist[dq.back()]) swap(dq.front(), dq.back());
                        }
                    }
                }
            }
        }
        return dist[e] != INF;
    }

    // min_cost, max_flow
    pair<T, int> flow_after_spfa(int s, int e) {
        int mn = numeric_limits<int>::max();
        for(int cur = e; cur != s; cur = par[cur].first) {
            mn = min(mn, edges[par[cur].second].spare());
        }
        if(mn == 0) return make_pair<T, int>(-1, -1);
        T min_cost = 0;
        int max_flow = mn;
        for(int cur = e; cur != s; cur = par[cur].first) {
            min_cost += (T)mn * edges[par[cur].second].dist;
            edges[par[cur].second].flow += mn;
            edges[edges[par[cur].second].rev].flow -= mn;
        }
        return make_pair(min_cost, max_flow);
    }
     pair<T, int> flow(int s, int e) {
         pair<T, int> ret;
         while(spfa(s, e)) {
             pair<T, int> cur = flow_after_spfa(s, e);
             if(cur.first == -1) break;
             ret.first += cur.first;
             ret.second += cur.second;
         }
         return ret;
    }

    // addEdge
    void addEdge(int u, int v, int cost, T dist) {
        int a = edges.size();
        int b = a + 1;

        Edge uv = Edge(a, v, cost, dist, b);
        Edge vu = Edge(b, u, 0, -dist, a);

        edges.push_back(uv);
        edges.push_back(vu);

        G[u].push_back(a);
        G[v].push_back(b);
    }

    pair<T, int> flow() { return flow(src, snk); }
};
