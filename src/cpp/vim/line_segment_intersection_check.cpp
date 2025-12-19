/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/20149
 * Test : Accepted
 * Last Updated : 2025.02.07 02:47 AM (KST)
 * Tag : line, intersection
 */
template<typename T> struct Point {
    T x, y;
    Point():Point(0, 0) { }
    Point(T _x, T _y):x(_x),y(_y) { }
    Point operator+(Point p) { return Point(x+p.x,y+p.y); }
    Point operator-(Point p) { return Point(x-p.x,y-p.y); }
    T operator*(Point p) { return x*p.y-y*p.x; }
    bool operator<(const Point &p) const { return make_pair(x, y) < make_pair(p.x, p.y); }
    bool operator==(Point p) { return x == p.x && y == p.y; }
    template<typename OT> void operator=(Point<OT> p) { *this=Point(p.x,p.y); }
    void t() { swap(x, y); }
};
template<typename T> inline istream& operator>>(istream &in, Point<T> &o) { in >> o.x >> o.y; return in; }
template<typename T> inline ostream& operator<<(ostream &out, Point<T> &o) { out << o.x << ' ' << o.y; return out; }
// -1: 반시계, 0: 평행, 1: 시계
template<typename T> int ccw(Point<T> a, Point<T> b, Point<T> c) {
    T x = a * b + b * c + c * a;
    return (x > 0) - (x < 0);
}
template<typename T> T dist(Point<T> a, Point<T> b) {
    T x = (a.x - b.x), y = (a.y - b.y);
    return x * x + y * y;
}
template<typename T> struct Line {
    Point<T> p1, p2;
    Line():Line(0, 0) {}
    Line(T a, T b):Line(Point<T>(0, 0), Point<T>(a, b)) { }
    Line(Point<T> a, Point<T> b):p1(a),p2(b) { 
        if(p1.x > p2.x) swap(p1, p2);
        else if(p1.x == p2.x && p1.y > p2.y) swap(p1, p2);
    }
    T dx() { return p1.x - p2.x; }
    T dy() { return p1.y - p2.y; }
    T ccw() { return p1 * p2; }
    void t() { p1.t(); p2.t(); }
};
// 0: 교점 0개, 1: 교점 1개 (끝점 O), 2: 교점 1개 (끝점 X), 3: 교점 ∞개
// 4: 평행 교점 1개, 5: 평행 교점 ∞개
template<typename T> int intersect(Line<T> l1, Line<T> l2) {
    int ca = ccw(l1.p1, l1.p2, l2.p1), cb = ccw(l1.p1, l1.p2, l2.p2);
    int cc = ccw(l2.p1, l2.p2, l1.p1), cd = ccw(l2.p1, l2.p2, l1.p2);
    if(ca == 0 && cb == 0 && cc == 0 && cd == 0) {
        if(l1.p1.x == l1.p2.x && l2.p1.x == l2.p2.x && l1.p2.x == l2.p1.x) l1.t(), l2.t();
        int A = l1.p1.x, B = l1.p2.x, C = l2.p1.x, D = l2.p2.x;
        if(A > D || B < C) return 0;
        if(A == D || B == C) return 4;
        return 5;
    }
    if(ca * cb <= 0 && cc * cd <= 0) return (!ca || !cb || !cc || !cd) ? 1 : 2;
    return 0;
}
// TODO
template<typename T, typename AT> pair<int, Point<AT>> intersection_point(Line<T> l1, Line<T> l2) {
    int chk = intersect(l1, l2);
    if(chk == 0 || chk == 3) return make_pair(chk, Point<AT>());
    if(chk == 1 || chk == 4) {
        Point<AT> ans;
        if(l1.p1 == l2.p1 || l1.p1 == l2.p2) ans = l1.p1;
        else if(l1.p2 == l2.p1 || l1.p2 == l2.p2) ans = l1.p2;
        else if(ccw(l1.p1, l1.p2, l2.p1) == 0) ans = l2.p1;
        else if(ccw(l1.p1, l1.p2, l2.p2) == 0) ans = l2.p2;
        else if(ccw(l2.p1, l2.p2, l1.p1) == 0) ans = l1.p1;
        else if(ccw(l2.p1, l2.p2, l1.p2) == 0) ans = l1.p2;
        return make_pair(1, ans);
    }
    T a = l1.ccw() * l2.dx() - l1.dx() * l2.ccw();
    T b = l1.ccw() * l2.dy() - l1.dy() * l2.ccw();
    T d = l1.dx() * l2.dy() - l1.dy() * l2.dx();
    return make_pair(chk, Point<AT>(1. * a / d, 1. * b / d));
}
