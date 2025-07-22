#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2=(mod+1)/2;
const int maxn = 2e3+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

void init(){

}

void solve(){
    int n,m;cin >> n >> m;
    string S;cin >> S;

    vector<int> p(n+1);
    for(int i=1;i<=n;i++) cin >> p[i];

    vector<vector<pii>> edge(n+1);

    vector<int> res;
    vector<pii> E(m);
    vector<bool> del(m+1);

    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i+1});
        edge[v].push_back({u,i+1});
        E[i]={u,v};
        if(S[i]=='1'){
            swap(p[u],p[v]);
            res.push_back(i+1);
        }
    }

    vector<vector<pii>> adj(n+1);
    vector<int> deg(n+1);
    vector<bool> vis(n+1);
    
    function<void(int)> dfs_tree = [&](int u){
        vis[u]=true;
        for(auto [v,id]:edge[u]){
            if(!vis[v]){
                adj[u].push_back({v,id});
                adj[v].push_back({u,id});
                //cout << "tree " << u << ' ' << v << ' ' << id << '\n';
                deg[u]++;deg[v]++;
                dfs_tree(v);
            }
        }
    };
    dfs_tree(1);

    int cnt=2;
    while(true){
        int x=-1;
        for(int i=1;i<=n;i++) if(deg[i]==1) x=i;
        if(x==-1) break;

        int k=-1;
        for(int i=1;i<=n;i++) if(p[i]==x) k=i;

        if(k!=x){
            vector<int> path;
            function<bool(int,int)> dfs = [&](int u,int p){
                if(u==k) return true;
                for(auto [v,id]:adj[u]){
                    if(v==p) continue;
                    if(dfs(v,u)){
                        path.push_back(id);
                        return true;
                    }
                }
                return false;
            };
            dfs(x,-1);
            reverse(path.begin(),path.end());
            
            auto mov = [&](int id){
                res.push_back(id);
                auto [u,v]=E[id-1];
                swap(p[u],p[v]);
            };
            if((int)path.size()>=2){
                mov(path[0]);
                for(int i=(int)path.size()-1;i>=0;i--) mov(path[i]);
                for(int i=1;i<(int)path.size();i++) mov(path[i]);
            }
            else{
                int cid=-1;
                for(auto [v,id]:adj[k]){
                    if(del[id] || id==path[0]) continue;
                    cid=id;
                }
                if(cid==-1){
                    cout << "NO\n";
                    return;
                }
                mov(cid);
                mov(path[0]);
                mov(cid);
                mov(path[0]);
            }
        }

        for(auto [v,id]:adj[x]) if(!del[id]){
            deg[x]--,deg[v]--,del[id]=true;
            //cout << "del " << id << '\n';
        }
        /*
        cout << x << '\n';
        for(int i=1;i<=n;i++) cout << p[i] << ' ';
        cout << '\n';
        */
    }

    cout << "YES\n";
    cout << (int)res.size() << '\n';
    for(int x:res) cout << x << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}