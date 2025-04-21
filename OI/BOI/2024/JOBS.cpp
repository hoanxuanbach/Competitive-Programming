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
const int maxn=300005;
const int B=650;
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
 
int n,x[maxn],S,cc[maxn];
vector<int> edge[maxn];
set<pii> s[maxn];
 
void dfs(int u){
    //cout << u << endl;
    int v=0;
    for(int V:edge[u]){
        dfs(V);
        if((int)s[V].size()>(int)s[v].size()) v=V;
    }
    if(v) s[u].swap(s[v]);
 
    vector<pii> cur;
    for(int V:edge[u]) if(V!=v){
        for(auto a:s[V]) cur.push_back(a);
    }
    sort(cur.begin(),cur.end());
    int ss=max(0LL,-x[u]),cc=ss+x[u];
    vector<pii> val;
    auto l=s[u].begin();
 
    for(auto a:cur){
        while(l!=s[u].end() && l->fi<=cc) cc+=l->se,l=s[u].erase(l);
        auto r=s[u].upper_bound(mpp(a.fi,inf));
 
        if(l!=s[u].end() && r!=s[u].begin()){
            auto it=r;it=prev(it);
            pii lst=*it;
            if(*l<=lst){
                while(l!=s[u].end() && *l<=lst && cc-ss<=0) ss+=l->fi-cc,cc=l->fi+l->se,l=s[u].erase(l);
                if(l!=s[u].end() && *l<=lst){
                    val.push_back({ss,cc-ss});
                    s[u].erase(lst);
                    ss=lst.fi;cc=lst.fi+lst.se;
                }
            }
            l=s[u].upper_bound(mpp(a.fi,inf));
        }
 
        if(a.fi<=cc) cc+=a.se;
        else{
            if(cc-ss>0){
                val.push_back({ss,cc-ss});
                cc=a.fi+a.se;ss=a.fi;
            }
            else ss+=a.fi-cc,cc=a.fi+a.se;
        }
    }
 
    while(l!=s[u].end() && l->fi<=cc) cc+=l->se,l=s[u].erase(l);
    auto r=s[u].end();
    if(l!=s[u].end() && r!=s[u].begin()){
        auto it=r;it=prev(it);
        pii lst=*it;
        if(*l<=lst){
            while(l!=s[u].end() && *l<=lst && cc-ss<=0) ss+=l->fi-cc,cc=l->fi+l->se,l=s[u].erase(l);
            if(l!=s[u].end() && *l<=lst){
                val.push_back({ss,cc-ss});
                s[u].erase(lst);
                ss=lst.fi;cc=lst.fi+lst.se;
            }
        }
    }
 
    if(cc-ss>0) val.push_back({ss,cc-ss});
    for(auto a:val) s[u].insert(a);
    //cout << "dfs: " << u << '\n';
    //for(auto a:s[u]) cout << a.fi << ' ' << a.se << '\n';
}
/*
void sub3_solve(){
    vector<vector<pii>> val;
    int mn=0,cur=0;
    for(int i=1;i<=n;i++){
        if(cc[i]){
            val.emplace_back();
            mn=cur=0;
        }
        cur+=x[i];mn=min(mn,cur);
        if(cur>=0) val.back().emplace_back(mn,cur),cur=mn=0;
    }
    int sz=(int)val.size();
    priority_queue<pii> pq;
    for(int i=0;i<sz;i++){
        reverse(val[i].begin(),val[i].end());
        pq.push({val[i].back().fi,i});
    }
    int nS=S;
    while(!pq.empty()){
        auto [mn,id]=pq.top();pq.pop();
        if(nS+mn<0) break;
        nS+=val[id].back().se;val[id].pop_back();
        if(!val[id].empty()) pq.push({val[id].back().fi,id});
    }
    cout << nS-S << '\n';
}
*/
 
void solve(){
    cin >> n >> S;
    bool check=true;
    for(int i=1;i<=n;i++){
        int p;cin >> x[i] >> p;
        edge[p].push_back(i);
        if(!p) cc[i]=1;
        //if(p && p!=i-1) check=false;
    }
    dfs(0);
    int st=S;
    while(!s[0].empty()){
        pii val = *s[0].begin();
        if(val.fi<=S) S+=val.se;
        s[0].erase(s[0].begin());
    }
    cout << S-st << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}