#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    //dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

void solve(){
    int H,W,L;cin >> H >> W >> L;
    vector<vector<int>> T(H,vector<int>(W,0));

    vector<pii> P;
    for(int i=0;i<H;i++) for(int j=0;j<W;j++){
        cin >> T[i][j];
        P.push_back({T[i][j],~(i*W+j)});
        P.push_back({T[i][j]+L,i*W+j});
    }
    sort(P.begin(),P.end());

    vector<int> par(H*W+1),nxt(H*W+1);
    vector<vector<int>> f(H*W+1);
    vector<pii> mx(H*W+1);
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) mx[i*W+j]={T[i][j],i*W+j};
    iota(par.begin(),par.end(),0);

    int Q;cin >> Q;
    
    vector<int> A(Q),B(Q),res(Q);
    for(int i=0;i<Q;i++){
        int x,y,u,v;cin >> x >> y >> u >> v;
        x--,y--,u--,v--;
        A[i]=x*W+y,B[i]=u*W+v;
        f[A[i]].push_back(i);
        f[B[i]].push_back(i);
    }

    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    auto unions = [&](int u,int v,int X){
        u=findpar(u),v=findpar(v);
        if(u==v) return;
        if((int)f[u].size()<(int)f[v].size()) swap(u,v);
        for(int id:f[v]){
            int a=findpar(A[id]),b=findpar(B[id]);
            if(a==b) continue;
            else if((a==u && b==v) || (a==v && b==u)) res[id]=X;
            else f[u].push_back(id);
        }
        par[v]=u,mx[u]=max(mx[u],mx[v]);
        
    };
    for(auto [X,id]:P){
        if(id<0){
            id=~id;
            int i=id/W,j=id%W;
            for(int t=0;t<4;t++){
                int ni=i+dx[t],nj=j+dy[t];
                if(ni<0 || nj<0 || ni>=H || nj>=W) continue;
                if(T[ni][nj]<=X) unions(ni*W+nj,i*W+j,X);
            }
        }
        else{
            int x=findpar(id);
            nxt[id]=mx[x].se;
            //cout << id << ' ' << nxt[id] << '\n';
        }
    }
    int LG=0;
    while((1<<LG)<=H*W) LG++;
    vector<vector<int>> jmp(LG,vector<int>(H*W));
    for(int i=0;i<H*W;i++) jmp[0][i]=nxt[i];
    for(int i=1;i<LG;i++) for(int j=0;j<H*W;j++) jmp[i][j]=jmp[i-1][jmp[i-1][j]];
    
    for(int i=0;i<Q;i++){
        int d=0,x=A[i];
        //cout << x << ' ' << B[i] << ' ' << res[i] << '\n';
        if(T[x/W][x%W]+L>=res[i]){
            cout << 1 << '\n';
            continue;
        }
        
        for(int j=LG-1;j>=0;j--){
            int y=jmp[j][x];
            if(T[y/W][y%W]+L<res[i]) d+=(1<<j),x=y;
        }
        
        x=nxt[x],d++;
        if(T[x/W][x%W]+L<res[i]) cout << -1 << '\n';
        else cout << d+1 << '\n';
            
    }
    
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
