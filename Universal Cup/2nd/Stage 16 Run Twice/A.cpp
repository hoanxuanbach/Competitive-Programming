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

const int maxn=25;
int dp[maxn+5],d[maxn+5][maxn+5];

void build(){
    dp[0]=1;
    //int total=0;
    for(int i=1;i<=maxn;i++){
        for(int j=1;j<=i;j++){
            for(int k=0;k<j;k++) d[i][j]+=dp[i-j]*dp[k]*dp[j-k-1];
            dp[i]+=d[i][j];
        }
        //total+=dp[i];
    }
    //cout << total << '\n';
}

int N,Num;
string s;

void encode(){
    cin >> N >> s;

    function<int(int,int)> dnc = [&](int l,int r){
        if(l>r) return 0LL;
        int n=(r-l+1)/3,p=0,x=0,num=0;
        for(int i=l;i<=r;i++){
            if(s[i]=='|'){
                if(num==1) x=i;
                continue;
            }
            num+=(s[i]=='('?1:-1);
            if(num==0){
                p=i;
                break;
            }
        }
        // l()x()p()
        int cl=(p-l+1)/3,cr=(r-p)/3,total=0;
        for(int i=1;i<cl;i++) total+=d[n][i];

        int lt=(x-l-1)/3,rt=(p-x-1)/3;
        for(int j=0;j<lt;j++) total+=dp[n-cl]*dp[j]*dp[cl-j-1];

        total+=dnc(l+1,x-1)*dp[n-cl]*dp[rt]+dnc(x+1,p-1)*dp[n-cl]+dnc(p+1,r);
        return total;
    };
    int res=dnc(0,3*N-1);
    cout << res << endl;
    /*
    assert(res==Num);
    */
}

string res;

void decode(){
    //N=(int)(rng()%4)+1;
    //Num=(int)(rng()%dp[N]);

    cin >> N >> Num;

    res.clear();
    int num=Num;

    //cout << N << ' ' << num << endl;

    function<void(int,int)> dnc = [&](int n,int mul){
        if(!n) return;
        int p=0;
        for(int i=1;i<=n;i++){
            int total=d[n][i]*mul;
            if(num>=total) num-=total;
            else{
                p=i;
                break;
            }
        }
        int x=0;
        for(int j=0;j<p;j++){
            int total=dp[n-p]*dp[j]*dp[p-j-1]*mul;
            if(num>=total) num-=total;
            else{
                x=j;
                break;
            }
        }
        //cout << n << ' ' << p << ' ' << x << '\n';
        res+='(';
        dnc(x,mul*dp[n-p]*dp[p-x-1]);
        res+='|';
        dnc(p-x-1,mul*dp[n-p]);
        res+=')';
        dnc(n-p,mul);
    };
    dnc(N,1);
    cout << res << endl;
}

void solve(){
    build();
    string S;cin >> S;
    int t;cin >> t;

    for(int i=1;i<=t;i++){
        if(S=="encode") encode();
        else decode();

        /*
        decode();
        s=res;
        encode();
        */
    }

}

/*
encode
1
3 6
(|(|(|)))
*/

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}