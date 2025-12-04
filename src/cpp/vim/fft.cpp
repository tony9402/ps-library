/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/1067
 * Test : Accepted
 * Last Updated : 2019.11.02 12:56 PM (KST)
 * Tag : fft
 */
typedef complex<double> base;

template<typename T>
struct FFT{
    void fft(vector<base> &a, bool inv = false){
        int n = (int)a.size();
        for(int i=1,j=0;i<n;i++){
            int bit = n >> 1;
            for(;j>=bit;bit>>=1)j -= bit;
            j += bit;
            if(i < j)swap(a[i], a[j]);
        }
        for(int idx = 2; idx <= n; idx <<= 1){
            double ang = 2*M_PI/idx*(inv?-1:1);
            base x(cos(ang), sin(ang));
            for(int i=0;i<n;i+=idx){
                base w(1);
                for(int j=0;j<idx/2;j++){
                    base u = a[i+j], v = a[i+j+idx/2]*w;
                    a[i+j] = u+v;
                    a[i+j+idx/2] = u-v;
                    w *= x;
                }
            }
        }
        if(inv){
            for(auto &i : a) i /= n;
        }
    }
    vector<T> multiply(const vector<T> &a, const vector<T> &b){
        vector<base> A(a.begin(),a.end()), B(b.begin(),b.end());
        int n = 1, N=max(A.size(),B.size());
        while(n<N)n<<=1;
        A.resize(n);B.resize(n);
        fft(A);
        fft(B);
        for(int i=0;i<n;i++)
            A[i] *= B[i];
        fft(A, true);
        vector<T> res;
        res.resize(n);
        for(int i=0;i<n;i++)   
            res[i] = (T)(A[i].real() + (A[i].real() > 0 ? 0.5 : -0.5));
        return res;
    }
};
