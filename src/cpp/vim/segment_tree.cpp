/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/2042
 * Test : Accepted
 * Last Updated : 2023.04.01 09:57 PM (KST)
 * Tag : segment, segtree
 */
template<typename T>
struct Segment {
    vector<T> tree;
    int siz;

    Segment(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree = vector<T>(siz << 1);
    }
    void update(int idx, T data) {
        tree[idx += siz] = data;
        while(idx >>= 1) tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }
    T query(int l, int r, int s, int e, int pos) {
        if(s <= l && r <= e) return tree[pos];
        if(e <  l || r <  s) return 0;
        int mid = (l + r) / 2;
        return merge(query(l, mid, s, e, pos << 1) , query(mid + 1, r, s, e, pos << 1 | 1));
    }
    T query(int s, int e) { return query(0, siz - 1, s, e, 1); }
    T merge(T a, T b) {
        return a + b;
    }
};