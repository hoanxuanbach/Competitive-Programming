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
void solve(){
    int n,m,L,X,Y;cin >> n >> m >> L >> X >> Y;
    int D=X-Y;  
    
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int s,t;cin >> s >> t;
        if(mp.find(s)!=mp.end()) mp[s]=max(mp[s],t);
        else mp[s]=t;
    }

    vector<pii> P;
    for(auto [s,t]:mp) P.push_back({s,t});
    
    vector<ld> res(m);
    for(int i=0;i<m;i++){
        int x;cin >> x;
        P.push_back({x,inf+i});
    }
    sort(P.begin(),P.end());
    
    ld cur=inf;
    for(auto [a,b]:P){
        if(b>=inf){
            b-=inf;
            res[b]=min(cur,(ld)(L-a)/Y);
        }
        else{
            int val=b*D+a;
            ld tm=(ld)(b-a)/X+(ld)(L-b)/Y;
            cur=min(cur,tm);
        }
    }
    for(int i=0;i<m;i++) cout << setprecision(9) << fixed << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
