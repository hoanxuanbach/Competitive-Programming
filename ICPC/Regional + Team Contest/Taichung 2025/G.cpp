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

const int N = 1000;
vector<int> mul(vector<int> a,vector<vector<int>> b){
    int n=(int)a.size();
    vector<int> c(n);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) c[i]=(c[i]+a[j]*b[j][i])%mod;
    return c;
}
vector<vector<int>> mul(vector<vector<int>> a,vector<vector<int>> b){
    int n=(int)a.size();
    vector<vector<int>> c(n,vector<int>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    return c;
}


void solve(){
    string S,Z;cin >> S >> Z;
    int M;cin >> M;

    vector<int> p(N+3);
    vector<array<int,2>> nxt(N+3,{-1,-1});
    iota(p.begin(),p.end(),0);

    function<int(int)> fp = [&](int u){
        if(u!=p[u]) return p[u]=fp(p[u]);
        return u;
    };
    function<void(int,int)> unite = [&](int u,int v){ 
        u=fp(u);v=fp(v);
        if(u==v) return;
        //cout << "unite " << u << ' ' << v << '\n';
        p[v]=u;
        for(int k=0;k<=1;k++){
            int x=nxt[u][k],y=nxt[v][k];
            if(x!=-1 && y!=-1) unite(x,y);
            else if(x==-1 && y!=-1) nxt[u][k]=y;
        }
    };

    int T=1,cnt=1;
    bool flag=true;
    while(flag){
        //cout << T << endl;
        //for(int i=0;i<T;i++) if(fp(i)==i) cout << i << ' ' << nxt[i][0] << ' ' << nxt[i][1] << '\n';
        flag=false;
        for(int x=T-1;x>=0;x--){
            if(fp(x)!=x) continue;
            if(nxt[x][0]==-1){
                int y=T++;
                nxt[x][0]=y;
                nxt[y][0]=x;
                flag=true;
            }
            if(nxt[x][1]==-1){
                int y=T++,z=T++;
                nxt[x][1]=y;
                nxt[y][1]=z;
                nxt[z][1]=x;
                flag=true;
            }
        }
        //cout << "end" << endl;
        for(int x=0;x<T;x++){
            if(fp(x)!=x) continue;
            int y=x;
            bool del=true;
            for(char c:S){
                int t=(c=='B');
                if(nxt[y][t]==-1){
                    del=false;
                    break;
                }
                y=fp(nxt[y][t]);
            }
            if(!del || x==y) continue;
            flag=true;
            unite(x,y);
        }
        if(T>=N) break;
    }

    int n=0;
    vector<int> f(T,-1);
    for(int i=0;i<T;i++) if(fp(i)==i) f[i]=n++;

    vector<vector<int>> adj(n,vector<int>(n,0));
    for(int x=0;x<T;x++) if(f[x]!=-1){
        for(int k=0;k<=1;k++){
            int y=fp(nxt[x][k]);
            adj[f[x]][f[y]]++;
        }
    }

    int fst=fp(0),lst=fst;
    for(char c:Z){
        int t=(c=='B');
        lst=fp(nxt[lst][t]);
    }
    fst=f[fst];lst=f[lst];

    vector<int> cur(n);cur[fst]++;
    while(M){
        if(M&1) cur=mul(cur,adj);
        adj=mul(adj,adj);M>>=1;
    }
    cout << cur[lst] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
