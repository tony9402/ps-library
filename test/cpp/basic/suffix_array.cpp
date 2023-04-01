#include<bits/stdc++.h>

using namespace std;

[[suffix_array]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; cin >> S;
    SuffixArray sa(S);
    for(auto it: sa.get_sa()) cout << it + 1 << ' '; cout << '\n';
    auto lcp = sa.get_lcp();
    cout << "x ";
    for(int i = 1; i < (int)lcp.size(); ++i) cout << lcp[i] << ' ';

    return 0;
}