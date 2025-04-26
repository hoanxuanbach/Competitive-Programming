#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,m,t;
namespace solve3{
    int cnt[3];
    vector<int> edge[maxn];
    bool vis[maxn];
    map<pii,int> mp;
    void dfs(int u){
        vis[u]=true;cnt[(int)edge[u].size()]++;
        for(int v:edge[u]){
            if(!vis[v]) dfs(v);
        }
    }
    void solve(){
        for(int i=1;i<=m;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                cnt[0]=cnt[1]=cnt[2]=0;
                dfs(i);
                if(cnt[0]!=0) mp[{1,1}]++;
                else if(cnt[1]!=0) mp[{1,cnt[2]+2}]++;
                else mp[{2,cnt[2]}]++;
            }
        }
        for(int i=1;i<=t;i++){
            int k,ans=1;cin >> k;
            for(auto x:mp){
                if(x.fi.fi==1) ans=(ans*power(k*power(k-1,x.fi.se-1)%mod,x.se)%mod)%mod;
                else{
                    if(x.fi.se%2==0) ans=(ans*power(k*(power(k-1,x.fi.se)+(k-1))%mod*power(k,mod-2)%mod,x.se))%mod;
                    else ans=(ans*power(k*(power(k-1,x.fi.se)+mod-(k-1))%mod*power(k,mod-2)%mod,x.se))%mod;
                }
            }
            cout << ans << '\n';
        }
    }
}
namespace solve1{
    vector<int> edge[maxn];
    int f[20],dp[(1<<15)+5],fac[20],mask,ok[20];
    bool check[(1<<15)+5];
    void backtrack(int u){
        if(u==n){
            check[mask]=true;
            return;
        }
        backtrack(u+1);
        if(ok[u+1]==0){
            for(int v:edge[u+1]) ok[v]++;
            mask^=(1<<u);
            backtrack(u+1);
            mask^=(1<<u);
            for(int v:edge[u+1]) ok[v]--;
        }
    }
    int cal(int k,int i){
        int res=1;
        for(int j=0;j<i;j++) res=res*(k-j)%mod;
        res=res*power(fac[i],mod-2)%mod;
        return res;
    }
    void solve(){
        for(int i=1;i<=m;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        backtrack(0);dp[0]=1;fac[0]=1;
        for(int i=1;i<=n;i++){
            fac[i]=fac[i-1]*i%mod;
            for(int j=(1<<n)-1;j>=0;j--){
                dp[j]=0;
                for(int k=j;k;k=(k-1)&j){
                    if(!check[k]) continue;
                    dp[j]=(dp[j]+dp[j^k])%mod;
                }
            }
            f[i]=dp[(1<<n)-1];
        }
        for(int i=1;i<=t;i++){
            int k,ans=0;cin >> k;
            for(int j=1;j<=min(n,k);j++) ans=(ans+f[j]*cal(k,j))%mod;
            cout << ans << '\n';
        }
    }
}
namespace solve2{
    vector<pii> e;
    vector<int> p;
    int num[50],l=0,sz;
    bool vis[50];
    vector<int> edge[50];
    void dfs2(int u){
        vis[u]=true;
        for(int v:edge[u]){
            if(!vis[v]) dfs2(v);
        }
    }
    void backtrack2(int u){
        if(u==m){
            int cc=0;
            for(int i=1;i<=sz;i++) vis[i]=false;
            for(int i=1;i<=sz;i++){
                if(!vis[i]){cc++;dfs2(i);}
            }
            if(l%2==0) num[cc]++;
            else num[cc]--;
            return;
        }
        for(int b=0;b<=1;b++){
            if(b){
                edge[e[u].first].push_back(e[u].second);
                edge[e[u].second].push_back(e[u].first);
                l++;
            }
            backtrack2(u+1);
            if(b){
                l--;
                edge[e[u].first].pop_back();
                edge[e[u].second].pop_back();
            }
        }
    }
    void solve(){
        for(int i=1;i<=m;i++){
            int u,v;cin >> u >> v;
            e.push_back({u,v});
            p.push_back(u);p.push_back(v);
        }
        sort(p.begin(),p.end());
        p.erase(unique(p.begin(),p.end()),p.end());
        for(pii &x:e){
            x.first=lower_bound(p.begin(),p.end(),x.first)-p.begin()+1;
            x.second=lower_bound(p.begin(),p.end(),x.second)-p.begin()+1;
        }
        sz=(int)p.size();
        int a=n-sz;
        backtrack2(0);
        for(int i=1;i<=t;i++){
            int ans=0,k;cin >> k;
            for(int j=1;j<=sz;j++) ans=(ans+num[j]*power(k,j)%mod+mod)%mod;
            if(m!=0) ans=(ans*power(k,a))%mod;
            else ans=power(k,n);
            cout << ans << '\n';
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> t;
    if(n<=15) solve1::solve();
    else if(m<=24) solve2::solve();
    else solve3::solve();
}
