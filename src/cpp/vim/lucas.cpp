/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/23824
 * Test : Accepted
 * Last Updated : 2025.11.20 14:23 PM (KST)
 * Tag : lucas
 */
[[power]]

struct Lucas {
    int mod;
    vector<long long> F, rF;
    Lucas(int _mod):mod(_mod) {
        F.resize(mod, 1);
        rF.resize(mod, 1);
        for(int i = 1; i < mod; ++i) F[i] = F[i - 1] * i % mod;
        rF[mod - 1] = power<long long>(F[mod - 1], mod - 2, mod);
        for(int i = mod - 2; i >= 0; --i) rF[i] = rF[i + 1] * (i + 1) % mod;
    }
    long long combination(long long n, long long r) {
        if(r < 0 || r > n) return 0LL;
        return F[n] * rF[r] % mod * rF[n - r] % mod;
    }
    long long lucas(long long n, long long r) {
        if(r < 0 || r > n) return 0LL;
        long long res = 1;
        while(n > 0 && r > 0) {
            long long a = n % mod, b = r % mod;
            if(a < b) return 0LL;
            res = res * combination(a, b) % mod;
            n /= mod; r /= mod;
        }
        return res;
    }
};
