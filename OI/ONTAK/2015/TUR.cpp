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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=2005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

vector<int> K,ord;
bool check[maxn];
int n,m,a[maxn][maxn];

int deg[25],adj[25][25];
vector<int> topo(vector<int> &cc){
    int sz=(int)cc.size();
    memset(deg,0,sizeof(deg));
    memset(adj,0,sizeof(adj));
    for(int i=0;i<sz;i++) for(int j=0;j<sz;j++){
        adj[i][j]=a[cc[i]][cc[j]];
        deg[j]+=adj[i][j];
    }
    vector<int> res;
    queue<int> q;
    for(int i=0;i<sz;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        res.push_back(cc[u]);
        for(int i=0;i<sz;i++){
            if(adj[u][i]){
                deg[i]--;
                if(!deg[i]) q.push(i);
            }
        }
    }

    if((int)res.size()!=cc.size()) return {-1};
    return res;
}

int val[maxn];
int dp[maxn],trace[maxn];
pii cur[25];
vector<int> cal(int mask){
    vector<int> res,rt;
    for(int i=0;i<m;i++){
        if((mask>>i)&1) res.push_back(K[i]);
        else rt.push_back(K[i]);
    }
    rt=topo(rt);
    if(rt[0]==-1) return rt;

    vector<int> lt;
    for(int i=0;i<(int)ord.size();i++){
        bool ok=true;
        for(int j=1;j<(int)rt.size();j++) if(a[ord[i]][rt[j-1]]>a[ord[i]][rt[j]]) ok=false;
        if(!ok) res.push_back(ord[i]);
        else lt.push_back(ord[i]);
    }

    for(int i=0;i<(int)lt.size();i++){
        val[i]=(int)rt.size();
        for(int j=0;j<(int)rt.size();j++){
            if(!a[rt[j]][lt[i]]){
                val[i]=j;
                break;
            }
        }
    }
    int sz=(int)rt.size();
    for(int i=0;i<=sz;i++) cur[i]={0,-1};
    pii Max={0,-1};
    for(int i=0;i<(int)lt.size();i++){
        pii x=cur[val[i]];
        dp[i]=x.fi+1;
        trace[i]=x.se;
        Max=max(Max,{dp[i],i});
        for(int j=val[i];j<=sz;j++) cur[j]=max(cur[j],{dp[i],i});
    }
    int pos=(int)lt.size()-1,p=Max.se;
    while(true){
        for(int i=pos;i>p;i--) res.push_back(lt[i]);
        if(p==-1) break;
        pos=p-1;p=trace[p];
    }
    return res;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin >> a[i][j];
    cin >> m;
    for(int i=0;i<m;i++){
        int x;cin >> x;
        K.push_back(x);
        check[x]=true;
    }
    for(int i=1;i<=n;i++) if(!check[i]) ord.push_back(i);
    sort(ord.begin(),ord.end(),[](int x,int y){
        return a[x][y];
    });

    vector<int> res=K;
    for(int i=0;i<(1<<m)-1;i++){
        vector<int> cc=cal(i);
        if(!cc.empty() && cc[0]==-1) continue;
        if((int)cc.size()<(int)res.size()) res=cc;
    }
    cout << (int)res.size() << '\n';
    for(int x:res) cout << x << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
