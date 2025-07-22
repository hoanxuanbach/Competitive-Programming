#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2=(mod+1)/2;
const int maxn = 2e3+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

vector<int> f[maxa];
void init(){
    for(int i=2;i<=maxa-5;i++){
        if(f[i].empty()){
            for(int j=i*2;j<=maxa-5;j+=i) f[j].push_back(i);
        }
    }
}

void solve(){
    int n;cin >> n;
    vector<int> a(n),p(n+1),mn(n);
    for(int i=1;i<n;i++) cin >> a[i],p[a[i]]=i;
    for(int i=1;i<n;i++){
        if(!f[a[i]].empty()){
            mn[i]=inf;
            for(int x:f[a[i]]) mn[i]=min(mn[i],p[x]);
        }
    }
    int pos=0,cnt=0,add=0;
    for(int i=1;i<n;i++){
        if(pos<i){
            pos++;
            if(f[a[pos]].empty()) add++;
        }
        if(f[a[i]].empty()){
            add--;
            continue;
        }
        while(pos<mn[i]){
            pos++;
            if(f[a[pos]].empty()){
                cnt+=pos-(i+add);
                add++;
            }
        }
    }
    cout << cnt << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}