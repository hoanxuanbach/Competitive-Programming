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

void solve(){
    int N;cin >> N;
    vector<int> f(N+1);
    for(int i=1;i<=N;i++) for(int j=i*2;j<=N;j+=i) f[j]+=i;

    int k=-1,val=-1;

    vector<int> vis(N+1);
    for(int i=2;i<=N;i++){
        int x=i;
        vector<int> v;
        while(x<=N && !vis[x]){
            v.push_back(x);
            vis[x]=1;x=f[x];
        }
        bool check=false;
        int mn=inf,sz=(int)v.size();
        for(int j=0;j<sz;j++) if(v[j]==x){
            sz-=j;check=true;
            for(int t=0;t<sz;t++) mn=min(mn,v[j+t]);
            break;
        }   
        if(check && sz>k) k=sz,val=mn;
    }
    cout << k << ' ' << val << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
