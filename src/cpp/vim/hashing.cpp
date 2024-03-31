/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/21162
 * Test : Accepted
 * Last Updated : 2023.04.02 02:35 AM (KST)
 * Tag : hashing
 */
template<long long C, long long HASH_MOD> struct Hashing {
    vector<long long> H, B;
    template<typename T> void build(const T& S) {
        H.resize(S.size() + 1);
        B.resize(S.size() + 1); B[0] = 1;
        for(int i = 1; i <= (int)S.size(); ++i) H[i] = (H[i - 1] * C + S[i - 1]) % HASH_MOD;
        for(int i = 1; i <= (int)S.size(); ++i) B[i] = B[i - 1] * C % HASH_MOD;
    }
    long long get(int s, int e) {
        long long ret = (H[e] - H[s - 1] * B[e - s + 1]) % HASH_MOD;
        if(ret < 0) ret += HASH_MOD;
        return ret;
    }
    void chk_setting() { assert(gcd(C, HASH_MOD) == 1); }
};
