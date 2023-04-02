#include<bits/stdc++.h>

using namespace std;

[[dynamic_segment_tree_with_lazy_propagation]]
template<typename T> T DynamicSegmentLazy<T>::merge(T a, T b) { return a + b; }

struct Query{
    long long i, j, k, idx;
    Query(long long i=0, long long j=0, long long k=0, long long idx=0):i(i),j(j),k(k),idx(idx){ }
    bool operator<(const Query& o) const { return k > o.k; }
};
vector<Query> f, s;
vector<long long> answer;

DynamicSegmentLazy<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    for(int i=0;i<n;i++){
        int t;
        long long a, b, c;
        cin >> t >> a >> b >> c;
        (t == 1 ? f : s).push_back(Query(a,b,c,s.size()));
    }
    answer.resize(s.size());
    sort(s.begin(),s.end());
    for(int i=1;i<=(int)f.size();i++){
        while(s.size() && s.back().k < i){
            answer[s.back().idx] = tree.query(s.back().i, s.back().j);
            s.pop_back();
        }
        tree.update(f[i-1].i, f[i-1].j, f[i-1].k);
    }
    while(s.size()){
        answer[s.back().idx] = tree.query(s.back().i, s.back().j);
        s.pop_back();
    }
    for(auto &i: answer)cout << i << '\n';
    
    return 0;    
}