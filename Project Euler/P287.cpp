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
    int N;cin >> N;

    /*
    for(int x=0;x<(1<<N);x++){
        for(int y=0;y<(1<<N);y++){
            int X=x-(1<<(N-1)),Y=y-(1<<(N-1));  
            if(X*X+Y*Y<=(1LL<<(2*N-2))) cout << 1;
            else cout << 0;
        }
        cout << '\n';
    }
    */
   
    auto f = [&](int a,int b){

        int res=0;
        for(int k=0;k<N;k++){
            /*
            (x*(2^k)-a)^2+(y*(2^k)-b)^2<=2^(2*N-2)
            */
            int cnt=0;
            for(int x=1;x<=(1LL<<(N-k-1));x++){
                int d=(x<<k)-a;
                int S=(1LL<<(2*N-2))-d*d;
                if(S<0) continue;
                S=sqrtl(S);S+=b;S>>=k;
                S=min(S,1LL<<(N-1));
                cnt+=S;
            }

            /*
            (x*(2^k)+a)^2+(y*(2^k)+b)^2>2^(2*N-2)
            */
            int cnt2=0;
            for(int x=0;x<(1LL<<(N-k-1));x++){
                int d=(x<<k)+1-a;
                int S=(1LL<<(2*N-2))-d*d+1;
                S=max(S,0LL);
                int s=sqrtl(S);
                if(s*s<S) s++;
                s=max(0LL,s-(1-b));
                int y=s>>k;
                if((y<<k)<s) y++;
                cnt2+=max(0LL,(1LL<<(N-k-1))-y);
            }

            cnt+=cnt2;
            res+=cnt;
            if(k) res-=4*cnt;
        }
        return res;
    };

    int cnt=2*f(0,1)+f(0,0)+f(1,1);
    cout << cnt*2+(cnt-1)/3 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
