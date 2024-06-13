/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/
 * Test :
 * Last Updated : 
 * Tag : z
 */
template<typename T>
vector<int> Z(const T &V) {
    int N = (int)V.size();
    vector<int> ret(N); ret[0] = N;
    for(int i = 1, l = 0, r = 0; i < N; ++i) {
        if(i < r) ret[i] = min(r - i - 1, ret[i - l]);
        while(i + ret[i] < N && V[i + ret[i]] == V[ret[i]]) ++ ret[i];
        if(i + ret[i] > r) r = i + ret[i], l = i;
    }
    return ret;
}
