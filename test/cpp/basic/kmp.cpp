#include<bits/stdc++.h>

using namespace std;

[[kmp]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; getline(cin, S);
    string T; getline(cin, T);
    KMP<string> kmp;
    auto it = kmp.kmp(S, T);
    cout << it.size() << '\n';
    for(auto x : it) cout << x + 1 << ' ';

    return 0;
}