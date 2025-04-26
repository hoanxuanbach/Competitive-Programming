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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=105;
const int maxm=200005;
const int maxq=500005;
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
const int base=1e12;
const int base_digits=12;
struct bignum{
    vector<int> num;
    bignum(){}
    void trim(){
        while(!num.empty() && num.back()==0) num.pop_back();
    }
    friend ostream& operator <<(ostream& out, const bignum&a) {
		out << (a.num.empty() ? 0 : a.num.back());
		for (int i = (int)a.num.size() - 2; i >= 0; --i) out << setw(base_digits) << setfill('0') << a.num[i];
		return out;
	}
    bignum operator+(const bignum&a){
        bignum res=*this;
        int sza=(int)a.num.size(),maxsz=max((int)num.size(),sza)+1,carry=0;
        res.num.resize(maxsz);
        for(int i=0;i<maxsz;i++){
           res.num[i]+=(i<sza?a.num[i]:0)+carry;
           carry=(res.num[i]>=base);
           if(carry) res.num[i]-=base;
        }
        res.trim();
        return res;
    }
    bignum operator*(const int&a){
        bignum res=*this;
        int maxsz=(int)num.size()+3,carry=0;
        res.num.resize(maxsz);
        for(int i=0;i<maxsz;i++){
           res.num[i]=res.num[i]*a+carry;
           carry=res.num[i]/base;res.num[i]%=base;
        }
        res.trim();
        return res;
    }
    int operator%(const int &a){
        int cur=0;
        bignum res=*this;
        for(int i=(int)res.num.size()-1;i>=0;i--) cur=(cur*base+res.num[i])%a;
        return cur;
    }
    bignum operator/(const int &a){
        int carry=0;
        bignum res=*this;
        for(int i=(int)res.num.size()-1;i>=0;i--){
            int d=(res.num[i]+carry*base)/a,r=(res.num[i]+carry*base)%a;
            res.num[i]=d;carry=r;
        }
        res.trim();
        return res;
    }

};
int gcd(bignum x,int a){
    int d=x%a;
    return __gcd(d,a);
}
vector<int> nxt[maxn];
bignum res[maxn];
void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        int k;cin >> k;
        for(int j=1;j<=k;j++){
            int d;cin >> d;
            nxt[i].push_back(d);
        }
    }
    res[1].num.push_back(1);
    for(int i=1;i<=n;i++){
        if(nxt[i].size()){
            int g=gcd(res[i],(int)nxt[i].size());
            for(int j=1;j<=n;j++) res[j]=res[j]*((int)nxt[i].size()/g);
            for(int v:nxt[i]) res[v]=res[v]+res[i]/(int)nxt[i].size();
        }
    }
    cout << res[1] << '\n';
}
signed main(){
    //freopen("WAL.INP","r",stdin);
    //freopen("WAL.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
