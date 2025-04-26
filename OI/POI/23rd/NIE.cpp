#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
#define pii pair<int,int>
#define fi first 
#define se second;
const int mod = 1e9+7;

int n,m;
vector<int> edge[maxn];
bool tree=true;
int num[maxn],low[maxn],T;
vector<vector<pii>> S;

vector<pii> e;
void dfs(int u,int p){
    num[u]=low[u]=++T;
    for(int v:edge[u]){
        if(v==p) continue;
        if(!num[v]){
            e.push_back({u,v});dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=num[u]){
                vector<pii> cc;
                while(e.back()!=make_pair(u,v)){
                    cc.push_back(e.back());
                    e.pop_back();
                }
                cc.push_back(e.back());
                e.pop_back();
                S.push_back(cc);
            }
        }
        else{
            low[u]=min(low[u],num[v]),tree=false;
            if(num[v]<num[u]) e.push_back({u,v});
        }
    }
}

bool vis[maxn];
vector<int> adj[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    if(tree){
        cout << "BRAK\n";
        return 0;
    }
    int sz=-1,cnt=0;
    for(auto E:S){
        if((int)E.size()<=1) continue;
        vector<int> V;
        for(auto [u,v]:E){
            if(adj[u].empty()) V.push_back(u);
            adj[u].push_back(v);
            if(adj[v].empty()) V.push_back(v); 
            adj[v].push_back(u);
        }
        int deg=0;
        for(int v:V) deg=max(deg,(int)adj[v].size());
        if(deg<=2){
            int cur=(int)V.size();
            if(sz==-1) sz=cur,cnt=1;
            else if(sz==cur) cnt++;
            else{
                cout << "NIE\n";
                return 0;
            }
        }
        else{
            bool check=true;
            vector<int> A;
            for(int v:V){
                int dd=(int)adj[v].size();
                if(dd>2){
                    if(dd!=deg) check=false;
                    else A.push_back(v);
                }
            }
            if((int)A.size()!=2) check=false;
            if(!check){
                cout << "NIE\n";
                return 0;
            }
            int lsz=-1,lcnt=0;
            for(int x:V){
                if(x==A[0] || x==A[1] || vis[x]) continue;
                int len=0;
                vector<int> q;
                q.push_back(x);vis[x]=true;
                while(!q.empty()){
                    int u=q.back();q.pop_back();
                    len++;
                    for(int v:adj[u]){
                        if(v==A[0] || v==A[1] || vis[v]) continue;
                        q.push_back(v);vis[v]=true;
                    }
                }
                if(lsz==-1) lsz=len,lcnt=1;
                else if(lsz==len) lcnt++;
                else check=false;
            }
            if(!check){
                cout << "NIE\n";
                return 0;
            }
            int cur=2*lsz+2;
            if(sz==-1) sz=cur,cnt=1LL*lcnt*(lcnt-1)/2%mod;
            else if(sz==cur) (cnt+=1LL*lcnt*(lcnt-1)/2%mod)%=mod;
            else{
                cout << "NIE\n";
                return 0;
            }
        }
        for(int v:V) adj[v].clear(),vis[v]=false;
    }
    cout << "TAK\n";
    cout << sz << ' ' << 1LL*cnt*2*sz%mod << '\n';
}