#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
const ld PI = acosl(-1);

void solve(){
    int n;cin >> n;
    vector<ld> f(2*n+1);f[0]=1;
    f[1]=expl((ld)1/n);
    for(int i=2;i<=2*n;i++) f[i]=f[i-1]*f[1];   
    for(int i=0;i<=2*n;i++) f[i]-=1;

    int res=0;
    ld val=PI;
    vector<pair<ld,int>> P;
    for(int a=0;a<=2*n;a++){
        if(f[a]>=PI){
            if(f[a]-PI<val) val=f[a]-PI,res=a*a;
            break;
        }
        for(int b=0;b<=a;b++){
            ld cur=f[a]+f[b];
            if(cur>=PI){
                if(cur-PI<val) val=cur-PI,res=a*a+b*b;
                break;
            }
            P.push_back({cur,a*a+b*b});
        }
    }
    sort(P.begin(),P.end());

    int pos=(int)P.size()-1;

    for(auto [d,S]:P){
        while(pos>=0 && P[pos].first+d>PI) pos--;
        {
            ld f=abs(d+P[pos].first-PI);
            if(f<val) val=f,res=S+P[pos].second;
        }
        if(pos+1<(int)P.size()){
            ld f=abs(d+P[pos+1].first-PI);
            if(f<val) val=f,res=S+P[pos+1].second;
        }
    }
    cout << val << ' ' << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
