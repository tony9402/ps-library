#include<bits/stdc++.h>

using namespace std;

[[palindrome_tree]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; cin >> S;
    PalindromeTree<long long> tree(303030);
    tree.init(S);
    long long ans = 0;
    for(int i = tree.cnt; i > 2; --i) {
        ans = max<long long>(ans, 1LL * tree[i].len * tree[i].cnt);
        tree[tree[i].suffix_link].cnt += tree[i].cnt;
    }
    cout << ans;

    return 0;
}