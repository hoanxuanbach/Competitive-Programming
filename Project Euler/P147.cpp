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

int cal(int n,int m){
    if(n>m) swap(n,m);
    int res=n*(n+1)/2*m*(m+1)/2;
    
    for(int i=1;i<n+m;i++){
        int d=min(n,min(i,n+m-i));
        for(int lt=0;lt<=2*d;lt++) for(int rt=lt+1;rt<=2*d;rt++){
            int j=i+1,l=lt,r=rt;
            while(j<=n && r+j-i<=2*min(n,min(j,n+m-j))) j++;
            if(j>n){
                int x=i;
                if(i<n) x=n,l+=n-i,r+=n-i;
                //cout << '*' << x << ' ' << l << ' ' << r << '\n'; 
                while(j<n+m && (l-j+x)>=0 && (r-j+x)<=2*min(n,min(j,n+m-j))) j++;
            }
            res+=j-i-1;
        }
    }
    //cout << n << ' ' << m << ' ' << res << '\n';
    return res;
}

void solve(){
    int N,M,res=0;cin >> N >> M;
    for(int i=1;i<=N;i++) for(int j=1;j<=M;j++) res+=cal(i,j);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
