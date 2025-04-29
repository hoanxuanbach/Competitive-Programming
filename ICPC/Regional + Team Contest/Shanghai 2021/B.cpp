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
const int maxn=200005;
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
const int root=3;
const int iroot=power(3,mod-2);
int fac[maxn],dfac[maxn],inv[maxn];
int C(int k,int n){
    if(k>n) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void NTT(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wlen=power((invert ? iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=(int)(1LL*a[i+j+len/2]*w%mod);
                a[i+j]=(u+v>=mod?u+v-mod:u+v);
                a[i+j+len/2]=(u-v<0?u-v+mod:u-v);
                w=(int)(1LL*w*wlen%mod);
            }
        }
    }
    if(invert){
        int in=power(n,mod-2);
        for(int &x:a) x=(int)(1LL*x*in%mod);
    }
}
void mul(vector<int> &a,vector<int> &b){
    int n=1,len=(int)a.size()+b.size();
    while(len>n) n<<=1;
    a.resize(n);b.resize(n);
    NTT(a,false);NTT(b,false);
    for(int i=0;i<n;i++) a[i]=a[i]*b[i]%mod;
    NTT(a,true);a.resize(len);

}
int p[maxn],cnt[maxn],n,cc=0;
vector<int> a[maxn];
bool vis[maxn];
void solve(){
    cin >> n;
    fac[0]=fac[1]=dfac[0]=dfac[1]=inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=mod-(mod/i)*inv[mod%i]%mod;
        fac[i]=fac[i-1]*i%mod;
        dfac[i]=dfac[i-1]*inv[i]%mod;
    }
    for(int i=1;i<=n;i++) cin >> p[i];
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int d=i;cc++;
            do{
                vis[d]=true;
                cnt[cc]++;d=p[d];
            }while(d!=i);
            a[cc].resize(cnt[cc]);
            for(int j=0;j<cnt[cc];j++) a[cc][j]=C(j,cnt[cc]);
            pq.push({cnt[cc],cc});
        }
    }
    while((int)pq.size()>=2){
        pii x=pq.top();pq.pop();
        pii y=pq.top();pq.pop();
        if(x.second>y.second) swap(x,y);
        mul(a[x.second],a[y.second]);
        cnt[x.second]+=cnt[y.second];
        pq.push({cnt[x.second],x.second});
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(i%2==0) ans=(ans+a[1][i]*fac[n-i])%mod;
        else ans=(ans-a[1][i]*fac[n-i]%mod+mod)%mod;
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
