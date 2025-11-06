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

#define uint unsigned int

void solve(){
    int N;cin >> N;
    vector<int> P={2,3,5};
    vector<int> X;

    vector<int> val;
    function<void(int,int)> dfs = [&](int i,int x){
        if(i==3){
            val.push_back(x);
            x+=1;
            bool prime=true;
            for(int d=2;d*d<=x;d++) if(x%d==0){
                prime=false;
                break;
            }
            if(prime && x!=2 && x!=3 && x!=5){
                X.push_back(x);
            }
            return;
        }
        if(x*P[i]<=N) dfs(i,x*P[i]);
        dfs(i+1,x);
    };
    dfs(0,1);
    //cout << (int)X.size() << '\n';
    sort(X.begin(),X.end());
    //for(int x:X) cout << x << ' ';
    //cout << '\n';

    int S=sqrtl(N);
    vector<uint> f(S+1),g(S+1);g[1]=1;
    for(int x:X){
        for(int i=x;i<S;i++) f[i/x]+=f[i]*x;
        for(int i=S;i>=1;i--){
            int d=N/(i*x);
            if(d<S) f[d]+=g[i]*x;
            else g[i*x]+=g[i]*x;
        }
    }
    sort(val.begin(),val.end());
    int sz=(int)val.size();
    vector<uint> sum(sz);
    for(int i=0;i<sz;i++){
        sum[i]=val[i];
        if(i) sum[i]+=sum[i-1];
    }
    auto get = [&](int n){
        int p=upper_bound(val.begin(),val.end(),n)-val.begin()-1;
        return sum[p];
    };
    uint res=0;
    for(int i=1;i<S;i++){
        res+=get(i)*f[i];
        //cout << f[i] << ' ';
    }
    //cout << '\n';
    for(int i=1;i<=S;i++){
        res+=get(N/i)*g[i];
        //cout << g[i] << ' ';
    }
    //cout << '\n';
    cout << (res&((1ULL<<32)-1)) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
