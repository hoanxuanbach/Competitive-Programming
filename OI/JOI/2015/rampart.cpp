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
const int maxn=4005;

int N,M,L,P;
int c[maxn][maxn],a[maxn][maxn],b[maxn][maxn];

int bit[maxn];
void update(int x,int val){
    for(int i=x;i<=N;i+=(i&(-i))) bit[i]+=val;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}

vector<int> pos[maxn];

void solve(){
    cin >> N >> M >> L >> P;
    for(int i=0;i<P;i++){
        int x,y;cin >> x >> y;
        c[x][y]=1;
    }
    for(int i=1;i<=N;i++) for(int j=1;j<=M;j++) a[i][j]=b[i][j]=min(N,M);
    for(int i=1;i<=N;i++){
        int x=0;
        for(int j=1;j<=M;j++){
            if(c[i][j]) x=0;
            else x++;
            b[i][j]=min(b[i][j],x);
        }
        x=0;
        for(int j=M;j>=1;j--){
            if(c[i][j]) x=0;
            else x++;
            a[i][j]=min(a[i][j],x);
        }
    }
    for(int j=1;j<=M;j++){
        int x=0;
        for(int i=1;i<=N;i++){
            if(c[i][j]) x=0;
            else x++;
            b[i][j]=min(b[i][j],x);
        }
        x=0;
        for(int i=N;i>=1;i--){
            if(c[i][j]) x=0;
            else x++;
            a[i][j]=min(a[i][j],x);
        }
    }
    long long ans=0;
    for(int i=1-M;i<=N-1;i++){
        for(int j=1;j<=N+1;j++) bit[j]=0,pos[j].clear();
        //cout << '*' << i << '\n';
        for(int x=max(1,i+1);x<=N && x-i<=M;x++){
            int y=x-i,da=a[x][y],db=b[x][y];
            //cout << x << ' ' << y << ' ' << da << ' ' << db << '\n';
            for(int p:pos[x]) update(p,-1);
            if(L<=db) ans+=query(x-L+1)-query(x-db);
            if(L<=da){
                update(x,1);
                pos[x+da].push_back(x);
            }
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
