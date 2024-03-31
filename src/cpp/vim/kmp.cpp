/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1786
 * Test : Accepted
 * Last Updated : 2023.04.02 03:04 AM (KST)
 * Tag : kmp
 */
template<typename T> struct KMP {
    vector<int> fail;
    vector<int> failure(const T &Q) {
        fail.resize((int)Q.size() + 1);
        for(int i = 1, j = 0; i < (int)Q.size(); ++i) {
            while(j > 0 && Q[i] != Q[j]) j = fail[j - 1];
            if(Q[i] == Q[j]) fail[i] = ++j;
        }
        return fail;
    }
    vector<int> kmp(const T& P, const T& Q) {
        if(fail.size() == 0) failure(Q);
        vector<int> res;
        for(int i = 0, j = 0; i < (int)P.size(); ++i) {
            while(j > 0 && P[i] != Q[j]) j = fail[j - 1];
            if(P[i] == Q[j]) {
                if(j + 1 == (int)Q.size()) res.push_back(i - (int)Q.size() + 1), j = fail[j];
                else ++j;
            }
        }
        return res;
    }
};
