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
    
    int S=sqrt(N)+1;
    vector<int> f(S);
    for(int i=2;i<S;i++) if(!f[i]) for(int j=i;j<S;j+=i) f[j]=i;

    vector<pii> P;
    for(int i=1;i<S;i++){
        int x=i,k=1;
        while(x>1){
            int j=f[x];
            k*=-1;x/=j;
            if(x%j==0){
                k=0;
                break;
            }
        }
        if(k) P.push_back({i,k});
    }

    map<int,int> mp;
    auto cal = [&](int m){
        if(mp.find(m)!=mp.end()) return mp[m];
        int cnt=0;
        for(auto [x,k]:P){
            if(x*x>m) break;
            int s=m/(x*x);
            cnt+=k*x*x*s*(s+1)/2;
        }
        //cout << m << ' ' << cnt << '\n';
        return mp[m]=cnt;
    };

    int res=0;
    for(int c=1;c<S;c++){
        if(c%10000==0) cout << c << endl;
        vector<pii> P;
        int x=c;
        while(x>1){
            int j=f[x],k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,2*k});
        }
        function<void(int,int)> dfs = [&](int i,int X){
            if(i==(int)P.size()){
                int Y=c*c/X;
                int a=c+X,b=c+Y;
                if(b*b>N) return;
                //cout << a << ' ' << b << ' ' << c << '\n';
                res+=(a*a+b*b+c*c)*cal(N/(b*b));
                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) X*=P[i].first;
                if(X>c) break;
                dfs(i+1,X);
            }
        };
        dfs(0,1);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
