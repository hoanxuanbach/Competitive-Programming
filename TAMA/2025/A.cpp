#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){   
    int n;cin >> n;
    string S="1";
    bool check=false;
    for(int i=1;i<=n;i++){
        string T;
        int x=1;
        char c=S[0];
        for(int j=0;j<(int)S.length()-4;j++){
            if(S[j]=='1' && S[j+1]=='2' && S[j+2]=='2' && S[j+3]=='2' && S[j+4]=='3') check=true;
        }
        for(int j=1;j<(int)S.length();j++){
            if(S[j]!=c){
                T+=char('0'+x);
                T+=c;
                x=0;c=S[j];
            }
            x++;
        }
        if(x){
            T+=char('0'+x);
            T+=c;
        }
        S=T;
        //cout << S << '\n';
        if(check){
            cout << "NO" << endl;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}