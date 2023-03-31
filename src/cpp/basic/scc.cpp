/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/2150
 * Test : Accepted
 * Last Updated : 2023.04.01 12:35 AM (KST)
 */
struct SCC{
    bool _set_size;
    stack<int> st;
    vector<vector<int>> adj, scc;
    vector<int> d, used;
    int id, N;

    SCC():_set_size(false) {}
    SCC(int _N){
        _set_size = true;
        setSize(_N);
    }
    void setSize(int _N) {
        _set_size = true;
        N = _N;
        id = 0;
        adj = vector<vector<int>>(N + 1);
        d = used = vector<int>(N + 1);
    }

    void addEdge(int a, int b, bool bidirected = false) {
        adj[a].push_back(b);
        if(bidirected) adj[b].push_back(a);
    }

    int dfs(int x){
        d[x] = ++id;

        st.push(x);
        int par = d[x];
        for(const auto &i : adj[x]){
            if(!d[i])par = min(par, dfs(i));
            else if(!used[i])par = min(par, d[i]);
        }

        if(par == d[x]){
            vector<int> now;
            while(!st.empty()){
                int t = st.top();st.pop();
                used[t] = true;
                now.push_back(t);
                if(t == x)break;
            }
            scc.push_back(now);
        }
        return par;
    }

    void run(){ for(int i=1;i<=N;i++)if(!d[i])dfs(i); }
    int getSize() { return (int)scc.size(); }
};