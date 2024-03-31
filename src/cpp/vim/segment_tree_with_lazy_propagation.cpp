/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/10999
 * Test : Accepted
 * Last Updated : 2023.04.01 09:56 PM (KST)
 * Tag : seglazy, segmentlazy
 */
template<typename T>
struct SegmentLazy {
    vector<T> tree, lazy;
    int siz;

    SegmentLazy(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        lazy = tree = vector<T>(siz << 1);
    }
    void putItem(int idx, T data) { tree[idx + siz] = data; }
    void build() {
        for(int i = siz - 1; i; --i) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    void propagate(int l, int r, int pos) {
        if(!lazy[pos]) return;
        if(l != r) {
            lazy[pos << 1] = merge(lazy[pos << 1], lazy[pos]);
            lazy[pos << 1 | 1] = merge(lazy[pos << 1 | 1], lazy[pos]);
        }
        tree[pos] += lazy[pos] * (r - l + 1);
        lazy[pos] = 0;
    }
    void update(int l, int r, int s, int e, int pos, T data) {
        if(s <= l && r <= e) {
            lazy[pos] += data;
            propagate(l, r, pos);
            return;
        }
        propagate(l, r, pos);
        if(e <  l || r <  s) return;
        int mid = (l + r) / 2;
        update(l, mid, s, e, pos << 1, data);
        update(mid + 1, r, s, e, pos << 1 | 1, data);
        tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
    }
    void update(int s, int e, T data) { update(0, siz - 1, s, e, 1, data); }
    T query(int l, int r, int s, int e, int pos) {
        propagate(l, r, pos);
        if(s <= l && r <= e) return tree[pos];
        if(e <  l || r <  s) return 0;
        int mid = (l + r) / 2;
        return merge(query(l, mid, s, e, pos << 1), query(mid + 1, r, s, e, pos << 1 | 1));
    }
    T query(int s, int e) { return query(0, siz - 1, s, e, 1); }
    T merge(T a, T b) {
        return a + b;
    }
};