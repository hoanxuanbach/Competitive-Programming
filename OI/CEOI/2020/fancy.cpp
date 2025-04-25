#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;
const int mod = 1e9+7;
const int maxn = 1e5+5;
int n,par[maxn],sz[maxn],total;

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
int f(int x){
    return (x*(x+1)/2)%mod;
}

void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    total-=(f(sz[u])+f(sz[v]));
    (sz[u]+=sz[v])%=mod;par[v]=u;
    total+=f(sz[u]);
    total=(total%mod+mod)%mod;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    vector<pair<int,int>> p(n);
    for(int i=0;i<n;i++){
        int h;cin >> h;
        p[i]={h,i+1};
    }
    for(int i=1;i<=n;i++) cin >> sz[i];
    sort(p.begin(),p.end(),greater<pair<int,int>>());
    int lst=inf,res=0;
    for(auto [x,i]:p){
        int num=((x+1+lst)*(lst-x)/2)%mod;
        (res+=num*total)%=mod;
        lst=x,par[i]=i;
        (total+=f(sz[i]))%=mod;
        if(i>1 && par[i-1]) unions(i-1,i);
        if(i<n && par[i+1]) unions(i,i+1);
    }
    int num=((lst+1)*lst/2)%mod;
    (res+=num*total)%=mod;
    cout << res << '\n';
}
