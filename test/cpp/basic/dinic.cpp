#include<bits/stdc++.h>

using namespace std;

[[dinic]]
Dinic flow;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    flow.init(2000);
    int N, M, K; cin >> N >> M >> K;
    flow.addEdge(flow.src, flow.asrc, K);
    for(int i = 0; i < N; ++i) {
        int w; cin >> w;
        for(int j = 0; j < w; ++j) {
            int c; cin >> c;
            flow.addEdge(i, c + 999, 1);
        }
        flow.addEdge(flow.src, i, 1);
        flow.addEdge(flow.asrc, i, 1);
    }
    for(int i = 0; i < M; ++i) flow.addEdge(i + 1000, flow.snk, 1);
    cout << flow.Flow(flow.src, flow.snk);

    return 0;
}