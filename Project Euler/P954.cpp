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

    vector<int> p(n);p[0]=1;
    for(int i=1;i<n;i++) p[i]=p[i-1]*10;

    int res=0;
    for(int f=1;f<=6;f++){
        int start=0;
        function<int(int,int)> dfs = [&](int i,int x){
            if(i<0) return (int)(x%7==f);
            int cnt=0;
            for(int k=0;k<7;k++){
                int cc=p[i],dd=x/p[i+1];
                int mul=(1+(k<3));
                while(dd){
                    int b=dd%10;dd/=10;cc*=10;
                    int t=(b-k+14)*(cc-p[i])%7;
                    if(t==f){
                        if(dd || k) mul=0;
                        else if(!k && mul) mul=1;
                    }
                }
                if(mul) cnt+=dfs(i-1,x+k*p[i])*mul;
            }
            return cnt;
        };
        for(int i=0;i<n;i++) for(int k=1;k<=7;k++){
            cout << f << ' ' << i << ' ' << k << endl;
            res+=dfs(i-1,k*p[i])*(1+(k<3));
        }
    }

    cout << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
