/*
 * Problem for Testing Template : 
 * Test : 
 * Last Updated : 
 */
const int MAXL = 1000000000;
template<typename T>
struct DynamicSegment{
    struct Node{
        int l, r; // range
        T data;
        Node *left, *right;
        Node():l(1),r(MAXL),data(0),left(0),right(0) { }
        void extend(){
            if(l == r)return;
            if(left == 0){ //if leaf node
                left  = new Node();
                right =  new Node();
                int m = (l + r) / 2;
                left->l  = l;
                left->r  = m;
                right->l = m + 1;
                right->r = r; 
            }
            return;
        }
    };
    Node *tree;

    DynamicSegment() { tree = new Node(); }
    void update(Node *cur, int x, T data){
        if(x < cur->l || cur->r < x)return;
        if(cur->l == cur->r)return cur->data = data, (void)(0);
        update(cur->left, x, data);
        update(cur->right, x, data);
        cur->data = mergeNode(cur->left->data, cur->right->data);
    }
    void update(int x, T data){ update(tree, x, data); }

    T query(Node *cur, int l, int r){
        if(cur->l > cur->r || cur->r < l || cur->l > r)return T(0);
        if(l <= cur->l && cur->r <= r)return cur->data;
        cur->extend();
        return mergeNode(query(cur->left, l, r), query(cur->right, l, r));
    }
    T query(int l, int r){ return query(tree, l, r); }
    T mergeNode(T a, T b){ return a + b; }
};