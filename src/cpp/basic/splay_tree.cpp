/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/3444
 * Test : Accepted
 * Last Updated : 2023.10.29 09:12 PM (KST)
 */
template<typename T, const int node_siz = 500000>
struct SplayTree {
    struct Data {
        int sz;
        T mn, mx, sum, value;
        bool flip, dummy;

        Data(T _value = 0) : value(_value) {
            init();
            flip = dummy = false;
        }

        void init() {
            sz = 1;
            mn = mx = sum = value;
        }
    };

    struct Node {
        Node *l, *r, *p;
        Data data;

        Node():Node(0){}
        Node(T _value) : Node(_value, nullptr) {}

        Node(T _value, Node *_p) {
            p = _p;
            l = r = nullptr;
            data = Data(_value);
        }

        bool is_left() { return this == p->l; }

        bool is_right() { return this == p->r; }

        bool is_root() { return p == nullptr || (!is_left() && !is_right()); }

        void merge(Data o) {
            data.sz += o.sz;
            data.mn = min(data.mn, o.mn);
            data.mx = max(data.mx, o.mx);
            data.sum += o.sum;
        }

        void update() {
            data.init();
            if (l) merge(l->data);
            if (r) merge(r->data);
        }

        void push() {
            if (data.flip == false) return;
            swap(l, r);
            data.flip = false;
            if (l) l->data.flip ^= 1;
            if (r) r->data.flip ^= 1;
        }
    };

    Node *root;
    Node *node[node_siz];

    SplayTree() {}

    SplayTree(int N, const vector<T> &V) { init(N, V); }

    void init(int N, const vector<T> &V) {
        const T INF = numeric_limits<T>::max() / 2;
        Node *cur = root = new Node(-INF);
        for (int i = 1; i <= N; ++i) {
            node[V[i]] = cur->r = new Node(V[i], cur);
            cur = cur->r;
        }
        node[N + 1] = cur->r = new Node(INF, cur);
        root->data.dummy = cur->r->data.dummy = true;
        for (int i = N + 1; i >= 1; --i) node[i]->update();
    }

    void rotate(Node *cur) {
        if (cur->p == nullptr) return;
        Node *p = cur->p;
        p->push();
        cur->push();

        if (cur->is_left()) {
            if (cur->r) cur->r->p = p;
            p->l = cur->r;
            cur->r = p;
        }
        else {
            if (cur->l) cur->l->p = p;
            p->r = cur->l;
            cur->l = p;
        }

        if (!p->is_root()) {
            if (p->is_left()) p->p->l = cur;
            else p->p->r = cur;
        }
        else root = cur;

        cur->p = p->p;
        p->p = cur;

        p->update();
        cur->update();
    }

    Node *splay(Node *cur, Node *g = nullptr) {
        while (!cur->is_root() && cur->p != g) {
            if (cur->p->is_root() || cur->p->p == g) {
                rotate(cur);
                continue;
            }
            if (cur->p->p != g) rotate((cur->is_left() ^ cur->p->is_left()) ? cur : cur->p);
            rotate(cur);
        }
        if (g == nullptr) root = cur;
        return root;
    }

    Node *kth(int k) {
        Node *cur = root;
        cur->push();
        while (true) {
            while (cur->l && cur->l->data.sz > k) {
                cur = cur->l;
                cur->push();
            }
            if (cur->l) k -= cur->l->data.sz;
            if (!k--) break;
            cur = cur->r;
            cur->push();
        }
        return splay(cur);
    }

    Node *gather(int l, int r) {
        Node *Left = kth(r + 1);
        Node *Right = kth(l - 1);
        return splay(Left, Right)->r->l;
    }

    Node *flip(int l, int r) {
        Node *cur = gather(l, r);
        cur->data.flip ^= 1;
        return cur;
    }

    Node *shift(int l, int r, int x) {
        Node *cur = gather(l, r);
        if (x >= 0) {
            x %= (r - l + 1);
            if (x == 0) return cur;
            flip(l, r);
            flip(l, l + x - 1);
            flip(l + x, r);
        }
        else {
            x *= -1;
            x %= (r - l + 1);
            flip(l, r);
            flip(l, r - x);
            flip(r - x + 1, r);
        }
        return gather(l, r);
    }

    int operator[](const int k) {
        return splay(node[k])->l->data.sz;
    }

    // Debuging
    void inorder(Node *cur) {
        push(cur);
        if (cur->l) inorder(cur->l);
        if (cur->data.dummy == false) cout << cur->data << ' ';
        if (cur->r) inorder(cur->r);
    }

    void inorder() { inorder(root); }
};