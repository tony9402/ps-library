/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/12424
 * Test : Accepted
 * Last Updated : 2025.12.01 06:57 AM (KST)
 * Tag : mcmf
 */
template<typename FlowType, typename DistType>
struct MinCostMaxFlow {
    struct Edge {
        int edge_id;
        int node_idx;
        FlowType cost;
        FlowType flow;
        DistType dist;
        int rev;
        Edge(int _edge_id, int _node_idx, FlowType _cost, DistType _dist, int _rev):edge_id(_edge_id),node_idx(_node_idx),cost(_cost),flow(0),dist(_dist),rev(_rev) { }
        FlowType spare() { return cost - flow; }
    };

    vector<Edge> edges;
    vector<vector<int>> G;
    vector<DistType> dist;
    vector<int> work, visited, InQ;

    int src, snk, N;
    FlowType INF_FLOW;
    DistType INF_DIST;

    MinCostMaxFlow(int _N) { 
        src = _N + 1;
        snk = src + 1;
        N = snk;

        INF_FLOW = numeric_limits<FlowType>::max() / 2;
        INF_DIST = numeric_limits<DistType>::max() / 2;

        dist.resize(N + 1, INF_DIST);
        G.resize(N + 1);
        work.resize(N + 1);
        visited.resize(N + 1);
        InQ.resize(N + 1);
    }
    FlowType dfs(int s, int e, FlowType f) {
        visited[s] = 1;
        if(s == e) return f;
        for(int &i = work[s]; i < (int)G[s].size(); ++i) {
            Edge &nxt = edges[G[s][i]];
            if(visited[nxt.node_idx]) continue;
            if(nxt.spare() > 0 && dist[nxt.node_idx] == dist[s] + nxt.dist) {
                FlowType ret = dfs(nxt.node_idx, e, min(f, nxt.spare()));
                if(ret != 0) {
                    nxt.flow += ret;
                    edges[nxt.rev].flow -= ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    // SPFA slf swap
    bool spfa(int s, int e) {
        fill(dist.begin(), dist.end(), INF_DIST);
        dist[s] = 0;
        deque<int> dq; dq.push_back(s);
        InQ[s] = 1;

        while(!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            InQ[cur] = 0;
            for(const int &x: G[cur]) {
                Edge &edge = edges[x];
                if(edge.spare() > 0 && dist[edge.node_idx] > dist[cur] + edge.dist) {
                    dist[edge.node_idx] = dist[cur] + edge.dist;
                    if(InQ[edge.node_idx] == 0) {
                        InQ[edge.node_idx] = 1;
                        if(!dq.empty() && dist[edge.node_idx] > dist[dq.front()]) {
                            dq.push_back(edge.node_idx);
                        }
                        else {
                            dq.push_front(edge.node_idx);
                            if(dist[dq.front()] > dist[dq.back()]) swap(dq.front(), dq.back());
                        }
                    }
                }
            }
        }
        return dist[e] != INF_DIST;
    }
    bool update() {
        DistType mn = INF_DIST;
        for(i32 i = 0; i <= N; ++i) {
            if(visited[i] == 0) continue;
            for(i32 j: G[i]) {
                if(edges[j].spare() > 0 && visited[edges[j].node_idx] == 0) {
                    mn = min(mn, dist[i] - dist[edges[j].node_idx] + edges[j].dist);
                }
            }
        }
        if(mn == INF_DIST) return false;
        for(i32 i = 0; i <= N; ++i) {
            if(visited[i] == 0) dist[i] += mn;
        }
        return true;
    }
    pair<DistType, FlowType> flow(int s, int e) {
        pair<DistType, FlowType> ret;
        spfa(s, e);
        do {
            fill(work.begin(), work.end(), 0);
            fill(visited.begin(), visited.end(), 0);
            while(true) {
                FlowType now = dfs(s, e, INF_FLOW);
                if(now == 0) break;
                ret.first += now * dist[e];
                ret.second += now;
                fill(visited.begin(), visited.end(), 0);
            }
        } while(update());
        return ret;
    }
    pair<DistType, FlowType> flow() { return flow(src, snk); }
    // addEdge
    void addEdge(int u, int v, FlowType _cost, DistType _dist) {
        int a = (int)edges.size();
        int b = a + 1;

        Edge uv = Edge(a, v, _cost, _dist, b);
        Edge vu = Edge(b, u, 0, -_dist, a);

        edges.push_back(uv);
        edges.push_back(vu);

        G[u].push_back(a);
        G[v].push_back(b);
    }
};
