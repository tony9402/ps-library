/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/2042
 * Test : Accepted
 * Last Updated : 2023.04.01 09:57 PM (KST)
 * Tag : segment, segtree, seg
 */
template<typename T>
struct Segment {
    vector<T> tree;
    int siz;

    Segment(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree = vector<T>(siz << 1);
    }
    void build() {
        for(int i = siz - 1; i > 0; --i) {
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
        }
    }
    void update(int idx, T data) {
        tree[idx += siz] = data;
        while(idx >>= 1) tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
    }
    T query(int l, int r) {
        T ret_L = T(), ret_R = T();
        for(l += siz, r += siz; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) ret_L = ret_L + tree[l ++];
            if(~r & 1) ret_R = tree[r --] + ret_R;
        }
        return ret_L + ret_R;
    }
    T& operator[](const int &idx) { return tree[idx + siz]; }
};
