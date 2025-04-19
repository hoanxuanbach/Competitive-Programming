#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first 
#define se second
const int maxn = 4e6+5;
vector<pii> qq[maxn];
vector<int> adj[maxn];
bool root[maxn];

vector<pii> ss[maxn],gg[maxn];

int bit[maxn],T,T2;
void update(int x,int val){
    //cout << "update " << x << ' ' << val << '\n';
    for(int i=x;i<=T2;i+=(i&(-i))) bit[i]+=val;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    //cout << "query " << x << ' ' << res << '\n';
    return res;
}

void solve(){
    int N;cin >> N;
    vector<int> P(N+1),K(N+1);
    vector<vector<int>> edge(N+1);

    for(int i=2;i<=N;i++) cin >> P[i],edge[P[i]].push_back(i);
    for(int i=1;i<=N;i++) cin >> K[i];

    int D=0;
    vector<int> L(N+1),R(N+1),dep(N+1);
    function<void(int)> dfs = [&](int u){
        D=max(D,dep[u]);
        L[u]=++T;
        for(int v:edge[u]) dep[v]=dep[u]+1,dfs(v);
        R[u]=T;
    };
    dfs(1);
    
    vector<int> f(D+1);
    iota(f.begin(),f.end(),0);
    
    for(int i=1;i<=N;i++){
        qq[dep[i]].push_back({i,K[i]});
        //cout << "qq " << dep[i] << ' ' << i << ' ' << K[i] << '\n';
    }
    T=D;

    int Q;cin >> Q;
    vector<int> res(Q+1,-1);
    for(int i=1;i<=Q;i++){
        int t;cin >> t;
        if(t==1){
            int x,y;cin >> x >> y;
            if(x>D) continue;
            adj[f[y]].push_back(f[x]);
            //cout << "add_edge " << y << ' ' << x << ' ' << f[y] << ' ' << f[x] << '\n';
            root[f[x]]=true,f[x]=++T;
        }
        else if(t==2){
            int v,val;cin >> v >> val;
            qq[f[dep[v]]].push_back({v,val});
            //cout << "qq " << f[dep[v]] << ' ' << v << ' ' << val << '\n';
        }
        else{
            res[i]=0;
            int v;cin >> v;
            int d=dep[v];
            qq[f[d]].push_back({-i,v});
            //cout << "qq " << f[d] << ' ' << -i << ' ' << v << '\n';
            adj[++T].push_back(f[d]);
            //cout << "add_edge " << T << ' ' << f[d] << '\n';
            root[f[d]]=true,f[d]=T;
        }
    }

    vector<int> L2(T+1),R2(T+1);
    function<void(int)> dfs2 = [&](int u){
        L2[u]=++T2;
        for(int v:adj[u]) dfs2(v);
        R2[u]=T2;
    };
    for(int i=0;i<=T;i++) if(!root[i]) dfs2(i);

    for(int i=0;i<=T;i++){
        for(auto [id,v]:qq[i]){
            if(id>0){
                ss[L[id]].push_back({L2[i],v});
                //cout << "UU " << L[id] << ' ' << L2[i] << ' ' << v << '\n';
            }
            else{
                //L[v],R[v], L2[i],R2[i]
                //cout << "QQ " << -id << ' ' << v << ' ' << i << ' ' << L[v] << ' ' << R[v] << ' ' << L2[i] << ' ' << R2[i] << '\n';
                gg[R[v]].push_back({R2[i],-id});
                gg[R[v]].push_back({L2[i]-1,id});
                gg[L[v]-1].push_back({R2[i],id});
                gg[L[v]-1].push_back({L2[i]-1,-id});
            }
        }
    }
    for(int i=1;i<=N;i++){
        for(auto [x,val]:ss[i]) update(x,val);
        for(auto [x,id]:gg[i]){
            int val=query(x);
            //cout << x << ' ' << id << ' ' << val << '\n';
            if(id<0) res[-id]-=val;
            else res[id]+=val;
        }
    }
    for(int i=1;i<=Q;i++) if(res[i]!=-1) cout << res[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
