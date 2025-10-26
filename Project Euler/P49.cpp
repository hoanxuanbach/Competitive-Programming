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
    int N=10000;
    vector<int> p(N,1);
    p[0]=p[1]=0;
    for(int i=2;i<N;i++) if(p[i]){
        for(int j=i*2;j<N;j+=i) p[j]=0;
    }

    for(int i=1000;i<N;i++){
        if(!p[i]) continue;
        string S=to_string(i);
        sort(S.begin(),S.end());
        vector<int> P;
        do{
            int x=stoi(S);
            if(x>i && p[x]) P.push_back(x);
        }while(next_permutation(S.begin(),S.end()));
        sort(P.begin(),P.end());
        for(int x:P) for(int y:P) if(x<y && x-i==y-x){
            cout << i << x << y << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
