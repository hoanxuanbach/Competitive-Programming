#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1005075251;
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
    int N=200,X=1;

    int total=0;
    while(N--){
        cout << N << endl;
        X=X*3%mod;
        string S;cin >> S;

        vector<int> P;

        int cc=0;
        for(char c:S){
            if(c>='0' && c<='9') cc=cc*10+c-'0';
            else{
                P.push_back(cc);
                cc=0;
            }
        }
        if(cc) P.push_back(cc);
        int T=P[0];P.erase(P.begin());

        int sz=(int)P.size(),res=inf;
        vector<vector<int>> f(1<<sz);
        for(int i=1;i<(1<<sz);i++){
            int k=__builtin_popcount(i);
            if(k==1){
                for(int j=0;j<sz;j++) if(i>>j&1) f[i].push_back(P[j]);
            }
            else{
                for(int a=i&(i-1);a;a=(a-1)&i){
                    int b=a^i;
                    for(int x:f[a]) for(int y:f[b]){
                        f[i].push_back(x+y);
                        f[i].push_back(x-y);
                        f[i].push_back(x*y);
                        if(y!=0 && x%y==0) f[i].push_back(x/y);
                    }
                }
                sort(f[i].begin(),f[i].end());
                f[i].erase(unique(f[i].begin(),f[i].end()),f[i].end());
            }

            bool ok=false;
            for(int d:f[i]) if(d==T) ok=true;
            int sum=0;
            for(int j=0;j<sz;j++) if(i>>j&1) sum+=P[j];
            if(ok) res=min(res,sum);
        }
        if(res==inf) res=0;
        total=(total+X*res)%mod;
    }
    cout << total << '\n';
}
 
signed main(){
    freopen("828.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
