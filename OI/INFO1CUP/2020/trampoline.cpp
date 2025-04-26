// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define pii pair<int,int>
const int mod=998244353;
const int maxn=200005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int r,c,n,nxt[maxn][maxl];
pii x[maxn];
map<int,vector<pii>> mp;
int cal(int p,int i){
    int cur=x[p].first+(1<<(i-1)),y=nxt[p][i-1];
    if(y==-1) return -1;
    auto it=lower_bound(mp[cur].begin(),mp[cur].end(),make_pair(y,0));
    if(it==mp[cur].end()) return -1;
    return nxt[it->second][i-1];
}
bool check(int x1,int y1,int x2,int y2){
    if(x1>x2) return false;
    if(x1==x2){
        if(y1<=y2) return true;
        else return false;
    }
    for(int i=0;i<18;i++){
        if((x2-x1)&(1<<i)){
            auto it=lower_bound(mp[x1].begin(),mp[x1].end(),make_pair(y1,0));
            if(it==mp[x1].end()) return false;
            y1=nxt[it->second][i];x1+=(1<<i);
        }
        if(y1==-1) return false;
    }
    if(y1<=y2) return true;
    else return false;
}
void solve(){
    int r,c,n;cin >> r >> c >> n;
    for(int i=1;i<=n;i++) cin >> x[i].first >> x[i].second;
    sort(x+1,x+n+1);
    for(int i=1;i<=n;i++){mp[x[i].first].push_back({x[i].second,i});nxt[i][0]=x[i].second;}
    for(int i=1;i<18;i++){
        for(int j=1;j<=n;j++) nxt[j][i]=cal(j,i);
    }
    int t;cin >> t;
    while(t--){
        int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
        if(check(x1,y1,x2,y2)) cout << "Yes\n";
        else cout << "No\n";
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
