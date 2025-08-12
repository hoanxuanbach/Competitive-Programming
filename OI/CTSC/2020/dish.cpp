#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

const int S = 2500000;
bitset<2*S+5> bs[505];

void solve(){   
    auto print = [&](int i,int x,int j,int y){
        if(!x) swap(i,j),swap(x,y);
        if(x) cout << i << ' ' << x << ' ';
        if(y) cout << j << ' ' << y << ' ';
        cout << '\n';
    };

    int n,m,k;cin >> n >> m >> k;
    vector<int> d(n);
    for(int i=0;i<n;i++) cin >> d[i];
    while(m>=n){
        int id=0;
        for(int i=1;i<n;i++) if(d[id]<d[i]) id=i;
        assert(d[id]>=k);d[id]-=k;m--;
        print(id+1,k,0,0);
    }
    auto build = [&](vector<pii> p){
        int t=(int)p.size()-1;
        while(t--){
            sort(p.begin(),p.end(),greater<pii>());
            pii a=p[0],b=p.back();p.pop_back();
            assert(a.fi+b.fi>=k);
            print(b.se,b.fi,a.se,k-b.fi);
            a.fi-=(k-b.fi);p[0]=a;
        }
    };
    if(m==n-1){
        vector<pii> p;
        for(int i=0;i<n;i++) p.push_back({d[i],i+1});
        build(p);
    }
    else{
        bs[0].reset();
        bs[0][S+k]=1;
        for(int i=0;i<n;i++){
            int x=d[i]-k;
            if(x>=0) bs[i+1]=bs[i]|(bs[i]<<x);
            else bs[i+1]=bs[i]|(bs[i]>>(-x));
        }
        if(!bs[n][S]){
            cout << -1 << '\n';
            return;
        }
        vector<pii> A,B;

        int C=S;
        for(int i=n-1;i>=0;i--){
            int x=d[i]-k;
            if((C-x)>=0 && (C-x)<=2*S && bs[i][C-x]) A.push_back({d[i],i+1}),C-=x;
            else B.push_back({d[i],i+1});
        }
        build(A);build(B);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}