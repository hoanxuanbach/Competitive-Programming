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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=400005;
const int B=256;
const int maxs=260;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int f(int x,int a){
    return (x-(a&(x-1)))&(x-1);
}
int g(int x,int a){
    return (a&(x-1));
}

int a[maxn],c[2][maxn];
struct Block{
    int L,R;
    int total[2],add=0;
    int cnt[B+5],num[2][B+5],pos[B+5],cc[2][B+5],dd[B+5];
    void build(int k=1){
        for(int t=0;t<=1;t++){
            //for(int x=1;x<B;x<<=1) for(int i=L;i<=R;i++) c[t][i]^=num[t][x+f(x,a[i])];
            for(int i=B/4;i>=1;i>>=1) for(int j=0;j<i;j++) num[t][i+j]^=((num[t][i*2+j]^num[t][i*3+j])>>1);
            for(int i=1;i<=B/4;i<<=1) for(int j=0;j<i;j++){
                num[t][i*2+j]^=num[t][i+j];
                num[t][i*3+j]^=num[t][i+j];
            }
        }
        for(int i=L;i<=R;i++){
            for(int t=0;t<=1;t++) c[t][i]^=cc[t][g(B,a[i])]^num[t][B/2+g(B/2,a[i])];
            a[i]+=add;
        }
        add=0;
        memset(num,0,sizeof(num));
        memset(cc,0,sizeof(cc));
        memset(dd,0,sizeof(dd));
        memset(pos,0,sizeof(pos));
        if(k) init();
    }
    void init(){
        memset(cnt,0,sizeof(cnt));
        for(int i=L;i<=R;i++){
            pos[g(B,a[i])]=i;
            dd[g(B,a[i])]^=1;
            cnt[B/2+f(B/2,a[i])]^=B/2;
        }
        for(int i=B/4;i>=1;i>>=1) for(int j=0;j<i;j++) cnt[i+j]^=((cnt[i*2+j]^cnt[i*3+j])>>1);
        for(int i=1;i<=B/4;i<<=1) for(int j=0;j<i;j++){
            cnt[i*2+j]^=cnt[i+j];
            cnt[i*3+j]^=cnt[i+j];
        }
    }
    int query(int t,int l,int r){
        l=max(l,L);r=min(r,R);
        if(l>r) return 0;
        if(l==L && r==R) return total[t];
        else{
            build();
            int res=0;
            for(int i=l;i<=r;i++) res^=c[t][i];
            return res;
        }
    };
    void update(int t,int l,int r){
        l=max(l,L);r=min(r,R);
        if(l>r) return;
        //cout << "update " << L << ' ' << R << ' ' << l << ' ' << r << '\n';
        if(l==L && r==R){
            add++;
            total[t]^=cnt[B/2+g(B/2,add)];
            num[t][B/2+f(B/2,add)]^=(B/2);
            /*
            for(int x=1;x<B;x<<=1){
                num[t][x+g(x,add)]^=x;
            }
            */
            int id=pos[f(B,add)];
            //cout << '*' << id << '\n';
            if(id) cc[t][f(B,add)]^=(((a[id]+add)^(a[id]+add-1))/B)*B;
            if(dd[f(B,add)]) total[t]^=(((a[id]+add)^(a[id]+add-1))/B)*B;
        }
        else{
            build(0);
            for(int i=l;i<=r;i++){
                a[i]++;
                total[t]^=(a[i]^(a[i]-1));
                c[t][i]^=(a[i]^(a[i]-1));
            }
            init();
        }
    }
}S[maxn/B+5];

int n,m,d[maxn],lst[maxn];
int res[maxn];
vector<pii> qq[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> d[i];
    for(int i=1;i<=m;i++){
        int l,r;cin >> l >> r;
        qq[r].push_back({l,i});
    }
    for(int i=0;i<=n/B;i++){
        S[i].L=max(1,i*B);
        S[i].R=min(i*B+B-1,n);
        S[i].init();
    }
    for(int i=1;i<=n;i++){
        for(int j=(lst[d[i]]+1)/B;j<=i/B;j++) S[j].update(i&1,lst[d[i]]+1,i);
        lst[d[i]]=i;
        for(auto [l,id]:qq[i]) for(int j=l/B;j<=i/B;j++) res[id]^=S[j].query(i&1,l,i);
    }
    for(int i=1;i<=m;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
