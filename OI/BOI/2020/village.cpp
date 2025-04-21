// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int n;
vector<int> edge[maxn];
namespace Min{
    int p[maxn],deg[maxn],dep[maxn],res[maxn],sum;
    bool vis[maxn];
    void dfs(int u,int par){
        p[u]=par;dep[u]=dep[par]+1;
        for(int v:edge[u]){
            if(v==par) continue;
            dfs(v,u);deg[u]++;
        }
    }
    void solve(){
        dfs(1,0);
        set<pii> s;
        for(int i=1;i<=n;i++){
            res[i]=i;
            if(deg[i]==0) s.insert({dep[i],i});
        }
        while(!s.empty()){
            pii x=*s.rbegin();s.erase(x);
            if(p[x.se]==0){
                sum+=2;
                swap(res[edge[1][0]],res[1]);
                break;
            }
            int pa=p[x.se];vis[pa]=true;
            vector<int> add;add.push_back(pa);
            for(int v:edge[pa]){
                if(v==p[pa] || vis[v]) continue;
                add.push_back(v);vis[v]=true;
                s.erase({dep[v],v});
            }
            sum+=(int)add.size()*2-2;
            for(int i=0;i<(int)add.size();i++) res[add[i]]=add[(i+1)%(int)add.size()];
            deg[p[pa]]--;
            if(deg[p[pa]]==0) s.insert({dep[p[pa]],p[pa]});
        }
        //cout << sum << '\n';
        //for(int i=1;i<=n;i++) cout << res[i] << ' ';
        //cout << '\n';
    }
}
namespace Max{
    int child[maxn],dep[maxn],ans=0,cnt=0;
    vector<int> ver[maxn],x;
    deque<int> dq;
    bool cmp(int a,int b){
        return (int)ver[a].size()>(int)ver[b].size();
    }
    void dfs(int u,int par){
        ver[cnt].push_back(u);
        child[u]=1;dep[u]=dep[par]+1;
        ans+=2*dep[u];
        for(int v:edge[u]){
            if(v==par) continue;
            dfs(v,u);child[u]+=child[v];
        }
    }
    int findcen(int u,int par){
        for(int v:edge[u]){
            if(v==par) continue;
            if(child[v]>n/2) return findcen(v,u);
        }
        return u;
    }
    vector<pii> p;
    void solve(){
        dfs(1,0);
        int root=findcen(1,0);
        ans=0;dep[root]=0;
        for(int v:edge[root]){
            cnt++;dfs(v,root);
            x.push_back(cnt);
        }
        cnt++;ver[cnt].push_back(root);
        x.push_back(cnt);
        sort(x.begin(),x.end(),cmp);
        int num=0;
        bool ok=false;
        for(int v:x){
            if(!ok && (num+(int)ver[v].size())>n/2){
                int k=min(2*(num+(int)ver[v].size())-n,n-2*num);
                if(2*(num+(int)ver[v].size())-n<n-2*num){
                    for(int i=0;i<(int)ver[v].size()-k;i++) dq.push_back(ver[v][i]);
                    for(int i=0;i<k;i++){dq.push_back(dq.front());dq.pop_front();}
                    for(int i=(int)ver[v].size()-k;i<(int)ver[v].size();i++) dq.push_front(ver[v][i]);
                }
                else{
                    for(int i=0;i<k;i++){dq.push_back(dq.front());dq.pop_front();}
                    for(int i=0;i<k;i++) dq.push_front(ver[v][i]);
                    for(int i=k;i<(int)ver[v].size();i++) dq.push_back(ver[v][i]);
                }
                ok=true;
            }
            else{
                for(int a:ver[v]) dq.push_back(a);
            }
            num+=(int)ver[v].size();
        }
        for(int v:x){
            for(int a:ver[v]){
                p.push_back({a,dq.back()});
                dq.pop_back();
            }
        }
        sort(p.begin(),p.end());
        //cout << ans << '\n';
        //for(pii a:p) cout << a.second << ' ';
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    Min::solve();
    Max::solve();
    cout << Min::sum << ' ' << Max::ans << '\n';
    for(int i=1;i<=n;i++) cout << Min::res[i] << ' ';
    cout << '\n';
    for(pii a:Max::p) cout << a.second << ' ';
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
