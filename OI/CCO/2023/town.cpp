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
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,a[maxn];
map<int,vector<int>> mp;

struct BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}f0,f1;

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        mp[-abs(a[i])].push_back(i);
    }
    int t=0;
    for(int i=1;i<=n;i++) f0.update(i,1);
    vector<int> dp(2,inf);dp[0]=0;
    for(auto [x,v]:mp){
        if(x==0) break;
        vector<int> ndp(2,inf);
        int sz=(int)v.size(),pt=t;
        for(int id:v) f0.update(id,-1),t++;
        //cout << "* " << -x << '\n';
        for(int t0=0;t0<=1;t0++){
            vector<vector<int>> cc(2);
            for(int id:v){
                int k=(id&1)^(a[id]>0);
                cc[k].push_back(id);
            }
            int t1=(n^t0^pt^1)&1,val=dp[t0^1];
            for(int s0=0;s0<=1;s0++) for(int s1=0;s1<=1;s1++){
                int x0=(int)cc[0].size()-s0*(t0^1)-s1*t1;
                int x1=(int)cc[1].size()-s0*t0-s1*(t1^1);
                if(x0<0 || x1<0 || x0!=x1 || s0+s1>sz) continue;
                //cout << s0 << ' ' << s1 << ' ' << t0 << ' ' << t1 << '\n';
                vector<int> cur,p(2,0);
                if(s0) cur.push_back(cc[t0][p[t0]++]);
                while(p[0]<(int)cc[0].size() && p[1]<(int)cc[1].size()){
                    cur.push_back(cc[t0^s0][p[t0^s0]++]);
                    cur.push_back(cc[t0^s0^1][p[t0^s0^1]++]);
                }
                int pos=(int)cur.size()-1,total=val;
                for(int x:cur) total+=f0.query(x);
                if(s1){
                    cur.push_back(cc[t1^1][p[t1^1]++]);
                    total+=n-t-f0.query(cur.back());
                }
                //for(int x:cur) cout << x << ' ';
                //cout << '\n';
                for(int i=(int)cur.size()-1;i>=0;i--){
                    total+=f1.query(cur[i]);
                    f1.update(cur[i],1);
                }
                for(int x:cur) f1.update(x,-1);
                ndp[t0^1^s0]=min(ndp[t0^1^s0],total);
                //cout << total << '\n';
                while(pos>=1){
                    int d0=f0.query(cur[pos]),d1=f0.query(cur[pos-1]);
                    total+=2*(n-t-d0-d1);
                    if((t0^s0)!=(t1^s1)) total+=(cur[pos]>cur[pos-1]?1:-1);
                    ndp[t0^1^s0]=min(ndp[t0^1^s0],total);pos-=2;
                    //cout << pos << ' ' << total << '\n';
                }
            }
        }
        swap(dp,ndp);
        //cout << dp[0] << ' ' << dp[1] << '\n';
    }
    int res=min(dp[0],dp[1]);
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}