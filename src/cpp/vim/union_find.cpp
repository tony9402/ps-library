/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1717
 * Test : Accepted
 * Last Updated : 2023.04.01 10:47 PM (KST)
 * Tag : uf, unionfind
 */
struct UnionFind {
    vector<int> uf, siz;
    UnionFind(int N) {
        uf.resize(N, -1);
        siz.resize(N, 1);
    }
    int find(int x) { return uf[x] < 0 ? x : uf[x] = find(uf[x]); }
    bool same(int a, int b) { return find(a) == find(b); }
    bool merge(int a, int b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        uf[b] = a;
        siz[a] += siz[b];
        return true;
    }
};