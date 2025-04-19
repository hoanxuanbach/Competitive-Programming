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
const int maxn=5005;
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

int n,m,d[maxn];
int res[maxn][maxn];
bool c[maxn],del[maxn];
vector<int> pos[maxn],pos2[maxn];

int rand_int(int l,int r){
    return (l+(int)rng()%(r-l+1));
}

void solve(){
    cin >> n >> m;
    /*
    n=rand_int(10,10);
    if(n&1) m=rand_int(n*(n-1)/2*(n-1)/2,n*(n-1)*(2*n-1)/6);
    else m=rand_int(n/2*((n/2)*(n/2)+(n/2-1)*(n/2-1)),n*(n-1)*(2*n-1)/6);
    */
    //int pn=n,pm=m;
    m=(n*(n-1)*(n-2)/6-m)*2+n*(n-1)/2;
    if(m>n*(n-1)*(2*n-1)/6){
        cout << "No\n";
        return;
    }
    int M=m;
    m=n*(n-1)*(2*n-1)/6-m;
    //cout << m << '\n';
    if(m%2!=0){
        cout << "No\n";
        return;
    }
    for(int i=0;i<n;i++) d[i]=1;
    int l=0,r=n-1;
    while(m>0 && (r-l)>1){
        int val=min(m/2,r-l-1);
        m-=2*val;
        d[l]--;d[l+val+1]--;
        d[l+1]++;d[l+val]++;
        if(d[l]==0) l++;
        if(d[r]==0) r--;
    }
    if(m>0){
        cout << "No\n";
        return;
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        pos[i].clear();
        pos2[i].clear();
        del[i]=false;
        for(int j=0;j<n;j++) res[i][j]=0;
        for(int j=0;j<d[i];j++){
            //cout << i << ' ';
            pos[i].push_back(cnt++);
        }
    }
    //cout << '\n';
    cnt=0;
    for(int i=n-1;i>=0;i--){
        while(!pos[i].empty()){
            int x=pos[i].back();
            for(int j=0;j<n;j++) c[j]=0;
            pos[i].pop_back();
            int dd=n-1-i-cnt;
            //cout << "***" << x << ' ' << dd << '\n';
            for(int j=i;j>=0;j--){
                while(dd && !pos[j].empty()){
                    int u=pos[j].back();dd--;
                    pos[j].pop_back();
                    res[x][u]=1;c[u]=1;
                    //cout << x << ' ' << u << '\n';
                    pos2[j-1].push_back(u);
                }
            }
            del[x]=true;cnt++;
            for(int j=0;j<n;j++){
                while(!pos2[j].empty()){
                    pos[j].push_back(pos2[j].back());
                    pos2[j].pop_back();
                }
                if(c[j] || del[j]) continue;
                res[j][x]=1;
                //cout << j << ' ' << x << '\n';
            }
        }
    }
    cout << "Yes\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++) cout << (res[i][j]^1);
        int dd=0;
        for(int j=0;j<n;j++) if(i!=j) dd+=(res[i][j]^1);
        M-=dd*dd;
        if(i) cout << '\n';
        //cout << dd << '\n';
    }
    assert(M==0);
    /*
    if(M!=0){
        cout << "sus" << endl;
        cout << pn << ' ' << pm << endl;
        exit(0);
    }
    */
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
