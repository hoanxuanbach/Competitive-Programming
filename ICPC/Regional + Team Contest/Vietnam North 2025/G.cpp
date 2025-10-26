#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
    if (fopen(".inp", "r"))
        assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
    using namespace chrono;
    auto start = steady_clock::now();
#endif
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int testcases = 1;
    // cin >> testcases;
    for (int test = 1; test <= testcases; test++){
        // cout << "Case #" << test << ": ";
        Hollwo_Pelw();
    }
#ifdef hollwo_pelw_local
    auto end = steady_clock::now();
    cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}



const int N = 1e5 + 5;
const int S = 200;

#define ll long long

double angle(int x,int y,int z,int t){
    int a=z-x,b=t-y;
    double d=sqrtl(a*a+b*b);
    return (double)b/d;
}

int n, q, a[N], h[N], diff[N];

ll T,sum[N];
double calc(double sintheta0, int diff1) {
    double res=T+diff1/cos(asin(sintheta0));
    for (int i=1;i<=S;i++) res+=sum[i]/cos(asin(sintheta0/i));
    return res;
}

void Hollwo_Pelw(){
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> a[i];
        diff[i] = h[i] - h[i - 1];
    }
    for(int i=1;i<n;i++){
        if(a[i]>S) T+=diff[i+1];
        else sum[a[i]]+=diff[i+1];
    }
    for (int i = 1; i <= q; i++) {
        int x, y, z, t;
        cin >> x >> y >> z >> t;

        double f = angle(x, y, z, t);
        cout << fixed << setprecision(9) << calc(f, h[1] - x) << '\n';
    }
}