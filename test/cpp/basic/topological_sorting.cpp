#include<bits/stdc++.h>

using namespace std;

[[topological_sorting]]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    Graph<int> G(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        G.addEdge(u, v);
    }
    vector<int> answer = topological_sorting(G);
    for(auto it: answer) cout << it << ' ';

    return 0;
}