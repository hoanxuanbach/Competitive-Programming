#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1003443221;
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
    freopen("1001.txt","r",stdin);
    string ss;cin >> ss;
    vector<int> A;

    A.push_back(0);
    int X=0;
    for(char c:ss){
        if(c==',') A.push_back(X+1),X=0;
        else X=X*10+c-'0';
    }
    A.push_back(X+1);
    A.push_back(0);

    int n = (int)A.size()/2;
    vector<int> pos(n,-1),f(2*n,0),dp(n);

    for(int y=0;y<2*n;y++){
        if(pos[A[y]]==-1) pos[A[y]]=y;
        else{
            int k=A[y],x=pos[k];
            
            f[x]=1;
            for(int i=x+1;i<y;i++){
                f[i]=f[i-1];
                if(pos[A[i]]!=i && pos[A[i]]>x) f[i]=(f[i]+f[pos[A[i]]-1]*dp[A[i]])%mod;
            }
            dp[k]=f[y-1];
        }
    }
    cout << dp[0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
