/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/9250
 * Test : Accepted
 * Last Updated : 2023.04.02 03:00 AM (KST)
 * Tag : aho-corasick, aho, corasick
 */
struct AhoCorasick {
    struct Trie {
        Trie *nxt[26];
        Trie *fail;
        bool output;

        Trie() {
            for(int i=0;i<26;++i) nxt[i]=nullptr;
            fail=nullptr;
            output=false;
        }
        ~Trie() {
            for(int i=0;i<26;++i) if(nxt[i]) delete nxt[i];
        }
    } *root;
    AhoCorasick() { root = new Trie(); }
    void insert(const string &S) {
        Trie *cur = root;
        int N = (int)S.size();
        for(int i = 0; i < N; ++i) {
            int nxt = S[i] - 'a';
            if(cur->nxt[nxt] == nullptr) cur->nxt[nxt] = new Trie();
            cur = cur->nxt[nxt];
        }
        cur->output=true;
    }
    void build() {
        queue<Trie*> Q;
        root->fail = root;
        Q.push(root);
        while(!Q.empty()) {
            Trie* cur = Q.front(); Q.pop();

            for(int i = 0; i < 26; ++i) {
                Trie *next = cur->nxt[i];
                if(next == nullptr) continue;
                if(cur == root) next->fail = root;
                else {
                    Trie *dst = cur->fail;
                    while(dst != root && dst->nxt[i] == nullptr) dst = dst->fail;
                    if(dst->nxt[i]) dst = dst->nxt[i];
                    next->fail = dst;
                }
                if(next->fail->output) next->output = true;
                Q.push(next);
            }
        }
    }
    bool find(const string &S) {
        Trie *cur = root;
        int N = (int)S.size();
        for(int i = 0; i < N; ++i) {
            int nxt = S[i] - 'a';
            while(cur != root && cur->nxt[nxt] == nullptr) cur = cur->fail;
            if(cur->nxt[nxt]) cur = cur->nxt[nxt];
            if(cur->output) return true;
        }
        return false;
    }
};
