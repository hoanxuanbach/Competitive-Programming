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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int inf = 1e18;
const int N = 1e6+5;

int deg[N],f[N],mn[N];
vector<int> g[N];

void solve(){
    int n,m,q;cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt=0;

    for(int i=1,l=1;i<=n;i++){
        for(int x:g[i]) if(deg[x]>1) f[i]++;
        if(f[i]>2) cnt++;

        auto add = [&](int u){
            if(deg[u]==1){
                for(int x:g[u]) if(l<=x && x<=i) f[x]++,cnt+=(f[x]==3);
            }
            deg[u]++;
        };
        auto del = [&](int u){
            deg[u]--;
            if(deg[u]==1){
                for(int x:g[u]) if(l<=x && x<=i) cnt-=(f[x]==3),f[x]--;
            }
        };

        for(int x:g[i]) if(l<=x && x<=i) add(i),add(x);
        while(cnt){
            for(int x:g[l]) if(l<=x && x<=i) del(l),del(x);
            l++;
        }
        mn[i]=l;
    }

    for(int i=0;i<q;i++){
        int x,y;cin >> x >> y;
        cout << (mn[y]<=x?"Yes":"No") << '\n';
    }

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
