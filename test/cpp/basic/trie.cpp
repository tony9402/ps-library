#include<bits/stdc++.h>

using namespace std;

[[trie]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    while(~--T) {
        int N; cin >> N;
        bool answer = false;
        for(int i = 0; i < N; ++i) {
            string S; cin >> S;
            answer |= Trie::insert(S);
        }
        cout << (answer ? "NO" : "YES") << '\n';
        Trie::clear();
    }
    return 0;
}