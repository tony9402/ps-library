/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1000
 * Test : Accepted
 * Last Updated : 2023.04.02 01:22 AM (KST)
 * Tag : fastinput
 */
#define BUFFERMAX 1 << 19
struct IO {
    char buf[BUFFERMAX];

    char _read() {
        static int idx = BUFFERMAX;
        if(idx == BUFFERMAX){
            fread(buf, 1, BUFFERMAX, stdin);
            idx = 0;
        }
        return buf[idx++];
    }

    char readChar() {
        char ret = _read();
        while(ret == 10 || ret == 32) ret = _read();
        return ret;
    }

    string readString() {
        string ret = "";
        char now = _read();
        while(now == 10 || now == 32) now = _read();
        while(true) {
            ret += now;
            now = _read();
            if(now == 10 || now == 32) break;
        }
        return ret;
    }

    template<typename T> T readInt() {
        T ret = 0;
        bool minus = false;
        char now = _read();
        while(now == 10 || now == 32) now = _read();
        if(now == '-') minus = true, now = _read();
        while(48 <= now && now <= 57) {
            ret = ret * 10 + now - 48;
            now = _read();
        }
        if(minus) ret *= -1;
        return ret;
    }

    void read(int &x) { x = readInt<int>(); }
    void read(long long &x) { x = readInt<long long>(); }
    void read(char &x) { x = readChar(); }
    void read(string &x) { x = readString(); }
    template<typename Type, typename... Types> void read(Type &arg, Types &...args) {  read(arg); read(args...); }
} io;

template<typename T>
IO& operator>> (IO& in, T &x) { in.read(x); return in; }

#define cin io
#define istream IO