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
const int mod=1000000000000000069;
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
const int base=131;

int n,m,pw[maxn];
struct hashing{
    vector<int> h;
    void init(string s){
        h.assign((int)s.length()+1,0);
        for(int i=1;i<=(int)s.length();i++) h[i]=((__int128)h[i-1]*base%mod+s[i-1]-'a'+1)%mod;
    }
    int get_hash(int l,int r){
        return (h[r]-(__int128)h[l-1]*pw[r-l+1]%mod+mod)%mod;
    }
}A[maxn],B[maxn];

void solve(){
    cin >> n >> m;
    pw[0]=1;
    for(int i=1;i<=m;i++) pw[i]=(__int128)pw[i-1]*base%mod;
    for(int i=0;i<n;i++){
        string s;cin >> s;
        A[i].init(s);
    }
    for(int i=0;i<n;i++){
        string s;cin >> s;
        B[i].init(s);
    }
    for(int d=0;d<m;d++){
        int pos=0;
        map<pair<int,bool>,int> mp;
        vector<vector<pii>> edge;
        for(int i=0;i<n;i++){
            int lt=A[i].get_hash(1,d),rt=A[i].get_hash(d+1,m);
            if(mp.find({lt,0})==mp.end()){
                mp[{lt,0}]=pos++;
                edge.push_back({});
            }
            if(mp.find({rt,1})==mp.end()){
                mp[{rt,1}]=pos++;
                edge.push_back({});
            }
            edge[mp[{lt,0}]].push_back({mp[{rt,1}],i});
        }
        for(int i=0;i<n;i++){
            int lt=B[i].get_hash(1,m-d),rt=B[i].get_hash(m-d+1,m);
            if(mp.find({lt,1})==mp.end()){
                mp[{lt,1}]=pos++;
                edge.push_back({});
            }
            if(mp.find({rt,0})==mp.end()){
                mp[{rt,0}]=pos++;
                edge.push_back({});
            }
            edge[mp[{lt,1}]].push_back({mp[{rt,0}],n+i});
        }
        vector<int> in(pos,0),out(pos,0);
        for(int i=0;i<pos;i++){
            out[i]=(int)edge[i].size();
            for(auto [v,id]:edge[i]) in[v]++;
        }
        bool flag=true;
        for(int i=0;i<pos;i++) flag &= (in[i]==out[i]);
        if(!flag) continue;
        vector<int> res;

        function<void(int)> dfs = [&](int u){
            while((int)edge[u].size()){
                pii x=edge[u].back();edge[u].pop_back();
                dfs(x.fi);res.push_back(x.se);
            }
        };

        dfs(0);
        reverse(res.begin(),res.end());
        if((int)res.size()==2*n){
            for(int i=0;i<2*n;i++) if(res[i]<n) cout << res[i]+1 << ' ';
            cout << '\n';
            for(int i=0;i<2*n;i++) if(res[i]>=n) cout << res[i]-n+1 << ' ';
            cout << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
