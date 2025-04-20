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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=5005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;

int n,m,d,c[maxn][maxn],pos[maxn][maxn];
int mm[maxn],used[maxn];
vector<int> cc[maxn];

namespace Linked_List{
    int pre[maxn],nxt[maxn],Max;
    void build(){
        int ft=-1,p=-1;Max=0;
        for(int i=0;i<d;i++){
            if(used[i]){
                if(ft==-1) ft=i;
                if(p!=-1) nxt[p]=i,pre[i]=p,Max=max(Max,i-p-1);
                p=i;
            }
        }
        nxt[p]=ft;pre[ft]=p;
        Max=max(Max,ft-p-1+d);
    }
    void del(int x){
        Max=max(Max,(nxt[x]-pre[x]-1+d)%d);
        pre[nxt[x]]=pre[x];nxt[pre[x]]=nxt[x];
    }
};

void solve(){
    cin >> n >> m >> d;
    vector<pii> p;
    int Min=d;
    for(int i=1;i<=n;i++){
        int x,y;cin >> x >> y;mm[y]=1;
        p.push_back({x,y});Min=min(Min,x);
    }
    for(auto [x,y]:p) c[x-Min][y]|=1;
    for(int i=1;i<=m;i++){
        int x,y;cin >> x >> y;
        x=(x-Min+d)%d;c[x][y]|=2;
    }
    vector<int> cur;
    for(int i=0;i<d;i++){
        for(int j=0;j<d;j++) pos[i][j]=((c[i][j]&2)?i:(i?pos[i-1][j]:-1));
        bool check=false;
        for(int j=0;j<d;j++) if(c[i][j]&1) check=true;
        if(check) cur.push_back(i);
    }
    int ans=d*d;
    for(int k=0;k<(int)cur.size();k++){
        int s=cur[k],t=(k+1==(int)cur.size()?d:cur[k+1]);
        for(int i=s;i<t;i++){
            for(int j=0;j<d;j++){
                if(pos[i][j]>s && !mm[j]) cc[pos[i][j]].push_back(j),used[j]=true;
                else if(mm[j]) used[j]=true;
            }
            Linked_List::build();

            ans=min(ans,(d-Linked_List::Max)*(d-i+s));

            for(int j=s+1;j<=i;j++){
                for(int x:cc[j]) Linked_List::del(x);
                ans=min(ans,(d-Linked_List::Max)*(d-i+j));
            }

            for(int j=s;j<=i;j++) cc[j].clear();
            for(int j=0;j<d;j++) used[j]=false;
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
