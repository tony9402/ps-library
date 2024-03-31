/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/9248
 * Test : Accepted
 * Last Updated : 2023.04.02 01:54 AM (KST)
 * Tag : suffixarray, sa
 */
template<typename T> struct SuffixArray {
    vector<int> pos, sa, lcp;
    int N;
    SuffixArray(const T& S) {
        N = (int)S.size();
        lcp = pos = sa = vector<int>(N);
        vector<int> tmp(N);
        for(int i = 0; i < N; ++i) sa[i] = i, pos[i] = S[i];
        for(int d = 1; ; d <<= 1) {
            function<bool(int, int)> compare = [&](int a, int b) -> bool {
                if(pos[a] != pos[b]) return pos[a] < pos[b];
                if(a + d < N && b + d < N) return pos[a + d] < pos[b + d];
                return a > b;
            };
            sort(sa.begin(), sa.end(), compare);
            for(int i = 1; i < N; ++i) tmp[i] = tmp[i - 1] + compare(sa[i - 1], sa[i]);
            for(int i = 0; i < N; ++i) pos[sa[i]] = tmp[i];
            if(tmp.back() + 1 == N) break;
        }
        // part of LCP
        for(int i = 0, k = 0; i < N; ++i, k = max(k - 1, 0)) {
            if(!pos[i]) continue;
            while(sa[pos[i] - 1] + k < N && sa[pos[i]] + k < N && S[sa[pos[i] - 1] + k] == S[sa[pos[i]] + k]) ++k;
            lcp[pos[i]] = k;
        }
    }
    vector<int> &get_sa() { return sa; }
    vector<int> &get_lcp() { return lcp; }
};