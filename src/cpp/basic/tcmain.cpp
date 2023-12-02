#include<bits/stdc++.h>

using namespace std;

typedef bool i1;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f4;
typedef double f8;
typedef long double f16;

template<typename T> using Vec = vector<T>;

template<int fp=0> struct fastio { fastio() { ios::sync_with_stdio(false); cin.tie(0); if(fp)cout<<fixed<<' '<<setprecision(fp); } };

template<typename First, typename Second> inline istream& operator>>(istream &in, pair<First, Second> &_data) { in>>_data.first>>_data.second; return in; }
template<typename First, typename Second> inline ostream& operator<<(ostream &out, pair<First, Second> &_data) { out<<_data.first<<' '<<_data.second; return out; }
template<typename First, typename Second, typename Third> inline istream& operator>>(istream &in, tuple<First, Second, Third> &_data) { in>>get<0>(_data)>>get<1>(_data)>>get<2>(_data); return in; }
template<typename First, typename Second, typename Third> inline ostream& operator<<(ostream &out, tuple<First, Second, Third> &_data) { out<<get<0>(_data)<<' '<<get<1>(_data)<<' '<<get<2>(_data); return out; }

template<typename T> auto Vector(const int N, const T& value) { return vector(N, value); }
template<typename...Ts> auto Vector(const int N, Ts... args) { return vector(n, Vector(args...))}
template<typename InputType> void in(InputType& x) { cin>>x; }
template<typename InputType, typename... InputTypes> void in(InputType& x, InputTypes& ...y) { cin>>x; in(y...); }
template<typename IterableInputType> void vin(IterableInputType &V, int skip=0) { for(auto &x: V) if(--skip < 0) cin >> x; }

template<const int p=0, typename OutputType> void out(OutputType x) { cout<<x<<' '; }
template<const int p=0, typename OutputType, typename... OutputTypes> void out(OutputType x, OutputTypes ...y) { cout<<fixed<<setprecision(p)<<x<<' '; out<p>(y...); }
template<const int p=0, typename IterableOutputType> void vout(const IterableOutputType &V, int skip=0) { for(auto &x: V) if(--skip<0) out<p>(x); }

template<i64 modulo=numeric_limits<i64>::max(), typename... T> i64 Sum(T... x) { return (... + x) % modulo; }
template<i64 modulo=numeric_limits<i64>::max(), typename... T> i64 Mul(T... x) { return (... * x) % modulo; }

constexpr int dy[] = {-1,1,0,0,-1,-1,1,1,-2,-1,1,2,2,1,-1,-2};
constexpr int dx[] = {0,0,-1,1,-1,1,-1,1,1,2,2,1,-1,-2,-2,-1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testcase = ${1}; ${2} cin >> testcase;
    while(~--testcase) {
        ${3}
    }
}