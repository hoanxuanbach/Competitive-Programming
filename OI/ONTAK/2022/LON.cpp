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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,deg[maxn],pos[maxn];
bool used[maxn];
vector<pii> edge[maxn];
char c[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        deg[u]++;deg[v]++;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    for(int i=1;i<=n;i++) cin >> c[i];
    bool check=true;
    for(int i=1;i<=n;i++) if(deg[i]&1) check=false;
    if(!check){
        cout << "NO\n";
        return;
    }
    vector<int> res;
    stack<int> st;
    for(int i=1;i<=n;i++) if(deg[i]){
        st.push(i);break;
    }
    while(!st.empty()){
        int u=st.top();
        while(pos[u]<(int)edge[u].size() && used[edge[u][pos[u]].se]) pos[u]++;
        if(pos[u]==(int)edge[u].size()){
            res.push_back(u);
            st.pop();
        }
        else{
            used[edge[u][pos[u]].se]=true;
            st.push(edge[u][pos[u]].fi);
        }
    }
    for(int i=1;i<=m;i++){
        if(!used[i]){
            cout << "NO\n";
            return;
        }
    }
    res.pop_back();
    int cur=0,p=-1,Min=0;
    for(int i=0;i<(int)res.size();i++){
        cur+=(c[res[i]]=='('?1:-1);
        if(cur<Min) Min=cur,p=i;
    }
    if(cur!=0){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int i=p+1;i<(int)res.size();i++) cout << res[i] << ' ';
    for(int i=0;i<=p;i++) cout << res[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
