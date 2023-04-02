#include<bits/stdc++.h>

using namespace std;

[[heavy_light_decomposition]]

template<typename T> T Segment<T>::merge(T a, T b) { return max<T>(a, b); }

void HLD::update(int a, int b) {
    seg.update(a, b);
}

int HLD::query(int s, int e) {
    int ret = 0;
    while(top[s] != top[e]) {
        if(dep[top[s]] < dep[top[e]]) swap(s, e);
        ret = max(ret, seg.query(in[top[s]], in[s]));
        s = par[top[s]];
    }
    if(in[s] > in[e]) swap(s, e);
    return max(ret, seg.query(in[s] + 1, in[e]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    Graph<int> G(N+1);
    vector<tuple<int,int,int>> edges;
    for(int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G.addEdge(u, v); G.addEdge(v, u);
        edges.emplace_back(u, v, w);
    }
    HLD hld(G);
    hld.dfs(); hld.dfs2();
    for(auto &[u, v, w] : edges) {
        if(hld.dep[u] < hld.dep[v]) swap(u, v);
        hld.update(hld.in[u], w);
    }
    int Q; cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int cmd, a, b; cin >> cmd >> a >> b;
        if(cmd == 1) {
            auto &[u, v, w] = edges[a - 1];
            hld.update(hld.in[u], w = b);
        }
        else cout << hld.query(a, b) << '\n';
    }

    return 0;
}