/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1629
 * Test : Accepted
 * Last Updated : 2023.04.01 10:44 PM (KST)
 */
template<typename T, typename modulo>
T power(T a, T b, modulo mod) {
    T ret = 1;
    while(b) {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}