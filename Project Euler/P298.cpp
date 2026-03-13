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

#define ld double
ld dp[55][105][450];

void solve(){
    int T=1,K;cin >> K;
    map<vector<int>,int> mp;mp[{0}]=0;
    vector<vector<int>> S={{0}};
    vector<vector<pii>> adj(T);

    auto add = [&](vector<int> s){
        if(mp.find(s)!=mp.end()) return mp[s];
        mp[s]=T++;
        adj.emplace_back();
        S.push_back(s);
    
        for(int x:s) cout << x << ' ';
        cout << endl;

        return T-1;
    };

    int dd=0;
    auto fL = [&](vector<int> L,int d){
        int sz=(int)L.size();
        for(int i=0;i<sz;i++){
            if(L[i]==d){
                dd++;
                L.erase(L.begin()+i);
                L.insert(L.begin(),d);
                return L;
            }
        }
        if(sz==5) L.pop_back();
        L.insert(L.begin(),d);
        return L;
    };
    auto fR = [&](vector<int> R,int d){
        int sz=(int)R.size();
        for(int i=0;i<sz;i++){
            if(R[i]==d){
                dd--;
                return R;
            }
        }
        if(sz==5) R.pop_back();
        R.insert(R.begin(),d);
        return R;
    };

    function<void(int)> dfs = [&](int x){
        vector<int> s=S[x];
        int n=(int)s.size();

        for(int d=0;d<=9;d++){
            
            dd=0;
            vector<int> L(n);
            for(int i=0;i<n;i++) L[i]=i;
            L=fL(L,d);

            vector<int> R=s;
            R=fR(R,d);

            int m=(int)L.size(),k=m;
            vector<int> g(10,-1);
            for(int i=0;i<m;i++) g[L[i]]=i;
            for(int i=0;i<m;i++){
                if(g[R[i]]!=-1) R[i]=g[R[i]];
                else R[i]=k++;
            }
            
            int id=add(R);
            adj[x].push_back({id,dd});
        }
    };
    int pos=0;
    while(pos<T) dfs(pos++);

    dp[0][K][0]=1;
    for(int i=0;i<K;i++){
        for(int d=K-i;d<=K+i;d++) for(int x=0;x<T;x++){
            for(auto [y,dd]:adj[x]) dp[i+1][d+dd][y]+=dp[i][d][x]/10;
        }
    }

    ld res=0;
    for(int i=0;i<=2*K;i++) for(int x=0;x<T;x++) res+=abs(i-K)*dp[K][i][x];
    cout << setprecision(8) << fixed << res << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
