/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1708
 * Test : Accepted
 * Last Updated : 2025.02.19 01:17 AM (KST)
 * Tag : convex, convexhull
 */
[[intersection]]

template<typename T> vector<Point<T>> ConvexHull(vector<Point<T>> V) {
    swap(V[0], *min_element(V.begin(), V.end()));
    sort(V.begin() + 1, V.end(), [&](Point<T> a, Point<T> b) {
        int w = ccw(V[0], a, b);
        return w ? w > 0 : dist(V[0], a) < dist(V[0], b);
    });
    vector<int> st;
    for(int i = 0; i < (int)V.size(); ++i) {
        // line ok < or <=
        while(st.size() > 1 && ccw(V[st[st.size() - 2]], V[st.back()], V[i]) <= 0) st.pop_back();
        st.push_back(i);
    }
    int idx = (int)st.size() - 1;
    while(idx > 1 && ccw(V[st[idx - 2]], V[st[idx - 1]], V[st[idx]]) == 0) -- idx;
    reverse(st.begin() + idx, st.end());
    vector<Point<T>> res;
    for(int x: st) res.push_back(V[x]);
    return res;
}
template<typename T> long long max_distance_on_convex(const Vec<Point<T>> &convex) {
    int N = (int)convex.size();
    long long ret = 0;
    for(int i = 0, j = 0; i < N; ++i) {
        function<i64(i32, i32)> chk = [&](i32 a, i32 b) -> i64 { return area<i64>(convex[a], convex[(a + 1) % N], convex[b]); };
        while(chk(i, j) < chk(i, (j + 1) % N)) ret = max(ret, dist(convex[i], convex[j])), j = (j + 1) % N;
        ret = max(ret, dist(convex[i], convex[j]));
    }
    return ret;
}
