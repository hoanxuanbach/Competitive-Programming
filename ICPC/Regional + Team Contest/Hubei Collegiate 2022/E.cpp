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
#define pii pair<int,int>
const int inf=2e9;
const int mod=998244353;
const int maxl=35;
const int maxs=12000005;
const int maxn=200005;
const int maxa=1000005;
int n,q,a[maxn],b[maxn],pos[maxl],Max[maxn];
struct node{
    int nxt[2],num=0,ss=0;
    node(){memset(nxt,0,sizeof(nxt));}
};
namespace Trie{
    int sz=0;
    node T[maxs];
    void build(){
        sz=1;
    }
    void dfs(int u){
        Max[T[u].ss]=max(Max[T[u].ss],T[u].num);
        for(int i=0;i<2;i++){
            if(T[u].nxt[i]!=0){
                T[T[u].nxt[i]].ss=T[u].ss+i;T[T[u].nxt[i]].num|=T[u].num;
                dfs(T[u].nxt[i]);
            }
        }
    }
    void add(int p){
        int u=0;
        for(int i=n;i>=1;i--){
            int sw=((a[i]>>p)&1)^b[i]^1;
            if((a[i]>>p)&1){
                if(T[u].nxt[sw^1]==0) T[u].nxt[sw^1]=sz++;
                int pp=T[u].nxt[sw^1];
                T[pp].num|=(1<<p);
            }
            if(T[u].nxt[sw]==0) T[u].nxt[sw]=sz++;
            u=T[u].nxt[sw];
        }
        pos[p]=u;
    }
}
void solve(){
    Trie::build();
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    for(int i=0;i<=29;i++) Trie::add(i);
    Trie::dfs(0);
    for(int i=1;i<=n;i++) Max[i]=max(Max[i],Max[i-1]);
    for(int i=1;i<=q;i++){
        int x,k;cin >> x >> k;
        int ans=Max[k];
        for(int j=0;j<=29;j++){
            if(x&(1<<j)){
                Trie::T[pos[j]].num+=(1<<j);
                if(Trie::T[pos[j]].ss<=k) ans=max(ans,Trie::T[pos[j]].num);
            }
        }
        for(int j=0;j<=29;j++){
            if(x&(1<<j)) Trie::T[pos[j]].num-=(1<<j);
        }
        cout << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
