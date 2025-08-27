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

int n,a[maxn];
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        int sum=0,res=inf;
        for(int j=l;j<=min(r,l+200);j++){
            int x=j-l+1;sum+=a[j];
            res=min(res,sum/((x+1)/2));
        }
        cout << res << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}