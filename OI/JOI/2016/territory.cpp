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
const int maxn=100005;
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

int dx[]={0,0,1,1},
    dy[]={0,1,0,1};

map<pii,int> mp;
map<pii,vector<piii>> g;
int n,K;
string s;

void solve(){
    cin >> n >> K >> s;
    int x=0,y=0;
    for(int t=0;t<4;t++){
        int xt=x+dx[t],yt=y+dy[t];
        mp[{xt,yt}]|=(1<<t);
    }
    for(char c:s){
        if(c=='E') y++;
        else if(c=='W') y--;
        else if(c=='N') x++;
        else x--;
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            mp[{xt,yt}]|=(1<<t);
        }
    }
    bool sx=false,sy=false;
    if(x<0) sx=true,x=-x;
    if(y<0) sy=true,y=-y;
    if(!x && !y) K=1;
    int total=0;
    for(auto [p,mask]:mp){
        auto [xt,yt]=p;
        if(sx) xt=-xt;
        if(sy) yt=-yt;
        int cx=xt,cy=yt;
        if(mask==15) total++;
        if(x!=0){
            int rx=(cx%x+x)%x;
            int d=(cx-rx)/x;
            int ry=cy-d*y;
            swap(rx,cx);
            swap(ry,cy);
        }
        else if(y!=0){
            int ry=(cy%y+y)%y;
            int d=(cy-ry)/y;
            int rx=cx-d*x;
            swap(rx,cx);
            swap(ry,cy);
        }
        g[mpp(cx,cy)].push_back({{xt,yt},mask});
        g[mpp(cx,cy)].push_back({{xt+x*K,yt+y*K},-mask});
    }
    if(K==1){
        cout << total << '\n';
        return;
    }
    int ans=0;
    for(auto [s,pos]:g){
        sort(pos.begin(),pos.end());
        //cout << "*******" << s.fi << ' ' << s.se << '\n';
        int px=-inf,py=-inf,add=0;
        vector<int> cur(4,0);
        for(auto [p,mask]:pos){
            auto [cx,cy]=p;
            //cout << cx << ' ' << cy << ' ' << mask << '\n';
            if(px!=-inf && *min_element(cur.begin(),cur.end())){
                if(x) add+=(cx-px)/x;
                else add+=(cy-py)/y;
            }
            for(int i=0;i<4;i++) if(abs(mask)>>i&1) cur[i]+=(mask<0?-1:1);
            px=cx;py=cy;
        }
        ans+=add;
        //cout << add << '\n';
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
