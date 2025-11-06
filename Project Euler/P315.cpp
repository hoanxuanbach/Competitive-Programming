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
    vector<string> S={"1110111","0010010","1011101","1011011","0111010","1101011","1101111","1110010","1111111","1111011"};
    vector<int> X;
    for(int i=0;i<10;i++){
        int val=0;
        for(int j=0;j<7;j++) val|=(S[i][j]-'0')<<j;
        X.push_back(val);
    }

    auto f = [&](int x){
        return __builtin_popcount(x);
    };
    auto g = [&](int x,int y){
        int A=0,B=0;
        while(x && y){
            int dx=x%10;x/=10;
            int dy=y%10;y/=10;
            A+=f(X[dx])+f(X[dy]);
            B+=f(X[dx]^X[dy]);
        }
        if(x<y) swap(x,y);
        while(x){
            int dx=x%10;x/=10;
            A+=f(X[dx]);
            B+=f(X[dx]);
        }
        return A-B;
    };
    
    int N;cin >> N;

    int res=0;
    vector<int> p(2*N);
    for(int i=2;i<2*N;i++) if(!p[i]){
        if(i>N){
            int x=i;
            while(x){
                int d=x,y=0;
                while(d) y+=d%10,d/=10;
                if(x==y) break;
                res+=g(x,y);x=y;
            }
        }
        for(int j=i*i;j<2*N;j+=i) p[j]=1;
    }
    //cout << C << endl;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
