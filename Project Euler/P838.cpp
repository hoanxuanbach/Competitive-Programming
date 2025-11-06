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
    vector<int> p(N+1);

    long double res=0,val=0;
    vector<int> X,Y;
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
            if(i%10==3) res+=log(i);
            else if(i%10==7) X.push_back(i),val+=log(i);
            else if(i%10==9) Y.push_back(i);
        }
    }

    int pos=(int)X.size()-1,k=0;
    while(X[k+1]*X[k+2]*X[k+3]<=N) k++;
    long double cur=val;

    for(int i=0;i<(int)Y.size();i++){
        while(pos>=k && X[pos]*Y[i]>N) cur-=log(X[pos]),pos--;
        val=min(val,cur);
        cur+=log(Y[i]);
    }

    res+=val;
    cout << setprecision(6) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
