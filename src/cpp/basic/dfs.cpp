
function<void(int, int)> dfs = [&](int cur, int prev) -> void {
    for(int nxt: G[cur]) {
        if(nxt == prev) continue;
        dfs(nxt, cur);
    }
};