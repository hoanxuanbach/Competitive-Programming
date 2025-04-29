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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=1000005;
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
const int base=101;

int n,m,st[maxn],tt[maxn],Max[maxn];
vector<pii> edge[maxn];
int N,dist[maxn];
string sa[maxn],sb[maxn];
map<string,int> mp;

int get(string D){
    int cur=0,res=0;
    for(char c:D){
        if(c=='d'){
            res+=cur*1440;
            cur=0;
        }
        else if(c==':'){
            res+=cur*60;
            cur=0;
        }
        else cur=cur*10+c-'0';
    }
    res+=cur;
    return res;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        string a,b,s,t;cin >> a >> s >> b >> t;
        sa[i]=a;sb[i]=b;
        if(mp.find(a)==mp.end()) mp[a]=++N;
        if(mp.find(b)==mp.end()) mp[b]=++N;
        st[i]=get(s)*2+1;tt[i]=get(t)*2;
        int xa=mp[a],xb=mp[b];
        edge[xb].push_back({xa,i});
    }
    cin >> m;
    int lst=0,T=-1;
    for(int i=1;i<=m;i++){
        int id;cin >> id;
        int ss=mp[sa[id]];
        Max[ss]=max(Max[ss],st[id]);
        st[id]--;
        lst=tt[id];
        T=mp[sb[id]];
    }
    auto check = [&](int x){
        for(int i=1;i<=N;i++) dist[i]=0;
        dist[T]=x;
        priority_queue<pii> pq;
        pq.push({x,T});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(dist[u]!=d) continue;
            for(auto [v,id]:edge[u]){
                if(d<tt[id]) continue;
                if(st[id]>dist[v]){
                    dist[v]=st[id];
                    pq.push({st[id],v});
                }
            }
        }
        for(int i=1;i<=N;i++){
            if(dist[i]<Max[i]) return false;
        }
        return true;
    };
    int l=0,r=1050000,res=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    if(res==1050000) cout << "stranded\n";
    else cout << max(res-lst,0LL)/2 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
