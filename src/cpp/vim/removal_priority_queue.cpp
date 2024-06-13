/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/
 * Test : 
 * Last Updated : 
 * Tag : rpq, remove_priority_queue
 */
template<typename T, typename Compare=less<T>>
struct RPQ {
    struct Node {
        T data;
        int id;
        Node():Node(T(), -1) { }
        Node(T _data, int _id):data(_data),id(_id) {}
    };
    vector<Node> heap;
    vector<int> inverted_index;
    Compare comp;
    RPQ():comp() { heap.resize(1); }
    RPQ(const vector<T> &V):comp() {
        int N = (int)V.size();
        heap.reserve(N + 1); heap.resize(N + 1);
        inverted_index.reserve(N + 1); inverted_index.resize(N + 1);
        for(int i = 1; i <= N; ++i) {
            heap[i] = Node(V[i - 1], i);
            inverted_index[i] = i;
        }
        for(int i = N; i >= 1; --i) heapify(i);
    }
    void heapify(int start_index = 1) {
        int cur = start_index, N = size();
        while(cur * 2 + 1 <= N) {
            int nxt = cur;
            if(comp(heap[nxt].data, heap[cur * 2].data)) nxt = cur * 2;
            if(comp(heap[nxt].data, heap[cur * 2 + 1].data)) nxt = cur * 2 + 1;
            if(cur != nxt) {
                swap(heap[cur], heap[nxt]);
                inverted_index[heap[cur].id] = cur;
                inverted_index[heap[nxt].id] = nxt;
                cur = nxt;
            }
            else break;
        }
    }
    T top() {
        assert((int)heap.size() > 0);
        return heap[1].data;
    }
    void pop() {
        heap[1] = heap.back(); heap.pop_back();
        heapify();
    }
    void remove(int idx) {
        assert(0 <= idx && idx < (int)inverted_index.size());
        int x = inverted_index[idx];
        assert(x > 0);
        heap[x] = heap.back(); heap.pop_back();
        heapify(x);
        inverted_index[idx] = -1;
    }
    void push_update() {
        int idx = size();
        while(idx != 1) {
            if(comp(heap[idx >> 1].data, heap[idx].data)) {
                swap(heap[idx], heap[idx >> 1]);
                inverted_index[heap[idx].id] = idx;
                idx >>= 1;
                inverted_index[heap[idx].id] = idx;
            }
            else break;
        }
    }
    int push(T data) {
        int id = inverted_index.size();
        heap.emplace_back(data, id);
        inverted_index.push_back(size());
        push_update();
        return id;
    }
    void update(int idx, T data) {
        assert(0 <= idx && idx < (int)inverted_index.size());
        int x = inverted_index[idx], N = size();
        assert(x > 0);
        heap[x].data = data;
        swap(heap[x], heap[N]);
        inverted_index[heap[x].id] = x;
        inverted_index[heap[N].id] = N;
        heapify(x);
        push_update();
    }
    int size() { return (int)heap.size() - 1; }
    bool empty() { return size() == 0; }
};
