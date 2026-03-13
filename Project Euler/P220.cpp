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

/*
x,y L -> -y,x 
    R -> y,-x    
*/

int dx[] = {0,1,0,-1},
    dy[] = {1,0,-1,0};



void solve(){
    int S,n;cin >> S >> n;
    vector<vector<array<int,4>>> A(n+1,vector<array<int,4>>(4,{0,0,0,0}));
    vector<vector<array<int,4>>> B(n+1,vector<array<int,4>>(4,{0,0,0,0}));
    for(int i=0;i<=3;i++) A[0][i][3]=B[0][i][3]=i;
    for(int i=1;i<=n;i++) for(int j=0;j<=3;j++){
        auto [x,y,k,d]=A[i-1][j];
        d=(d+1)%4;
        x+=B[i-1][d][0];
        y+=B[i-1][d][1];
        k+=B[i-1][d][2];
        d=B[i-1][d][3];
        x+=dx[d];y+=dy[d];k++;
        d=(d+1)%4;
        A[i][j]={x,y,k,d};
        //cout << "A " << i << ' ' << j << ' ' << x << ' ' << y << ' ' << k << ' ' << d << '\n';

        x=0;y=0;k=0;d=j;
        d=(d+3)%4;
        x+=dx[d];y+=dy[d];k++;
        x+=A[i-1][d][0];
        y+=A[i-1][d][1];
        k+=A[i-1][d][2];
        d=A[i-1][d][3];
        d=(d+3)%4;
        x+=B[i-1][d][0];
        y+=B[i-1][d][1];
        k+=B[i-1][d][2];
        d=B[i-1][d][3];

        B[i][j]={x,y,k,d};
        //cout << "B " << i << ' ' << j << ' ' << x << ' ' << y << ' ' << k << ' ' << d << '\n';
    }

    int x=0,y=1,d=0;

    int i=n,t=0;
    while((i--)>0){
        //cout << i << ' ' << t << ' ' << x << ' ' << y << ' ' << d << '\n';
        if(!t){
            if(A[i][d][2]<S){
                S-=A[i][d][2];
                x+=A[i][d][0];
                y+=A[i][d][1];
                d=A[i][d][3];
                d=(d+1)%4;
                if(B[i][d][2]<S){
                    S-=B[i][d][2];
                    x+=B[i][d][0];
                    y+=B[i][d][1];
                    d=B[i][d][3];
                    cout << x << ' ' << y << '\n';
                    return;
                }
                else t=1;
            }
        }
        else{
            if(S==1){
                cout << x << ' ' << y << '\n';
                return;
            }
            d=(d+3)%4;
            x+=dx[d];y+=dy[d];
            S--;
            if(A[i][d][2]<S){
                S-=A[i][d][2];
                x+=A[i][d][0];
                y+=A[i][d][1];
                d=A[i][d][3];
                d=(d+3)%4;
            }
            else t=0;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
