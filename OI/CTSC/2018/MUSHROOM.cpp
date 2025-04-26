// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int mod=998244353;
const int maxn=50005;
int n,f[maxn];
void solve(){
    vector<pii> x;
    int ans=1;
    for(int i=1;i<=n;i++){
        int l,cnt=0;cin >> l;
        while(!x.empty() && x.back().fi>=i-l+1){cnt++;x.pop_back();}
        if(!x.empty() && x.back().se>=i-l+1) ans=0;
        x.push_back({i-l+1,i});
        ans=ans*f[cnt]%mod;
    }
    if((int)x.size()!=1) ans=0;
    cout << ans << '\n';
}
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
void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}

vector<int> mul(vector<int> a,vector<int> b){
    int n=(int)a.size()+(int)b.size(),sz=1;
    while(sz<n) sz<<=1;
    a.resize(sz);b.resize(sz);
    fft(a,false);fft(b,false);
    for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%mod;
    fft(a,true);
    return a;
}
void dnc(int l,int r){
    if(l+1==r){f[l]=(f[l]+(l==1?2:f[l-1]*(l-1)%mod))%mod;return;}
    int mid=(l+r+1)>>1;
    dnc(l,mid);
    if(l!=1){
        vector<int> a(mid-l,0),b(r-l,0);
        for(int i=l;i<mid;i++) a[i-l]=f[i]*(i-1)%mod;
        for(int i=2;i<r-l;i++) b[i]=f[i];
        a=mul(a,b);
        for(int i=mid-l;i<min(r-l,(int)a.size());i++) f[i+l]=(f[i+l]+a[i])%mod;
        a.resize(mid-l);
        for(int i=l;i<mid;i++) a[i-l]=f[i];
        for(int i=2;i<r-l;i++) b[i]=f[i]*(i-1)%mod;
        a=mul(a,b);
        for(int i=mid-l;i<(min(r-l,(int)a.size()));i++) f[i+l]=(f[i+l]+a[i])%mod;
    }
    else{
        vector<int> a(mid),b(mid);
        for(int i=2;i<mid;i++) a[i]=f[i]*(i-1)%mod;
        for(int i=2;i<mid;i++) b[i]=f[i];
        a=mul(a,b);
        for(int i=mid;i<min(r,(int)a.size());i++) f[i]=(f[i]+a[i])%mod;
    }
    dnc(mid,r);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test >> n;
    f[0]=1;dnc(1,n);
    while(test--) solve();
}

