#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define pii pair<int,int>
namespace fmap{
    int tm=0,pos[maxn];
    void clear(){tm++;}
    bool find(int x){
        if(pos[x]==tm) return true;
        return false;
    }
    void insert(int x){
        pos[x]=tm;
    }
}
const int bl=2e2+20;
int sz[maxn],n,m,q,dp[maxn];
vector<int> edge[maxn];
pii d[maxn][bl],tmp[2*bl];
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){sz[i]=1;d[i][0]={-1,i};}
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<sz[i];j++) d[i][j].first++;
        for(int v:edge[i]){
            merge(d[v],d[v]+sz[v],d[i],d[i]+sz[i],tmp,greater<pii>());
            int cc=sz[i]+sz[v];
            sz[v]=0;
            fmap::clear();
            for(int j=0;j<cc;j++){
                if(fmap::find(tmp[j].second)) continue;
                d[v][sz[v]++]=tmp[j];
                fmap::insert(tmp[j].second);
                if(sz[v]==bl) break;
            }
        }
    }
    for(int i=1;i<=q;i++){
        int u,k;cin >> u >> k;
        fmap::clear();
        for(int i=1;i<=k;i++){
            int a;cin >> a;
            fmap::insert(a);
        }
        if(k<bl){
            int ans=-1;
            for(int j=0;j<sz[u];j++){
                if(fmap::find(d[u][j].second)) continue;
                ans=d[u][j].first;
                break;
            }
            cout << ans << '\n';
        }
        else{
            for(int i=1;i<=n;i++){
                if(fmap::find(i)) dp[i]=-1;
                else dp[i]=0;
            }
            for(int i=1;i<=n;i++){
                if(dp[i]==-1) continue;
                for(int v:edge[i]) dp[v]=max(dp[v],dp[i]+1);
            }
            cout << dp[u] << '\n';
        }
    }
}