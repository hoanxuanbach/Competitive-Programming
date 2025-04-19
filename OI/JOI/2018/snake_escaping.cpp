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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define pii pair<int,int>
const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,q,f1[(1<<20)+5],f2[(1<<20)+5],a[(1<<20)+5];
void solve(){
    cin >> n >> q;
    for(int i=0;i<(1<<n);i++){
        char c;cin >> c;
        f1[i]=f2[i]=a[i]=c-'0';
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<n);j++){
            if(j&(1<<i)) f1[j]+=f1[j^(1<<i)];
            else f2[j]+=f2[j^(1<<i)];
        }
    }
    for(int _=1;_<=q;_++){
        string s;cin >> s;
        int num=0,m0=0,m1=0,m2=0,cnt0=0,cnt1=0,cnt2=0;
        for(int i=0;i<n;i++){
            if(s[i]!='?'){
                num=num*2+(s[i]-'0');
                if(s[i]=='0'){cnt0++;m0+=(1<<(n-i-1));}
                else{cnt1++;;m1+=(1<<(n-i-1));}
            }
            else{num=num*2+1;m2+=(1<<(n-i-1));cnt2++;}
        }
        int res=0;
        if(cnt0<=cnt1 && cnt0<=cnt2){
            num^=m2;
            for(int i=m0;;i=(i-1)&m0){
                if(__builtin_popcount(i)&1) res-=f2[num^i];
                else res+=f2[num^i];
                if(i==0) break;
            }
        }
        else if(cnt1<=cnt0 && cnt1<=cnt2){
            for(int i=m1;;i=(i-1)&m1){
                if(__builtin_popcount(i)&1) res-=f1[num^i];
                else res+=f1[num^i];
                if(i==0) break;
            }
        }
        else{
            for(int i=m2;;i=(i-1)&m2){
                res+=a[num^i];
                if(i==0) break;
            }
        }
        cout << res << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}