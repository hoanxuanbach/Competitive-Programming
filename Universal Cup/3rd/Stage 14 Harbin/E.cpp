#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,m;cin >> n >> m;
    vector<int> x(n),v(m);
    for(int i=0;i<n;i++) cin >> x[i],x[i]=-x[i];
    for(int i=0;i<m;i++) cin >> v[i];

    vector<int> f(m+1),d(m);

    f[0]=1;
    vector<pii> ord;
    for(int i=0;i<m;i++){
        d[i]=n,f[0]=f[0]*n%mod;
        for(int j=0;j<n;j++) ord.push_back({x[j],i});
    }
    int dd=f[0];
    sort(ord.begin(),ord.end(),[&](pii a,pii b){
        return a.first*v[b.second]<b.first*v[a.second];
    });

    auto del = [&](int b,int a){
        //divide ax+b
        b=power(b,mod-2);
        for(int i=0;i<m;i++){
            f[i]=f[i]*b%mod;
            f[i+1]=(f[i+1]-f[i]*a%mod+mod)%mod;
        }
    };
    auto add = [&](int b,int a){
        //multiply ax+b
        for(int i=m-1;i>=0;i--){
            f[i+1]=(f[i+1]+f[i]*a)%mod;
            f[i]=f[i]*b%mod;
        }
    };

    int res=0;
    for(auto [X,i]:ord){
        del(d[i],n-d[i]);
        int tm=X*power(v[i],mod-2)%mod;
        res=(res+tm*f[m/2])%mod;
        d[i]--;
        add(d[i],n-d[i]);
    }

    res=res*power(dd,mod-2)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}