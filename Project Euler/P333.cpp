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
 
const int maxn = 1e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int total[maxn];
short f[maxn][20][13];

void solve(){
    int N;cin >> N;

    int A=0,B=0;
    while((1<<A)<N) A++;
    while(power(3,B)<N) B++;
    vector<int> p(B);p[0]=1;
    for(int i=1;i<B;i++) p[i]=p[i-1]*3;

    f[0][0][B-1]=1;
    total[0]=1;

    int res=0;
    vector<int> g(N);
    for(int i=0;i<N;i++){
        if(i>=2 && !g[i]) for(int j=i*2;j<N;j+=i) g[j]=1;
        for(int x=0;x<=A-1;x++) for(int y=B-1;y>=0;y--){
            if(x) f[i][x][y]+=f[i][x-1][y];
            if(y+1<B) f[i][x][y]+=f[i][x][y+1];
            if(x && y+1<B) f[i][x][y]-=f[i][x-1][y+1];
        }
        for(int x=0;x<A;x++) for(int y=0;y<B;y++){
            int ni=i+(1<<x)*p[y];
            if(ni>=N) continue;
            if(x+1<A && y) f[ni][x+1][y-1]=min(f[ni][x+1][y-1]+f[i][x][y],2);
            else total[ni]=(total[ni]+f[i][x][y]);
        }
        if(i>=2 && !g[i]){
            int cnt=total[i]+f[i][A-1][0];
            if(cnt==1){
                cout << i << endl;
                res+=i;
            }
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
