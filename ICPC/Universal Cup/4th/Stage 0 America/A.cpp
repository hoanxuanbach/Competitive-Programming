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

const int N = 1e4;

void solve(){
    auto get = [&](int x){
        vector<int> d(N);
        for(int i=2;i<=x;i++){
            while(x%i==0) x/=i,d[i]++;
        }
        return d;
    };
    int A,B;cin >> A >> B;
    vector<int> a=get(A),b=get(B);
    vector<int> fa(N),fb(N);

    int fA=1,fB=1;
    for(int i=N-1;i>1;i--){
        if(!a[i] && !b[i]) continue;
        if(a[i]){
            fa[i]=a[i]/2+1;a[i]&=1;
            if(!a[i]) fb[i]=1;
            else{
                int x=i-1;
                for(int j=2;j<=x;j++){
                    while(x%j==0){
                        if(a[j]) a[j]--;
                        else b[j]++;
                        x/=j;
                    }
                }
            }
        }
        if(b[i]){
            fb[i]=b[i]/2+1;b[i]&=1;
            if(!b[i]) fa[i]=1;
            else{
                int x=i-1;
                for(int j=2;j<=x;j++){
                    while(x%j==0){
                        if(b[j]) b[j]--;
                        else a[j]++;
                        x/=j; 
                    }
                }
            }
        }
        while(fa[i]) fa[i]--,fA*=i;
        while(fb[i]) fb[i]--,fB*=i;
    }
    cout << fA << ' ' << fB << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
