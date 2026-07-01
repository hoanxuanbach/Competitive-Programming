#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int maxn = 2e5+5;
const int inf = 1e18;

int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

#define ld long double
ld pw(ld a,int n){
    ld res=1;
    while(n){
        if(n&1) res*=a;
        a=a*a;n>>=1;
    }
    return res;
}


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int M = 5e6;

void solve(){
    int N;cin >> N;
    vector<int> d(N),f(M);
    vector<vector<int>> S(N);
    for(int i=2;i<M;i++) if(!f[i]) for(int j=i;j<M;j+=i) f[j]=i;
    for(int i=1;i<N;i++) for(int j=i;j<N;j+=i) d[j]++,S[j].push_back(i);

    /*
    vector<int> h(N);
    vector<bool> has(M);
    for(int x=1;x<M;x++){
        int p=d[x]+1;
        if(p<N && f[p]==p && !h[p]){
            for(int k:S[x]) has[k%p]=true;
            bool check=true;
            for(int i=1;i<p;i++) if(!has[i]) check=false;
            for(int k:S[x]) has[k%p]=false;
            if(check) h[p]=x;
        }
    }
    */

    function<pair<ld,int>(ld)> Parts = [&](ld val) {
        std::stringstream ss;
        // Use maximum possible precision for long double
        ss << std::scientific << std::setprecision(std::numeric_limits<long double>::max_digits10) <<  val; 
        std::string s = ss.str();

        size_t ePos = s.find('e');
        if (ePos != std::string::npos) {
            std::string sig = s.substr(0, ePos);
            std::string exp = s.substr(ePos + 1);
            return make_pair(stold(sig),stoll(exp));
        } else return make_pair(val,0LL);
    };


    vector<ld> dp(N);

    ld A=1;
    int B=0;
    for(int p=2;p<N;p++) if(f[p]==p){
        int k=p-1;
        vector<int> T;
        for(int i=2;i*i<=k;i++){
            if(k%i==0){
                T.push_back(i);
                while(k%i==0) k/=i;
            }
        }
        if(k>1) T.push_back(k);
        k=p-1;
        int r=2;
        auto is_root = [&](int x){
            for(int d:T) if(power(x,k/d,p)==1) return false;
            return true;
        };
        while(!is_root(r)) r++;
        vector<int> g(k);g[0]=1;
        for(int i=1;i<k;i++) g[i]=g[i-1]*r%p;
        for(int i=1;i<k;i++){
            while(g[i]<M && f[g[i]]!=g[i]) g[i]+=p;
            assert(g[i]<M);
        }

        
        auto get = [&](int x,int d){
            int mn=inf;
            for(int t=1;t<k/x;t++) if(__gcd(t,d)==1) mn=min(mn,g[t*x]);
            return mn;
        };

        dp[1]=1;
        for(int x:S[k]){
            if(x==1) continue;
            dp[x]=pw(r,x-1);
            for(int y:S[x]) if(y<x) dp[x]=min(dp[x],dp[y]*pw(get(y,x/y),(x/y-1)));
        }
        
        auto [fA,fB]=Parts(dp[k]);
        A*=fA;
        B+=fB;
        cout << p << ' ' << dp[k] << ' ' << fA << ' ' << fB << endl;
    }
    auto [res,e]=Parts(A);
    cout << res << 'e' << B+e << '\n';
}
 
/*
2^6 * 17 * 173
r = 1
r = 21
r = 14
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
