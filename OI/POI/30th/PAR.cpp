#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first 
#define se second
const int maxn = 2e5+5;

int n;
vector<pii> edge[maxn];
int l[maxn],r[maxn];
vector<int> s[maxn];

bool check(int M){
    bool ok=true;
    auto f = [&](int u,int L,int R){
        l[u]=max(l[u],L);r[u]=min(r[u],R);
        vector<int> ss;
        for(int x:s[u]){
            if(x<l[u] || x>r[u]) continue;
            ss.push_back(x);
        }
        s[u].clear();
        sort(ss.begin(),ss.end());
        for(int x:ss) if(l[u]==x) l[u]++;
        while(!ss.empty() && ss.back()==r[u]) r[u]--,ss.pop_back();
        for(int x:ss) if(l[u]<=x && x<=r[u]) s[u].push_back(x);
    };
    function<void(int,int)> dfs = [&](int u,int p){
        l[u]=1,r[u]=M;
        vector<int> child;
        for(auto [v,w]:edge[u]){
            if(v==p) continue;
            dfs(v,u);
            if(w==1) r[u]=min(r[u],r[v]-1);
            else if(w==2) l[u]=max(l[u],l[v]+1);
            else child.push_back(v);
        }
        for(int v:child){
            int cnt=max(r[v]-l[v]+1-(int)s[v].size(),0);
            f(v,l[u],r[u]);
            int nxt=max(r[v]-l[v]+1-(int)s[v].size(),0);
            if(cnt==1 && nxt==1) s[u].push_back(l[v]);
        }
        f(u,1,M);
        if(l[u]>r[u]) ok=false;
    };
    dfs(1,0);
    return ok;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        edge[i].clear();
        l[i]=r[i]=0;
        s[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w*2});
    }
    int l=1,r=n,res=n+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}