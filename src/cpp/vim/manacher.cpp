/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/13275
 * Test : Accepted
 * Last Updated : 2025.02.18 12:56 PM (KST)
 * Tag : manacher
 */
struct Manacher {
    vector<int> P;
    Manacher(string S) {
        string T = "$";
        for(char ch: S) T += ch, T += '$';
        int N = (int)T.size();
        P.resize(N);
        for(int i = 0, r = 0, c = 0; i < N; ++i) {
            if(2 * c >= i) P[i] = max(0, min(P[2 * c - i], r - i));
            while(0 <= i - P[i] - 1 && i + P[i] + 1 < N && T[i - P[i] - 1] == T[i + P[i] + 1]) ++ P[i];
            if(r < i + P[i]) r = i + P[i], c = i;
        }
    }
    int& operator[](int idx) { return P[idx]; }
};
