[[power]]

/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/15576
 * Test : Accepted
 * Last Updated : 2023.04.01 12:31 AM (KST)
 * Tag : ntt
 */
const long long W = 3;
const long long MOD = 998244353;

void _NTT(vector<long long> &V, bool inv = false) {
    int N = (int)V.size();
    vector<long long> root(N >> 1);
    for(int i = 1, j = 0; i < N; i++) {
        int bit = (N >> 1);
        for(; j >= bit; bit >>= 1) j &= ~bit; 
        j |= bit;
        if(i < j) swap(V[i], V[j]);
    }
    long long angle = power(W, (MOD - 1) / N, MOD);
    if(inv) angle = power(angle, MOD - 2, MOD);
    root[0] = 1;
    for(int i = 1; i * 2 < N; i++) root[i] = root[i - 1] * angle % MOD;
    for(int i = 2; i <= N; i <<= 1) {
        long long step = N / i;
        for(int j = 0; j < N; j += i) {
            for(int k = 0; k * 2 < i; k++) {
                long long u = V[j | k];
                long long v = V[j | k | i >> 1] * root[step * k] % MOD;
                V[j | k] = (u + v) % MOD;
                V[j | k | i >> 1] = (u - v) % MOD;
                if(V[j | k | i >> 1] < 0) V[j | k | i >> 1] += MOD;
            }
        }
    }
    if(inv) {
        long long t = power(1LL * N, MOD - 2, MOD);
        for(int i = 0; i < N; i++) V[i] = (V[i] * t) % MOD;
    }
}

vector<long long> multiply(const vector<long long> &vec1, const vector<long long> &vec2) { 
    vector<long long> A(vec1.begin(), vec1.end());
    vector<long long> B(vec2.begin(), vec2.end());
    int L = (int)vec1.size(), R = (int)vec2.size(), N;
    for(N = 2; N < L + R; N <<= 1);
    A.resize(N); B.resize(N);
    _NTT(A); _NTT(B);
    for(int i = 0; i < N; i++) A[i] = A[i] * B[i] % MOD;
    _NTT(A, true);
    return A;
}
