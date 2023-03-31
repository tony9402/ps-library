#include<bits/stdc++.h>

using namespace std;

[[power]]
[[ntt]]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b; cin >> a >> b;
    vector<long long> A, B, result;
    A.reserve(a.size()); B.reserve(b.size());
    for(int i = (int)a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for(int i = (int)b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    result = multiply(A, B);
    result.push_back(0);
    for(int i = 0; i < (int)result.size(); i++) {
        if(result[i] < 0) {
            int b = (-result[i] + 9) / 10;
            result[i + 1] -= b;
            result[i] += b * 10;
        }
        else {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
    }
    while(result.size() > 1 && result.back() == 0) result.pop_back();
    string s;
    for(int i = (int)result.size() - 1; i >= 0; i--) s += result[i] + '0';
    cout << s;

    return 0;
}