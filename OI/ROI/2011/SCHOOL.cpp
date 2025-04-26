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
const int inf=1e9;
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

vector<int> d[3];

void solve(){
    int a,b,c,m,n;cin >> a >> b >> c >> n;m=a+b+c;
    for(int j=0;j<3;j++) d[j].clear();
    for(int i=1;i<=n;i++){
        int y,x;cin >> y >> x;
        d[y-1994].push_back(x);
    }
    if(d[0].empty() || d[1].empty() || d[2].empty()){
        cout << -1 << '\n';
        return;
    }
    sort(d[0].begin(),d[0].end(),greater<int>());
    sort(d[1].begin(),d[1].end(),greater<int>());
    sort(d[2].begin(),d[2].end(),greater<int>());
    int p0=0,p2=0,Min=inf,c0=-1,c1=-1,c2=-1;
    for(int i=0;i<(int)d[1].size();i++){
        while(p0<(int)d[0].size() && d[0][p0]>d[1][i]) p0++;
        while(p2<(int)d[2].size() && d[2][p2]>d[1][i]) p2++;
        if(p2==(int)d[2].size() || p0==0) continue;
        int d0=p0-1,d2=(int)d[2].size()-p2-1,dd=m-i-p2-3,cnt=abs(b-i-1);
        if(dd<0 || dd>d0+d2) continue;
        int x0=1,x2=p2+1,k=0;
        if(x0+d0<a && x2+d2<c){
            k=min(dd,d0);
            x0+=k;dd-=k;
            k=min(dd,d2);
            x2+=k;dd-=k;
        }
        else if(x0+d0<a && x2+d2>c){
            k=min(d0,dd);
            x0+=k;dd-=k;
            x2+=dd;
        }
        else if(x0+d0>a && x2+d2<c){
            k=min(d2,dd);
            x2+=k;dd-=k;
            x0+=dd;
        }
        else{
            k=max(0,min({d0,dd,a-x0}));
            x0+=k;dd-=k;d0-=k;
            k=max(0,min({d2,dd,c-x2}));
            x2+=k;dd-=k;d2-=k;
            k=min(d0,dd);
            x0+=k;dd-=k;d0-=k;
            k=min(d2,dd);
            x2+=k;dd-=k;d2-=k;
        }
        cnt+=abs(x0-a)+abs(x2-c);
        if(cnt<Min){
            Min=cnt;
            c0=x0;c1=i+1;c2=x2;
        }
    }
    if(c0==-1){
        cout << -1 << '\n';
        return;
    }
    cout << Min << ' ' << c0 << ' ' << c1 << ' ' << c2 << '\n';
}

signed main(){
    //freopen("SCHOOL.INP","r",stdin);
    //freopen("SCHOOL.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();

}
