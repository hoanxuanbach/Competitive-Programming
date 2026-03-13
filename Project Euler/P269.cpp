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

const int N = 20;
const int M = 205;
const int T = 100;

int A[N][M];
int B[N][M][M];
int C[N][M][M][M];

void solve(){
    int n;cin >> n;

    int res=1;
    for(int i=1;i<n;i++) res*=10;

    for(int x=1;x<10;x++){
        cout << x << endl;
        memset(A,-1,sizeof(A));
        function<int(int,int)> fA = [&](int i,int dx){
            if(i==n) return (int)(dx==0);
            if(A[i][dx+T]!=-1) return A[i][dx+T];

            int cnt=0;
            for(int k=(i==0);k<10;k++) if((k-dx)%x==0) cnt+=fA(i+1,(k-dx)/x);
            return A[i][dx+T]=cnt;
        };
        res+=fA(0,0);
    }
    for(int x=1;x<10;x++) for(int y=x+1;x*y<10;y++){
        cout << x << ' ' << y << endl;
        memset(B,-1,sizeof(B));
        function<int(int,int,int)> fB = [&](int i,int dx,int dy){
            if(i==n) return (int)(dx==0 && dy==0);
            if(B[i][dx+T][dy+T]!=-1) return B[i][dx+T][dy+T];

            int cnt=0;
            for(int k=(i==0);k<10;k++) if((k-dx)%x==0 && (k-dy)%y==0) cnt+=fB(i+1,(k-dx)/x,(k-dy)/y);
            return B[i][dx+T][dy+T]=cnt;
        };
        res-=fB(0,0,0);
    }
    for(int x=1;x<10;x++) for(int y=x+1;x*y<10;y++) for(int z=y+1;x*y*z<10;z++){
        cout << x << ' ' << y << ' ' << z << endl;
        memset(C,-1,sizeof(C));    
        function<int(int,int,int,int)> fC = [&](int i,int dx,int dy,int dz){
            if(i==n) return (int)(dx==0 && dy==0 && dz==0);
            if(C[i][dx+T][dy+T][dz+T]!=-1) return C[i][dx+T][dy+T][dz+T];

            int cnt=0;
            for(int k=(i==0);k<10;k++) if((k-dx)%x==0 && (k-dy)%y==0 && (k-dz)%z==0) cnt+=fC(i+1,(k-dx)/x,(k-dy)/y,(k-dz)/z);
            return C[i][dx+T][dy+T][dz+T]=cnt;
        };
        res+=fC(0,0,0,0);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
