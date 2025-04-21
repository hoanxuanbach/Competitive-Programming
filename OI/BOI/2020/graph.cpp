#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second

int n,m,a[maxn],b[maxn];
vector<pii> edge[maxn];
bool vis[maxn];
vector<int> cc;
double res[maxn];

void dfs(int u){
    vis[u]=true;
    cc.push_back(u);
    for(auto [v,w]:edge[u]){
        if(vis[v]) continue;
        a[v]=-a[u],b[v]=w-b[u];
        dfs(v);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    bool check=true;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            cc.clear();
            a[i]=1;dfs(i);

            bool ok=false;
            int cA=-1,cB=-1;
            for(int u:cc) for(auto [v,w]:edge[u]){
                int A=a[u]+a[v],B=b[u]+b[v];
                if(A==0){
                    if(B!=w) check=false;
                }
                else{
                    B=w-B;
                    if(!ok) cA=A,cB=B,ok=true;
                    else if(cA*B!=cB*A) check=false;
                }
            }
            if(!check){
                cout << "NO\n";
                return 0;
            }
            double x;
            if(ok) x=(double)cB/cA;
            else{
                vector<int> val;
                for(int u:cc) val.push_back(-a[u]*b[u]);
                sort(val.begin(),val.end());
                x=val[(int)val.size()/2];
            }
            for(int u:cc) res[u]=a[u]*x+b[u];
        }
    }
    cout << "YES\n";
    for(int i=1;i<=n;i++) cout << setprecision(6) << fixed << res[i] << ' ';
    cout << '\n';
}
