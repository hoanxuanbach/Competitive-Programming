#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 10000;
const int maxn = 1e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int n,m,a[maxn],kmp[maxn],f[maxn];

const int X=1e5;
void init(){
    f[0]=1;
    for(int i=1;i<=X;i++) f[i]=f[i-1]*n%mod;
}

void solve(){   
    cin >> m;kmp[0]=-1;
    for(int i=1;i<=m;i++){
        cin >> a[i];
        int j=kmp[i-1];
        while(j!=-1 && a[j+1]!=a[i]) j=kmp[j];
        kmp[i]=j+1;
    }
    int res=0;
    while(m){
        res=(res+f[m])%mod;
        m=kmp[m];
    }
    string S=to_string(res);
    while((int)S.length()<4) S="0"+S;
    cout << S << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> n >> test;
    init();
    while(test--) solve();
}