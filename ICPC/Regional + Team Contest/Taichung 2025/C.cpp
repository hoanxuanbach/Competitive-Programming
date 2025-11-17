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
    int K,n,L;cin >> K >> n >> L;

    vector<int> R(n);
    for(int i=0;i<n;i++) cin >> R[i];

    int A=0,B=1;
    auto add = [&](int x,int y){
        int g=__gcd(x,y);
        x/=g;y/=g;
        if(x*B>A*y) A=x,B=y;
    };

    auto check = [&](int d){
        queue<int> q;
        vector<int> X;
        for(int i=0;i<n;i++){
            if(q.empty() || q.front()-d<R[i]){
                q.push(R[i]);
                X.push_back(i);
            }
            else{
                q.pop();
                q.push(R[i]);
            }
        }
        int sz=(int)X.size();
        if(sz>L) return false;
        if(sz==1) add(d,1);
        else{
            int T=K;
            for(int i=0;i<sz;i++) X[i]=min(X[i],L-sz+i);
            for(int i=0;i<sz;i++) T-=(1+(i>1))*R[X[i]];
            if(T<=0) return false;

            sz--;
            if(T>=sz*d) add(d,1);
            else{
                add(T,sz);
                if((T+sz-1)/sz<d) return false;
            }
        }
        return true;
    };

    int l=0,r=1e9;
    while(l<=r){
        int d=(l+r)>>1;
        if(check(d)) l=d+1;
        else r=d-1;
    }


    if(A%B==0) cout << A/B << '\n';
    else cout << A << "/" << B << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
