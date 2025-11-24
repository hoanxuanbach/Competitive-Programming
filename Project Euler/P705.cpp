#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

int cnt[15][15],d[15];

void solve(){
    int N;cin >> N;

    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        for(int j=i;j<N;j+=i) p[j]=1;
        string A;
        int x=i;
        while(x){
            if(x%10) A+=char('0'+x%10);
            x/=10;
        }
        reverse(A.begin(),A.end());
        for(char c:A){
            int k=c-'0';
            for(int i=1;i<10;i++) cnt[i][k]=(cnt[i][k]+d[i])%mod;
            d[k]++;
        }
    }
    
    vector<int> inv(10);
    for(int i=1;i<10;i++) inv[i]=power(i,mod-2);

    int mul=1;
    vector<int> f(10);
    for(int i=1;i<10;i++){
        for(int x=1;x<=i;x++) f[i]+=(i%x==0);
        mul=mul*power(f[i],d[i])%mod;
    }

    int res=0;
    for(int i=1;i<10;i++) for(int j=1;j<10;j++){
        if(cnt[i][j]){
            int val=inv[f[i]]*inv[f[j]]%mod*cnt[i][j]%mod;
            int k=0;
            for(int x=1;x<=i;x++) for(int y=1;y<=j;y++) if(i%x==0 && j%y==0) k+=(x>y);
            res=(res+val*k)%mod;
        }
    }
    res=res*mul%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
