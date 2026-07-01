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
    int N,res=0;cin >> N;
    vector<int> f(N);
    for(int i=2;i<N;i++) if(!f[i]) for(int j=i;j<N;j+=i) f[j]=i;

    for(int w=1;w<N;w++){
        if(w%10000==0) cout << w << endl;
        vector<pii> P;
        
        int x=w;
        while(x>1){
            int j=f[x],k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,2*k});
        }

        vector<int> S;
        function<void(int,int)> dfs = [&](int i,int d){
            if(i==(int)P.size()){
                int s=w*w/d;
                if((s+d)&1) return;
                int k=(s+d)/2;
                if(k<N) S.push_back((s-d)/2);
                return;
            }
            for(int k=0;k<=P[i].second;k++){
                if(k) d*=P[i].first;
                if(d>=w) break;
                dfs(i+1,d);
            }
        };
        dfs(0,1);
        int sz=(int)S.size();
        for(int i=0;i<sz;i++) for(int j=i+1;j<sz;j++) if((S[i]*S[j])%(S[i]+S[j])==0) res++;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
