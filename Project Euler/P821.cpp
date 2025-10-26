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
    int n;cin >> n;
    vector<array<int,3>> X;

    int x=1;
    for(int i=0;i<=60;i++){
        int y=x;
        for(int j=0;j<=60;j++){
            X.push_back({y,i,j});
            y*=3;
            if(y>n) break;
        }
        x*=2;
        if(x>n) break;
    }
    sort(X.begin(),X.end());
    
    int A=0,B=0,C=0;
    vector<int> P,num(60);
    auto get = [&](){
        int val=A/3+B/3;
        if(A%3==0 && num[A-2]==1) val--;
        int sum=0;
        for(int i=1;num[i];i+=2) sum+=num[i]/2;
        return min(val,sum);
    };
    for(auto [x,i,j]:X){
        if(j==0) A++;
        if(i==0) B++;
        num[i]++;
        int val=get();
        if(val>C) C=val,P.push_back(x);
    }

    int res=n;
    for(int i=0;i<(int)P.size();i++){
        int r=n/P[i];
        int d=r-r/2-r/3+r/6;
        res-=d;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
