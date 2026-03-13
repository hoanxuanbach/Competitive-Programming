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

int ax[]={-1,0,1,0},
    ay[]={0,1,0,-1},
    bx[]={-2,-2,-1,1,2,2,-1,1},
    by[]={-1,1,2,2,-1,1,-2,-2};

void solve(){
    int N,M;cin >> N >> M;

    int mn=inf,res=0;
    vector<int> S;
    for(int mask=0;mask<(1<<(N*M));mask++){
        vector<vector<int>> f(N,vector<int>(M));
        
        vector<int> p(N*M);
        iota(p.begin(),p.end(),0);
        function<int(int)> fp = [&](int u){
            if(u!=p[u]) return p[u]=fp(p[u]);
            return u;
        };

        int cnt=0,all=0;
        auto unite = [&](int u,int v){
            u=fp(u);v=fp(v);
            if(u!=v){
                cnt--;
                p[v]=u;
                return;
            }
        };
        for(int i=0;i<N;i++) for(int j=0;j<M;j++) f[i][j]=(mask>>(i*M+j)&1),cnt+=f[i][j],all+=f[i][j];
    
        bool check=true;
        for(int i=0;i<N;i++) for(int j=0;j<M;j++) if(f[i][j]) for(int t=0;t<8;t++){
            int ni=i+bx[t],nj=j+by[t];
            if(ni<0 || ni>=N || nj<0 || nj>=M || !f[ni][nj]) continue;
            unite(i*M+j,ni*M+nj);
            if(!f[i+ax[t/2]][j+ay[t/2]]) check=false;
        }
        if(!check || cnt!=1 || all==1) continue;

        bool empty=true;
        for(int i=0;i<N;i++) if(f[i][0]) empty=false;
        if(empty) continue;
        empty=true;
        for(int i=0;i<M;i++) if(f[0][i]) empty=false;
        if(empty) continue;

        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++) cout << f[i][j];
            cout << '\n';
        }
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
