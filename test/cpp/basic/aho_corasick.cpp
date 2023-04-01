#include<bits/stdc++.h>

using namespace std;

[[aho_corasick]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    AhoCorasick aho;
    for(int i = 0; i < N; ++i) {
        string S; cin >> S;
        aho.insert(S);
    }
    aho.build();
    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        string S; cin >> S;
        if(aho.find(S)) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}