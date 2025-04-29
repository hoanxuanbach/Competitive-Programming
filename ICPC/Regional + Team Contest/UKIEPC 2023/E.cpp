#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")


#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 2e5 + 5;
const int mod = 1e9 + 7;
const i64 oo = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

i64 rand_range(i64 l, i64 r)
{
    i64 len = r - l + 1;
    return (rng() % len + l);
}
double rd01(){
    double x=rand()/RAND_MAX;
    return x;
}

string s;
int n, a[50][50];
pair<int, int> res;

void solve() {
    cin >> s; n = isz(s);
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) cin >> a[i][j];
    int mask=0,cur=0;
    auto st=clock();
    for(double T=3*n;(clock()-st)<(4*CLOCKS_PER_SEC-50);T*=0.9997){
        for(int i=0;i<=100;i++){
            int id=rand_range(0,n-1),nmask=mask^(1<<id),nw=cur;
            if((mask>>id)&1){
                for(int j=0;j<n;j++) if((mask>>j)&1) nw-=a[min(id,j)][max(id,j)];
            }
            else{
                for(int j=0;j<n;j++) if((nmask>>j)&1) nw+=a[min(id,j)][max(id,j)];
            }
            res = max(res, {nw, nmask});
            if(nw>=cur || (i==100 && exp((nw-cur)/T)>=rd01())) cur=nw,mask=nmask;
        }
    }

    cout << __builtin_popcount(res.ss) << endl;
    for (int i = 0; i < n; ++i) if (res.ss >> i & 1) cout << s[i];
    cout << endl;
}

signed main() {

#ifndef CDuongg
    if(fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
