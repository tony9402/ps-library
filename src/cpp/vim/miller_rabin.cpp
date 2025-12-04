/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/5615
 * Test : Accepted
 * Last Updated : 2023.04.01 12:20 AM (KST)
 * Tag : miller, bigprime
 */
[[power]]
bool MillerRabin(long long a, long long b) {
    if(a % b == 0) return false;
    for(long long d = a - 1; ; d >>= 1) {
        long long cur = power<long long>(b, d, a);
        if(d & 1) return cur != 1 && cur != a - 1;
        if(cur == a - 1) return false;
    }
    return true;
}
bool isPrime(long long x) {
    if(x == 2 || x == 3 || x == 5 || x == 7) return true;
    if(x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if(x < 121) return x > 1;
    if(x < (1ULL << 32)) {
        for(const long long &y: {2, 7, 61}) {
            if(x == y) return true;
            if(x > y && MillerRabin(x, y)) return false;
        }
    }
    else {
        for (const long long &y : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if(x == y) return true;
            if(x > y && MillerRabin(x, y)) return false;
        }
    }
    return true;
}
