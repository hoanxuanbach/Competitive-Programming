#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
int mod;
const int maxn=500005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int rt,irt;
int p[105],sz;
void findrt(int n){
    int m=n;
    for(int i=2;i*i<=m;i++){
        if(m%i==0){
            p[sz++]=i;
            while(m%i==0) m/=i;
        }
    }
    if(m>1) p[sz++]=m;
    for(int i=2;i<=n;i++){
        bool ok=true;
        for(int j=0;j<sz;j++){
            if(power(i,n/p[j])==1){ok=false;break;}
        }
        if(ok){rt=i;break;}
    }
    irt=power(rt,mod-2);
    sz=0;m=n;
    for(int i=2;i*i<=m;i++){
        while(m%i==0){p[sz++]=i;m/=i;}
    }
    if(m>1) p[sz++]=m;
}
void dft(vector<int> &a,bool inv,int d){
    int n=(int)a.size();
    if(n==1) return;
    vector<int> r(n);r[0]=1;r[1]=power(inv?irt:rt,(mod-1)/n);
    for(int i=2;i<n;i++) r[i]=r[i-1]*r[1]%mod;
    vector<vector<int>> f(p[d],vector<int>(n/p[d],0));
    for(int i=0;i<p[d];i++){
        for(int j=0;j<n/p[d];j++) f[i][j]=a[i+j*p[d]];
        dft(f[i],inv,d+1);
    }
    for(int i=0;i<n;i++){
        a[i]=0;
        for(int j=0;j<p[d];j++) a[i]=(a[i]+r[i*j%n]*f[j][i%(n/p[d])])%mod;
    }
}
void solve(){
    int n,k;cin >> n >> k;mod=n+1;
    vector<int> a(n),b(n);findrt(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];
    dft(a,0,0);dft(b,0,0);
    for(int i=0;i<n;i++) a[i]=a[i]*power(b[i],k)%mod;
    dft(a,1,0);
    int dd=power(n,mod-2);
    for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    for(int i=0;i<n;i++) cout << a[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
