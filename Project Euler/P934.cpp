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

vector<int> P={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
vector<int> Q={53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

void solve(){
    int S=(int)P.size();
    vector<int> T=P;
    for(int i=1;i<S;i++) T[i]*=T[i-1];

    int n,res=0;cin >> n;
    function<void(int,int)> dfs = [&](int i,int d){
        if(i==S){
            if(!d) return;
            cout << '*' << d << '\n';
            int j=0;
            while(j<(int)Q.size()){
                int x=d%Q[j];
                if(x%7!=0) break;
                else j++;
            }
            assert(j<(int)Q.size());
            res+=Q[j];
            return;
        }

        int K=T[i]/P[i];
        for(int j=0;j<P[i];j++){
            if(d>n) break;
            int x=(d%P[i]);
            if((x%7)!=0) res+=((n-d)/T[i]+1)*P[i];
            else dfs(i+1,d);
            d+=K;
        }
    };
    dfs(0,0);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
