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
    int S=sqrtl(N);
    vector<vector<int>> d(S);
    for(int i=1;i<S;i++) for(int j=i*i;j<S;j+=i) d[j].push_back(i);
    int cnt=0;
    set<int> ss;
    for(int c=1;c<S;c++){
        cout << c << endl;
        for(int x:d[c]){
            int y=c/x;
            if((c+x)*(c+y)<=N) ss.insert((c+x)*(c+y));
        }
    }
    cout << (int)ss.size() << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
