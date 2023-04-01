/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/10066
 * Test : Accepted
 * Last Updated : 2023.04.02 02:55 AM (KST)
 */
template<typename T = int> struct PalindromeTree {
    struct Node {
        int len, suffix_link;
        T cnt;
        map<char, int> nxt;
        
        Node() : Node(0, 0) { }
        Node(int _len, int _link) {
            len = _len; suffix_link = _link;
            cnt = T();
        }
    };

    vector<Node> tree;
    int cnt, last_suffix;

    PalindromeTree(int N) {
        tree.resize(N);
        cnt = last_suffix = 2;
        tree[1] = Node(-1, 1);
        tree[2] = Node(0, 1);
    }
    void init(const string &S) {
        auto chk = [&](int idx, int cur) {
            return idx - tree[cur].len - 1 >= 0 && S[idx - tree[cur].len - 1] == S[idx];
        };
        for(int i = 0; i < (int)S.size(); ++i) {
            int cur = last_suffix;
            while(!chk(i, cur)) cur = tree[cur].suffix_link;
            if(tree[cur].nxt.count(S[i])) {
                last_suffix = tree[cur].nxt[S[i]];
                ++ tree[last_suffix].cnt;
                continue;
            }
            last_suffix = tree[cur].nxt[S[i]] = ++cnt;
            int nxt = cnt;
            tree[nxt].len = tree[cur].len + 2;
            ++ tree[nxt].cnt;
            if(tree[nxt].len == 1) {
                tree[nxt].suffix_link = 2;
                continue;
            }
            while(cur > 1) {
                cur = tree[cur].suffix_link;
                if(chk(i, cur)) {
                    tree[nxt].suffix_link = tree[cur].nxt[S[i]];
                    break;
                }
            }
        }
    }
    Node& operator[](const int &idx) { return tree[idx]; }
};