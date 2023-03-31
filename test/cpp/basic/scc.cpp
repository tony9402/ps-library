#include<bits/stdc++.h>

using namespace std;

[[scc]]
SCC scc;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    scc.setSize(N);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        scc.addEdge(a, b);
    }

    scc.run();
    cout << scc.getSize() << '\n';
    for(auto &i: scc.scc) sort(i.begin(), i.end());
    sort(scc.scc.begin(), scc.scc.end());

    for(auto &i : scc.scc) {
        for(auto &j : i) cout << j << ' ';
        cout << -1 << '\n';
    }

    return 0;
}