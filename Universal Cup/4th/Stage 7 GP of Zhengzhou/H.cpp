#include<bits/stdc++.h>
using namespace std;
#define int long long 
 
const int maxn = 5e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double 

void solve(){
    int n;cin >> n;
    vector<int> a(n+1),c(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> c[i];
    
    vector<ld> g(n+1);
    vector<int> cnt(n+1),ss(n+2);
    auto cal = [&](){
        for(int i=0;i<=n;i++) cnt[i]=0;
        for(int i=n;i>=1;i--){
            cnt[a[i]]++;
            ss[i]=ss[i+1]+c[i];
            g[i]=(ld)cnt[a[i]]/(n-i+1);
        }
        
        ld f=0,T=0;
        vector<pair<ld,ld>> S;
        S.push_back({0,0});
        for(int i=n;i>=1;i--){
            T*=g[i];
            ld d=g[i];
            f=(ss[i]-T)/(2-d);
            //f = ss[i] - f*(1-d) - T

            while(!S.empty() && f<S.back().first){
                auto [x,k]=S.back();S.pop_back();
                T-=d*x*(1-k);d*=k;
                f=(ss[i]-T)/(2-d);
            }

            T+=f*(1-d);
            S.push_back({f,d});
        }
        cout << setprecision(12) << fixed << f << '\n';
    };

    cal();
    int q;cin >> q;
    for(int i=0;i<q;i++){
        int k;cin >> k;
        while(k--){
            int p,x,y;cin >> p >> x >> y;
            a[p]=x;c[p]=y;
        }
        cal();
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}