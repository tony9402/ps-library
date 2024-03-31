/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1260
 * Test : Accepted
 * Last Updated : 2023.04.02 03:20 AM (KST)
 * Tag : graph
 */
template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size() - 1; }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};