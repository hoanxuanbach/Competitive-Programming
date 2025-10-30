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
    vector<int> p(N),X;
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i*i;j<N;j+=i) p[j]=1;
    }

    int res=0;
    function<void(vector<int>)> dfs = [&](vector<int> x){
        if(x.empty()) return;
        vector<int> a,b;

        int ca=0,cb=0;
        for(int i:x){
            if(i&1){
                ca++;
                if(i>1) a.push_back(i/2);
            }
            else{
                cb++;
                b.push_back(i/2);
            }   
        }
        res+=max(ca,cb);
        dfs(a);dfs(b);
    };
    dfs(X);
    cout << res << '\n';
    cout << setprecision(8) << fixed << (long double)res/(int)X.size() << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
