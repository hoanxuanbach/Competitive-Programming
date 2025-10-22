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
    int n,q;cin >> n >> q;

    int X=0;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i],X|=a[i];
    
    vector<int> b(n);
    function<int(int)> cal = [&](int x){
        if(x<0) return 0LL;
        bool check=false;
        for(int i=0;i<n;i++){
            if(b[i]>>x&1){
                check=true;
                b[i]^=(1LL<<x);
            }
        }
        if(check) return cal(x-1);
        else{
            int id=0;
            for(int i=1;i<n;i++) if(b[i]>b[id]) id=i;
            int val=(1LL<<x)-b[id];b[id]=0;
            return val+cal(x-1);
        }
    };

    int base=__builtin_popcountll(X);
    vector<int> d={0};
    for(int i=0;i<=31;i++){
        if(X>>i&1) continue;
        for(int j=0;j<n;j++) b[j]=a[j]&((1LL<<(i+1))-1);
        d.push_back(cal(i));
    }

    for(int i=0;i<q;i++){
        int k;cin >> k;
        for(int j=(int)d.size()-1;j>=0;j--){
            if(d[j]<=k){
                cout << base+j << '\n';
                break;
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
