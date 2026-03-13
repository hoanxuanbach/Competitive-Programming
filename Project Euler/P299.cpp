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
    
    int S=N/2;
    vector<int> f(S);
    for(int i=2;i<S;i++) if(!f[i]) for(int j=i;j<S;j+=i) f[j]=i;
   
    int res=0;
    for(int a=1;a<S;a++){
        if(a%10000==0) cout << a << endl;
        vector<pii> P;
        int x=a;
        while(x>1){
            int j=f[x],k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,2*k});
        }
        /*
        s = a+b+c
        (s-3*a)^2 - 8*a^2 = d^2
        a*(a+S) = T
        */
        function<void(int,int)> dfs = [&](int i,int X){
            if(i==(int)P.size()){

                {
                    int Y=a*a/X;
                    if((X+Y)%2==0){
                        int c=(X+Y)/2,b=Y-c;
                        if((a+b)<N && a<b && (a*b)%(a+b+c)==0) res+=2;
                    }
                }

                if((a*a)%(2*X)==0){
                    
                    int Y=a*a/(2*X);
                    if(X<Y && 2*(a+X+Y)<N){
                        //cout << a << ' ' << X << ' ' << Y << endl;
                        res++;
                    }
                }


                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) X*=P[i].first;
                if(X*X>a*a) break;
                dfs(i+1,X);
            }
        };
        dfs(0,1);
    }

    /*
    a*a = 2*x*y 
    2*(a+x+y) < N
    */

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
