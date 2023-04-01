/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/7469
 * Test : Accepted
 * Last Updated : 2023.04.01 03:21 PM (KST)
 */
template<typename T>
struct PST{
    struct Node{
        Node *left, *right;
        T data;
        Node(Node *l = nullptr, Node *r = nullptr, T v=0):left(l), right(r), data(v) { }
        Node *push(int l, int r, int x, T _data) {
            if(r < x || x < l) return this;
            if(l == r) return new Node(0, 0, this->data + _data);
            int mid = l + (r - l) / 2;
            Node *L = left->push(l, mid, x, _data);
            Node *R = right->push(mid + 1, r, x, _data);
            return new Node(L, R, L->data + R->data);
        }
    };
    Node *roots[100002];
    int siz;

    PST() { setting(); }
    PST(int N) { setting(N); }
    void setting(int N = 2e9 + 10){
        siz = N;
        roots[0] = new Node();
        roots[0]->left = roots[0]->right = roots[0];
    }
    
    void expand(int p){ roots[p] = roots[p - 1]; }
    void update(int p, int idx, T data, bool _expand=false){
        if(_expand) expand(p);
        roots[p] = roots[p]->push(1, siz, idx, data);
    }

    T query(Node *cur, int l, int r, int s, int e){
        if(s <= l && r <= e)return cur->data;
        if(e <  l || r <  s)return 0;
        int mid = l + (r - l) / 2;
        return query(cur->left, l, mid, s, e) + query(cur->right, mid + 1, r, s, e);
    }
    T query(int s, int e, int p){ return query(roots[p], 1, siz, s, e); }

    T kth(Node *s, Node *e, int l, int r, int k){
        if(l == r)return l;
        int mid = l + (r - l) / 2;
        T data = e->left->data - s->left->data;
        if(data >= k)return kth(s->left, e->left, l, mid, k);
        return kth(s->right, e->right, mid + 1, r, k - data);
    }
    T kth(int s, int e, int k){ return kth(roots[s], roots[e], 1, siz, k); }
};