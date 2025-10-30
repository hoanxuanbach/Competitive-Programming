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

void solve(){
    int N;cin >> N;

    int S=1000;
    vector<int> p(S,1);
    p[0]=p[1]=0;
    for(int i=2;i<S;i++) if(p[i]){
        for(int j=i*i;j<S;j+=i) p[j]=0;
    }

    int T=18;
    vector<vector<int>> d(T+1,vector<int>(S,0));
    for(int i=1;i<S;i++) d[0][i]=p[i];

    for(int i=1;i<=T;i++) for(int j=0;j<S;j++){
        for(int k=0;k<=9;k++) if(j+k<S) d[i][j]+=d[i-1][j+k];
    }

    int x=0,k=-1;
    for(int i=0;i<=T;i++){
        for(int j=1;j<=9;j++){
            if(d[i][j]<N) N-=d[i][j];
            else{
                x=j,k=i;
                break;
            }
        }
        if(x) break;
    }

    int res=x;
    while(k){
        int a=-1;
        for(int i=0;i<=9;i++){
            if(d[k-1][x+i]<N) N-=d[k-1][x+i];
            else{
                a=i;
                break;
            }
        }
        res=res*10+a;
        x+=a;k--;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
