/*
 * Problem for Testing Template : 
 * Test : 
 * Last Updated : 
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