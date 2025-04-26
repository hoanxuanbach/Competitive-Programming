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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

int ans[maxn],Max[maxn];
map<int,vector<pii>> mp;

void solve(){
    int h,w,n;cin >> h >> w >> n;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    auto mul2 = [&](string s){
        int res=0;
        for(int i=0;i<(int)s.length();i++){
            if(s[i]=='.'){
                if(s[i+1]=='5') res++;
                break;
            }
            else res=res*10+(s[i]-'0')*2;
        }
        return res;
    };
    for(int i=1;i<=n;i++){
        string sx,sy;cin >> sx >> sy;
        int x=mul2(sx),y=mul2(sy);
        mp[x-y].push_back({x,i});
    }
    for(auto &it:mp) sort(it.se.begin(),it.se.end());
    set<pii> s;
    s.insert({0,0});
    pq.push({0,0});

    auto check = [&](int x,int y){
        auto it=s.upper_bound({y,inf});it=prev(it);
        return (x<it->se);
    };
    auto update = [&](int l,int r,int x){
        auto it=s.lower_bound({l,0LL});
        int lst=-1;
        while(it!=s.end() && it->fi<r){
            lst=it->se;
            it=s.erase(it);
        }
        if(lst!=-1 && (it==s.end() || it->fi>r)) s.insert({r,lst});
        s.insert({l,x});
    };
    while(!pq.empty()){
        int x,y;tie(x,y)=pq.top();pq.pop();
        //cout << '#' << '\n';
        //cout << x << ' ' << y << ' ' << check(x,y) << '\n';
        //cout << "*" << '\n';
        //for(auto [l,w]:s) cout << l << ' ' << w << '\n';
        if(check(x,y) || x==2*h || y==2*w) continue;
        auto it=lower_bound(mp[x-y].begin(),mp[x-y].end(),mpp(x,0LL));
        if(it==mp[x-y].end()) continue;
        int p=it->fi,id=it->se,d=p-x;
        ans[id]=d;
        pq.push({x+2*d,y});
        pq.push({x,y+2*d});
        update(y,y+2*d,x+2*d);
    }
    for(int i=1;i<=n;i++) cout << ans[i] << '\n';
}
/*
12 12 11
3.5 3.5
2.5 9.5
9.5 2.5
7.5 5.5
7.5 6.5
6.5 8.5
6 11
10 7
8.5 9.5
8 11
10.5 10.5
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}

