#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
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
    int k,n,m;cin >> k >> n >> m;
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int la=0,ra=n-1,lb=0,rb=m-1;

    int res=0;
    while(k){
        int L=a[la]*b[lb],R=a[ra]*b[rb];
        if(L>0 || R>0){
            if(L>R) res+=L,la++,lb++;
            else res+=R,ra--,rb--;
            k--;
        }
        else break;
    }
    if(k){
        if(a[ra]>0 || b[lb]<0) swap(a,b),swap(la,lb),swap(ra,rb);
        while(k--) res+=a[ra--]*b[lb+k];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
