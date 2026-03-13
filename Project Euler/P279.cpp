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
    
    int S=N/2+1;
    vector<int> f(S);
    for(int i=2;i<S;i++) if(!f[i]) for(int j=i;j<S;j+=i) f[j]=i;

    /*
    int cnt=0;
    for(int a=1;a<=N;a++) for(int b=a;a+b<=N;b++) for(int c=b;a+b+c<=N;c++){
        bool ok=false;
        if(a*a+b*b==c*c) ok=true;
        if(c*c-a*c+a*a==b*b) ok=true;
        if(c*c-b*c+b*b==a*a) ok=true;
        if(a*a+b*b+a*b==c*c) ok=true;
        if(ok){
            cnt++;
        }
    }
    cout << cnt << '\n';
    */
   
    int res=N/3;
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
                    if(X<=Y && (X+Y)%2==0){
                        int c=(X+Y)/2,b=Y-c;
                        if(a<b && a+b+c<=N) res++;
                    }
                }

                {
                    int Y=3*a*a/X;
                    if(X<=Y && (X+Y)%4==0){
                        int c=(X+Y)/4;
                        int b1=Y-2*c+a;
                        int b2=Y-2*c-a;
                        if(b1%2==0){
                            b1/=2;
                            if(a<b1 && a+b1+c<=N) res++;
                        }
                        if(b2%2==0){
                            b2/=2;
                            if(a<b2 && a+b2+c<=N) res++;
                        }
                    }
                }

                if(a*a%(3*X)!=0){
                    X*=3;
                    int Y=3*a*a/X;
                    if(X<=Y && (X+Y)%4==0){
                        int c=(X+Y)/4;
                        int b1=Y-2*c+a;
                        int b2=Y-2*c-a;
                        if(b1%2==0){
                            b1/=2;
                            if(a<b1 && a+b1+c<=N) res++;
                        }
                        if(b2%2==0){
                            b2/=2;
                            if(a<b2 && a+b2+c<=N) res++;
                        }
                    }
                    X/=3;
                }

                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) X*=P[i].first;
                if(X*X>3*a*a) break;
                dfs(i+1,X);
            }
        };
        dfs(0,1);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
