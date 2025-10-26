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

vector<int> pw;
bool dfs(int x,int d){
    if(!d && x) return false;
    if(!x){
        if(d) return false;
        return true;
    }
    for(int i=1;i<=6;i++){
        int k=x%pw[i];
        if(k>d) break;
        if(dfs(x/pw[i],d-k)) return true;
        if(pw[i]>d) break;
    }
    return false;
}

void solve(){
    int N=1000000,S=N*N;
    pw.push_back(1);
    for(int i=1;i<=6;i++) pw.push_back(pw.back()*10);
    for(int i=2;i<N;i++){
        cout << i << endl;
        if(dfs(i*i,i)) S+=i*i;
    }
    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
