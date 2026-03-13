#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod1 = 998244353;
const int base1 = 97;
const int mod2 = 1e9+7;
const int base2 = 101;
const int maxn = 1e6+5;
const int inf = 1e18;

int p1[maxn],p2[maxn];
struct hashing{
    int n;
    string S;
    vector<int> h1,h2;
    hashing(int _n,string _S):n(_n),S(_S){
        h1.assign(n+1,0);
        h2.assign(n+1,0);
        for(int i=1;i<=n;i++){
            h1[i]=(h1[i-1]*base1+S[i]-'a')%mod1;
            h2[i]=(h2[i-1]*base2+S[i]-'a')%mod2;
        }
    }
    int get_hash(int l,int r){
        int t1=(h1[r]-h1[l-1]*p1[r-l+1]%mod1+mod1)%mod1;
        int t2=(h2[r]-h2[l-1]*p2[r-l+1]%mod2+mod2)%mod2;
        return t1*mod2+t2;
    };
};

void solve(){
    int n,m,k;cin >> n >> m >> k;
    string A,B;cin >> A >> B;
    A="#"+A;B="#"+B;
    
    int S=max(n,m);p1[0]=p2[0]=1;
    for(int i=1;i<=S;i++) p1[i]=p1[i-1]*base1%mod1,p2[i]=p2[i-1]*base2%mod2;

    hashing fA(n,A),fB(m,B);
    auto lcp = [&](int x,int y){
        int l=0,r=min(n-x,m-y);
        while(l<r){
            int d=(l+r+1)>>1;
            if(fA.get_hash(x+1,x+d)==fB.get_hash(y+1,y+d)) l=d;
            else r=d-1;
        }
        return l;
    };

    vector<vector<pii>> g(k+1,vector<pii>(2*k+1,{-inf,-1}));
    g[0][k]={lcp(0,0),-1};
    for(int i=0;i<k;i++) for(int d=-k;d<=k;d++){
        if(g[i][d+k].first==-inf) continue;
        int x=g[i][d+k].first,y=x+d;
        if(x<n && d>-k){
            g[i+1][d+k-1]=max(g[i+1][d+k-1],pii{x+1+lcp(x+1,y),d}); 
        }
        if(y<m && d<k){
            g[i+1][d+1+k]=max(g[i+1][d+1+k],pii{x+lcp(x,y+1),d});
        }
        if(x<n && y<m){
            g[i+1][d+k]=max(g[i+1][d+k],pii{x+1+lcp(x+1,y+1),d});
        }
    }
    int res=0;
    if(m-n<-k || m-n>k){
        cout << "NO\n";
        return;
    }
    while(res<=k && g[res][m-n+k].first!=n) res++;
    if(res>k){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << res << '\n';
    
    int d=m-n;
    for(int i=res;i>=1;i--){
        int fd=g[i][d+k].second;
        int x=g[i-1][fd+k].first;
        int y=x+fd;
        if(fd==d) cout << "REPLACE " << x+1 << ' ' << B[y+1] << '\n';
        else if(fd<d) cout << "INSERT " << x+1 << ' ' << B[y+1] << '\n';
        else cout << "DELETE " << x+1 << '\n';
        d=fd;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
