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
#define ld long double

void solve(){
    int k,t;cin >> k >> t;t%=k;
    string s;cin >> s;
    
    int n=(1<<k),d=1;
    for(int i=0;i<t;i++) d=(d*(n/2))%(n-1);

    //cout << '*' << d << '\n';

    vector<int> f(n);
    for(int i=0;i<n;i++) f[i]=s[i]-'a';
    for(int x=0;x<k;x++){
        int dd=((1<<x)*d)%(n-1);
        
        vector<int> ord(n);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int x,int y){
            int nx=(x+dd)%n,ny=(y+dd)%n;
            return make_pair(f[x],f[nx])<make_pair(f[y],f[ny]);
        });

        int T=0;
        vector<int> g(n);
        g[ord[0]]=0;
        
        for(int i=1;i<n;i++){
            int x=ord[i],y=ord[i-1];
            int nx=(x+dd)%n,ny=(y+dd)%n;
            if(f[x]>f[y] || (f[x]==f[y] && f[nx]>f[ny])) T++;
            g[x]=T; 
        }
        swap(f,g);
    }
    int x=0;
    for(int i=1;i<n;i++) if(f[i]<f[x]) x=i;
    string res;
    for(int i=0;i+1<n;i++) res+=s[(x+(i*d)%(n-1))%n];
    res+=s[(x+n-1)%n];

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
