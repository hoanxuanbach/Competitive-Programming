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
    int N,M;cin >> N >> M;
    vector<int> C(N);
    vector<vector<int>> Q(N);
    for(int i=0;i<N;i++){
        cin >> C[i];
        Q[i].assign(C[i],0);
        for(int j=0;j<C[i];j++) cin >> Q[i][j];
    }   
    vector<int> F(M);
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            int x;cin >> x;
            F[i]|=(x<<j);
        }
    }
    map<int,int> mp;
    int K=0,T=5,S=(1<<T)-1;
    for(int i=0;i<N;i++) K+=(C[i]<<(i*T));

    vector<bool> ck(1<<N,false);
    vector<int> f(1<<N,-1),g(1<<N),add(1<<N),val(1<<N,-1);
    for(int i=1;i<(1<<N);i++){
        for(int j=0;j<N;j++){
            if(i>>j&1){
                f[i]=j;
                val[i]=-val[i^(1<<j)];
                break;
            }
        }
    }

    function<int(int)> dfs = [&](int mask){
        if(mask==K) return 1LL;
        auto it=mp.find(mask);
        if(it!=mp.end()) return it->second;

        vector<pii> P;
        for(int i=0;i<N;i++){
            int j=(mask>>(i*T))&S;
            if(j<C[i]) P.push_back({i,Q[i][j]}); 
        }
        int n=(int)P.size(),res=0;
        vector<pii> A;
        for(int i=1;i<(1<<n);i++){
            int j=f[i];
            ck[i]=ck[i^(1<<j)];
            g[i]=g[i^(1<<j)];
            if(g[i]>>P[j].second&1) ck[i]=true;
            g[i]|=F[P[j].second];
            add[i]=add[i^(1<<j)]+(1LL<<(P[j].first*T));
            if(ck[i]) continue;
            A.push_back({val[i],mask+add[i]});
        }
        for(auto &[d,msk]:A) res+=d*dfs(msk);
        return mp[mask]=res;
    };
    cout << dfs(0) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
