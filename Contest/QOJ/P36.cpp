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
const int inf = 2e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define i128 __int128

const int B=37;
const int T=20;

int a[B+5],p[B+5];
int c[B+5],d[B+5];

void solve(){
    int m,N;cin >> m >> N;

    p[0]=1;
    for(int i=1;i<=m;i++) p[i]=p[i-1]*10;
    vector<vector<i128>> g(B+1,vector<i128>(8*B+1));

    g[0][0]=1;
    for(int i=1;i<=B;i++){
        for(int j=0;j<=8*i;j++) for(int k=0;k<=min(j,8LL);k++) g[i][j]+=g[i-1][j-k];
    }

    auto cal = [&](int s){
        for(int i=0;i<m;i++) c[i]=d[i]=0;

        for(int i=B;i>=s;i--) d[i%m]+=a[i];
        for(int i=0;i<s;i++) c[i%m]++;

        int K=400;
        i128 total=0;
        for(int t=1;t<=T;t++){
            i128 S=(i128)t*(p[m]-1);
            vector<vector<i128>> f(m+1,vector<i128>(K+1,0));
            f[0][0]=1;
            for(int i=0;i<m;i++){
                for(int k=0;k<=K;k++) for(int s=0;s<=8*c[i];s++){
                    if(!f[i][k] || (k+s+d[i])%10!=(S%10)) continue;
                    int nk=(k+s+d[i])/10;
                    f[i+1][nk]+=f[i][k]*g[c[i]][s];
                    //cout << "f " << i+1 << ' ' << nk << ' ' << k << ' ' << c[i] << ' ' << s << ' ' << (int)f[i][k] << ' ' << (int)g[c[i]][s] << '\n';
                }
                S/=10;
            }
            total+=f[m][S];
        }
        return total;
    };

    for(int i=B;i>=0;i--){
        for(int x=0;x<=8;x++){
            a[i]=x;
            i128 cnt=cal(i);
            if(N>cnt) N-=cnt;
            else break;
        }
    }

    __int128 res=0;
    for(int i=B;i>=0;i--) res=res*10+a[i];
    res/=(p[m]-1);

    string ret;
    while(res){
        ret+=char('0'+res%10);
        res/=10;
    }
    reverse(ret.begin(),ret.end());
    cout << ret << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
