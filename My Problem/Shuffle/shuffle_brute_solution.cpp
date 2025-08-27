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

const int maxn = 5e5+5;

int n,a[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];

    int q;cin >> q;
    while(q--){
        int id,l,r;cin >> id >> l >> r;
        if(id==1){
            int sum=0;
            for(int i=l;i<=r;i++) sum=(sum+a[i])%mod;
            sum=sum*power(r-l+1,mod-2)%mod;
            for(int i=l;i<=r;i++) a[i]=sum;
        }
        else{
            int sum=0;
            for(int i=l;i<=r;i++) sum=(sum+a[i])%mod;
            cout << sum << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}