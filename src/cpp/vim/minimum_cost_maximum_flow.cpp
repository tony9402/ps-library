/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/11408
 * Test : 
 * Last Updated : 2023.11.29 17.40 PM (KST)
 * Tag : mcmf
 */


struct MCMF {
    struct Edge {

        int to, c, f, dst;
        Edge* r;
        Edge(int _to=-1, int _c=0, int _dst=0):to(_to),c(_c),dst(_dst), f(0), r(nullptr) { }
        int spare() { return c - f; }
        void setRev(Edge* rev) { r = rev; }
        void flow(int x) { f += x; r->f -= x; }
    };
};
