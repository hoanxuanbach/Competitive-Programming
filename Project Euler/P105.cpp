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
    int N=100,T=0;
    while(N--){
        cout << N << endl;
        string S;cin >> S;
        vector<int> x;

        int X=0;
        for(char c:S){
            if(c==','){
                x.push_back(X);
                X=0;
            }
            else X=X*10+c-'0';
        }
        if(X) x.push_back(X);

        int n=(int)x.size();
        vector<int> f(1<<n),s(1<<n);
        for(int i=0;i<(1<<n);i++) for(int j=0;j<n;j++){
            if(i>>j&1) f[i]+=x[j],s[i]++;
        }
        bool check=true;
        for(int i=1;i<(1<<n);i++){
            int mask=((1<<n)-1)^i;
            for(int j=mask;j;j=(j-1)&mask){
                if(f[i]==f[j]) check=false;
                if(s[i]>s[j] && f[i]<f[j]) check=false;
            }
        }
        if(check) T+=f[(1<<n)-1];
    }
    cout << T << '\n';
}
 
signed main(){
    freopen("105.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
