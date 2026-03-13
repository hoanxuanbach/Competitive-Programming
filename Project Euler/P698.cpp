#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 123123123;
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

int f[35][35][35];

void solve(){
    vector<int> S={0,1,2,3,11,12,13,21,22,23,31,32,33};
    int T=33,K;cin >> K;

    vector<int> F(2*T+1);
    for(int x:S) F[x]=1;

    f[0][0][0]=1;
    for(int i=0;i<=T;i++) for(int j=0;j<=T;j++) for(int k=0;k<=T;k++){
        f[i+1][j][k]=min(inf,f[i+1][j][k]+f[i][j][k]);
        f[i][j+1][k]=min(inf,f[i][j+1][k]+f[i][j][k]);
        f[i][j][k+1]=min(inf,f[i][j][k+1]+f[i][j][k]);
    }
    int n=0;
    while(true){
        int total=0;n++;
        for(int x=0;x<=n;x++) for(int y=0;x+y<=n;y++){
            int z=n-x-y;
            if(F[x] && F[y] && F[z]) total=min(inf,total+f[x][y][z]);
        }
        if(total<K) K-=total;
        else break;
    }
    cout << '*' << n << '\n';

    int res=0;
    array<int,3> A={0,0,0};
    while(n--){
        for(int i=0;i<=2;i++){
            int total=0;A[i]++;
            for(int x=0;x<=n;x++) for(int y=0;x+y<=n;y++){
                int z=n-x-y;
                if(F[A[0]+x] && F[A[1]+y] && F[A[2]+z]){
                    int d=f[x][y][z];
                    total=min(inf,total+d);
                }
            }
            //cout << total << '\n';
            if(total<K) K-=total;
            else{
                res=(res*10+i+1)%mod;
                break;
            }
            A[i]--;
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
