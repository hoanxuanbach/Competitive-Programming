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
 
const int maxn = 1e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int f[maxn][3][3][3][3][3];

void solve(){
    int n;cin >> n;
    for(int x=1;x<=9;x++){
        array<int,3> a={1,0,0};
        int d=a[x%3];a[x%3]++;
        f[1][a[0]][a[1]][a[2]][d][x%3]++;
    }
    for(int i=1;i<n;i++) for(int x=0;x<=2;x++) for(int y=0;y<=2;y++) for(int z=0;z<=2;z++) for(int d=0;d<=2;d++) for(int s=0;s<=2;s++){
        int w=f[i][x][y][z][d][s];
        for(int k=0;k<=9;k++){
            array<int,3> a={x,y,z};
            int ns=(s+k)%3,nd=(d+a[ns])%3;
            a[ns]=(a[ns]+1)%3;
            (f[i+1][a[0]][a[1]][a[2]][nd][ns]+=w)%=mod;
        }
    }
    int res=0;
    for(int x=0;x<=2;x++) for(int y=0;y<=2;y++) for(int z=0;z<=2;z++) for(int s=0;s<=2;s++) res=(res+f[n][x][y][z][0][s])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
