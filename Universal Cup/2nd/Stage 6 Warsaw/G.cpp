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
const int mod=1e9+7;
const int maxn=2005;
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

int n,row[maxn],col[maxn];
int A[maxn][maxn],B[maxn][maxn];

int w[maxn],C[maxn],D[maxn];

int f[25][25],res[25],x[25];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin >> A[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin >> B[i][j];
    {//row
        for(int i=1;i<=n;i++) w[i]=rng()%mod;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) C[j]=(C[j]+w[i]*A[i][j])%mod;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) D[j]=(D[j]+C[i]*B[i][j])%mod;
        for(int i=1;i<=n;i++) if(D[i]!=w[i]) col[i]=1;
    }
    {//col
        for(int i=1;i<=n;i++){
            w[i]=rng()%mod;
            C[i]=D[i]=0;
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) C[i]=(C[i]+w[j]*A[i][j])%mod;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) D[i]=(D[i]+C[j]*B[i][j])%mod;
        for(int i=1;i<=n;i++) if(D[i]!=w[i]) row[i]=1;
    }
    int num=0;
    vector<int> pos;
    for(int i=1;i<=n;i++) if(row[i]){
        row[i]=++num;
        pos.push_back(i);
    }
    vector<piii> ans;
    for(int i=1;i<=n;i++){
        if(!col[i]) continue;
        memset(res,0,sizeof(res));
        memset(f,0,sizeof(f));
        for(int j=1;j<=n;j++){
            int val=(i==j);
            for(int k=1;k<=n;k++){
                if(row[k]) x[row[k]-1]=A[j][k];
                else val=(val-A[j][k]*B[k][i]%mod+mod)%mod;
            }
            x[num]=val;
            for(int j=0;j<num;j++) if(x[j]){
                if(!f[j][j]){
                    int inv=power(x[j],mod-2);
                    for(int k=0;k<=num;k++) f[j][k]=x[k]*inv%mod;
                    break;
                }
                int d=x[j];
                for(int k=j;k<=num;k++) x[k]=(x[k]+(mod-d)*f[j][k])%mod;
            }
        }

        for(int j=num-1;j>=0;j--){
            res[j]=f[j][num];
            for(int k=j+1;k<num;k++) res[j]=(res[j]-f[j][k]*res[k]%mod+mod)%mod;
            if(!f[j][j]) res[j]=B[pos[j]][i];
            else res[j]=res[j]*power(f[j][j],mod-2)%mod;
            if(B[pos[j]][i]!=res[j]) ans.push_back({{pos[j],i},res[j]});
        }
    }
    sort(ans.begin(),ans.end());
    cout << (int)ans.size() << '\n';
    for(auto x:ans) cout << x.fi.fi << ' ' << x.fi.se << ' ' << x.se << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
