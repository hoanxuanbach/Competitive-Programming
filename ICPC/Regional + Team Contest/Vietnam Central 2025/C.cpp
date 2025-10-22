#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

#define pii pair<int,int>
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

#define matrix array<array<int,2>,2>

const int LG = 18;

void solve(){
    int n;cin >> n;
    string S;cin >> S;
    int q;cin >> q;

    int k=0;
    vector<int> f(n),pos;
    vector<vector<int>> p(n/2,vector<int>(LG,0));
    vector<vector<int>> adj(n/2);

    for(int i=0;i<n;i++){
        if(S[i]=='('){
            p[k][0]=(pos.empty()?-1:f[pos.back()]);
            if(p[k][0]!=-1) adj[p[k][0]].push_back(k);
            f[i]=k++;pos.push_back(i);
        }
        else{
            f[i]=f[pos.back()];
            pos.pop_back();
        }
    }

    n=k;
    vector<int> d(n),g(n);
    vector<vector<matrix>> nxt(n,vector<matrix>(LG,matrix{array<int,2>{0LL,1LL},{1LL,0LL}}));

    int pp=0;
    for(int u=0;u<n;u++){
        if(p[u][0]==-1) g[u]=pp++;
        int sz=(int)adj[u].size();
        for(int i=0;i<(int)adj[u].size();i++){
            matrix cur;
            cur[0][0]=2*i+1;
            cur[1][1]=2*(sz-i-1)+1;
            cur[0][0]=min(cur[0][0],cur[1][1]+2);
            cur[1][1]=min(cur[1][1],cur[0][0]+2);
            cur[0][1]=min(cur[0][0],cur[1][1])+1;
            cur[1][0]=min(cur[0][0],cur[1][1])+1;
            int v=adj[u][i];g[v]=i;
            nxt[v][0]=cur;d[v]=d[u]+1;
        }
    }
    
    auto unite = [&](matrix a,matrix b){
        matrix c;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
            c[i][j]=inf;
            for(int k=0;k<=1;k++) c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
        }
        return c;
    };
    for(int j=1;j<LG;j++) for(int i=0;i<n;i++){
        if(p[i][j-1]==-1) p[i][j]=-1;
        else{
            p[i][j]=p[p[i][j-1]][j-1];
            nxt[i][j]=unite(nxt[i][j-1],nxt[p[i][j-1]][j-1]);
        }
    }
    
    auto get = [&](int u,int v,int x,int y){
        matrix cu={array<int,2>{0LL,1LL},{1LL,0LL}};
        matrix cv={array<int,2>{0LL,1LL},{1LL,0LL}};
        if(d[u]>d[v]) swap(u,v),swap(x,y);
        for(int i=0;i<LG;i++) if((d[v]-d[u])>>i&1) cv=unite(cv,nxt[v][i]),v=p[v][i];
        if(u==v){
            cout << cv[y][x] << '\n';
            return;
        }
        //cout << u << ' ' << v << ' ' << x << ' ' << y << '\n';
        for(int i=LG-1;i>=0;i--){
            if(p[u][i]==p[v][i]) continue;
            cu=unite(cu,nxt[u][i]);
            cv=unite(cv,nxt[v][i]);
            u=p[u][i],v=p[v][i];
        }
        int res=inf;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){

            int cur=cu[x][i]+cv[y][j]+2*(abs(g[u]-g[v])-1)+1;
            if(g[u]>g[v]) cur+=i+(!j);
            else cur+=j+(!i);
            //cout << i << ' ' << j << ' ' << g[u] << ' ' << g[v] << ' ' << cur << '\n';
            res=min(res,cur);
        }
        if(p[u][0]!=-1){
            cu=unite(cu,nxt[u][0]);
            cv=unite(cv,nxt[v][0]);
            swap(cv[0][1],cv[1][0]);
            cu=unite(cu,cv);
            res=min(res,cu[x][y]);
        }
        cout << res << '\n';
    };
    for(int i=0;i<q;i++){
        int x,y;cin >> x >> y;x--;y--;
        int fx=f[x],tx=(S[x]==')');
        int fy=f[y],ty=(S[y]==')');
        get(fx,fy,tx,ty);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

/*
3 3 1 1
3
3 3
3 4
4 3
3 2
*/
