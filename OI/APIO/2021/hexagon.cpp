#include "hexagon.h"
#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e9;
const int mod = 1e9+7;
const int maxn = 2e5+5;
const int inv2 = (mod+1)/2;
const int inv3 = (mod+1)/3;
int dx[]={0,0,1,1,0,-1,-1},
    dy[]={0,1,1,0,-1,-1,0};

int S[maxn],T[maxn],p[maxn],d[maxn];
int f[maxn],mt[maxn],tp[maxn],lx[maxn],rx[maxn],ly[maxn],ry[maxn],cnt;
vector<int> h[maxn],com;
vector<pair<int,int>> g[maxn];
int dd[maxn],pos[maxn];

int get(int i,int x){
    return p[i]+x*d[i];
}
int X,Y;
bool cmp(int i,int j){
    int yi=get(i,X),yj=get(j,X);
    return (yi<yj) || (yi==yj && ((tp[i]==-1)==(tp[j]==-1) ? i!=j && (tp[i]==-1)^d[i]:i<j));
}
struct cmp_t{
    bool operator()(int i,const int j){
        return cmp(i,j);
    }
};
set<int,cmp_t> ss;
void add_edge(int u,int v){
    //cout << "edge " << u << ' ' << v << '\n';
    g[u].push_back(make_pair(v,X));
    g[v].push_back(make_pair(u,X));
}

void add(int l,int r){
    if(tp[l]==-1 && tp[r]==-1){
        auto it=ss.lower_bound(r);
        if(it==ss.end() || cmp(r,mt[*it])){
            tp[l]=0,tp[r]=1;
            mt[l]=r,mt[r]=l;
            lx[cnt]=X;
            ly[cnt]=l;
            ry[cnt]=r;
            f[l]=f[r]=cnt++;
            ss.insert(r);
        }
        else{
            int rt=*it,lt=mt[rt];
            tp[l]=1,tp[r]=0;
            ss.insert(l);
            add_edge(f[lt],cnt);
            add_edge(f[lt],cnt+1);
            rx[f[lt]]=lx[cnt]=lx[cnt+1]=X;
            mt[l]=lt,mt[lt]=l;
            mt[r]=rt,mt[rt]=r;
            ly[cnt]=lt,ry[cnt]=l;
            ly[cnt+1]=r,ry[cnt+1]=rt;
            f[l]=f[lt]=cnt++;
            f[r]=f[rt]=cnt++;
        }
    }
    else if(tp[l]==0 && tp[r]==1){
        ss.erase(r);
        tp[l]=tp[r]=-1;
        rx[f[l]]=X;
    }
    else if(tp[l]==1 && tp[r]==0){
        ss.erase(l);
        int lt=mt[l],rt=mt[r];
        tp[l]=tp[r]=-1;
        mt[lt]=rt,mt[rt]=lt;
        add_edge(f[l],cnt);
        add_edge(f[r],cnt);
        rx[f[l]]=rx[f[r]]=lx[cnt]=X;
        ly[cnt]=lt,ry[cnt]=rt;
        f[lt]=f[rt]=cnt++;
    }
    else{
        if(tp[r]==-1) swap(l,r);
        if(tp[r]==1){
            ss.erase(r);
            ss.insert(l);
        }
        int rt=mt[r];
        swap(tp[l],tp[r]);
        mt[l]=rt,mt[rt]=l;
        add_edge(f[r],cnt);
        rx[f[r]]=lx[cnt]=X;
        ly[cnt]=l,ry[cnt]=rt;
        if(tp[l]) swap(ly[cnt],ry[cnt]);
        f[l]=f[rt]=cnt++;
    }
}

int dfs(int u,int par){
    int res=0;
    int len=rx[u]-lx[u]+1,dl=get(ry[u],lx[u])-get(ly[u],lx[u])+1,dr=get(ry[u],rx[u])-get(ly[u],rx[u])+1;
    if(pos[u]==rx[u]) swap(dl,dr);
    res=((dl+dr)*len/2)%mod*dd[u]%mod;
    if(len>1){
        int k=(dr-dl)/(len-1);
        res=(res+len*(len-1)/2%mod*dl%mod)%mod;
        res=(res+len*(len-1)/2%mod*(2*len-1)%mod*inv3%mod*(mod+k)%mod)%mod;
    }
    //cout << u << ' ' << dd[u] << ' ' << dl << ' ' << dr << ' ' << len << '\n';
    //cout << res << '\n';

    for(auto [v,x]:g[u]){
        if(v==par) continue;
        pos[v]=x;dd[v]=dd[u]+abs(x-pos[u]);
        int l=max(get(ly[u],x),get(ly[v],x));
        int r=min(get(ry[u],x),get(ry[v],x));
        res=(res-(r-l+1)*dd[v]%mod+mod)%mod;
        //cout << "del " << (r-l+1)*dd[v]%mod << '\n';
        res=(res+dfs(v,u))%mod;
    }
    return res;
}

int solve(int N,vector<i32> D,vector<i32> L){
    for(int i=0;i<cnt;i++) g[i].clear();
    int n=0;cnt=X=Y=0;
    for(int i=0;i<N;i++){
        int nX=X+L[i]*dx[D[i]];
        int nY=Y+L[i]*dy[D[i]];
        if(X!=nX){
            S[n]=min(X,nX);
            T[n]=max(X,nX);
            d[n]=(nY-Y)/(nX-X);
            p[n]=Y-X*d[n];
            n++;
        }
        X=nX;Y=nY;
    }

    com.clear();
    for(int i=0;i<n;i++) com.push_back(S[i]),com.push_back(T[i]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    for(int i=0;i<sz;i++) h[i].clear();
    for(int i=0;i<n;i++){
        tp[i]=-1;
        h[lower_bound(com.begin(),com.end(),S[i])-com.begin()].push_back(i);
        h[lower_bound(com.begin(),com.end(),T[i])-com.begin()].push_back(i);
    }
    for(int i=0;i<sz;i++){
        X=com[i];
        sort(h[i].begin(),h[i].end(),cmp);
        for(int j=0;j<(int)h[i].size();j+=2) add(h[i][j],h[i][j+1]);
    }
    //for(int i=0;i<cnt;i++) cout << lx[i] << ' ' << rx[i] << ' ' << S[ly[i]] << ' ' << T[ly[i]] << ' ' << S[ry[i]] << ' ' << T[ry[i]] << '\n';

    int rt=-1;
    for(int i=0;i<cnt;i++) if(lx[i]<=0 && 0<=rx[i] && p[ly[i]]<=0 && p[ry[i]]>=0){rt=i;break;}
    dd[rt]=pos[rt]=0;
    return dfs(rt,-1);
}

i32 draw_territory(i32 N, i32 A, i32 B,
                   std::vector<i32> D, std::vector<i32> L) {
    int a=0,b=0;X=Y=0;
    for(int i=0;i<N;i++){
        b+=L[i];
        int nX=X+L[i]*dx[D[i]];
        int nY=Y+L[i]*dy[D[i]];
        a+=X*nY-Y*nX;
        X=nX;Y=nY;
    }
    a=(abs(a)+b)%mod;
    a=a*inv2%mod;
    a=(a+1)%mod;

    B=B*inv2%mod;
    int T=0;
    for(int k=0;k<3;k++){
        T=(T+solve(N,D,L))%mod;
        for(int i=0;i<N;i++) D[i]=D[i]%6+1;
    }
    //cout << T << '\n';
    return (a*A+T*B)%mod;
}
#undef int
