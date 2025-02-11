/*
 * Problem for Testing Template :
 * https://www.acmicpc.net/problem/10868
 * Test : Accepted
 * Last Updated : 2025.02.11 18:00 (KST)
 * Tag: rmq
 */
struct RMQ {
    vector<int> L;
    vector<vector<int>> table;
    RMQ(const vector<int> &V) {
        int N = (int)V.size();
        L = vector<int>(N + 1, 0);
        for (int i = 2; i <= N; ++i) L[i] = L[i / 2] + 1;
        table = vector<vector<int>>(L[N] + 1, vector<int>(N));
        for (int i = 0; i < N; ++i) table[0][i] = V[i];
        for (int i = 1; i <= L[N]; ++i) {
            int k = 1 << (i - 1);
            for (int j = 0; j + k < N; ++j) {
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + k]);
            }
        }
    }
    int query(int l, int r) {
        int d = L[r - l + 1];
        return merge(table[d][l], table[d][r - (1 << d) + 1]);
    }
    int merge(int a, int b) {
        return min(a, b);
    }
};
