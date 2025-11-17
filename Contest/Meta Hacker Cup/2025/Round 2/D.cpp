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

int ans[105];
vector<array<int,3>> qq[105];

int tmp[(1<<24)+5],dp[(1<<24)+5];

void build(int K){
    if(qq[K].empty()) return;
    int T=(1<<(K-1));
    for(int i=0;i<T;i++) dp[i]=0;

    vector<int> pw(K+1,1);
    for(int i=1;i<=K;i++) pw[i]=pw[i-1]*10%mod;

    vector<vector<pii>> query(K);
    for(auto [x,mask,id]:qq[K]) query[x].push_back({mask,id});

    auto rot = [&](int mask,int x){
        //cout << "rot " << mask << ' ' << x << endl;
        assert(mask>>x&1);
        int d=mask&((1<<x)-1);mask>>=x;
        mask|=(d<<(K-x));mask>>=1;
        return mask;
    };
    cerr << "build " << K << endl;
    for(int i=1;i<K;i++){
        cerr << '*' << K << ' ' << i << endl;
        for(int xx=0;xx<T;xx++) tmp[xx]=0;
        for(int xx=0;xx<T;xx++){
            int cx=xx<<1|1;
            for(int d=0;d<=9;d++){
                int nx=d%K;
                if(!(cx>>nx&1)){ 
                    int mx=cx|(1<<nx);
                    //cout << '?' << mx << ' ' << nx << endl;
                    mx=rot(mx,nx);
                    tmp[xx]=(tmp[xx]+dp[mx])%mod;
                }
                else tmp[xx]=(tmp[xx]+pw[i-1])%mod;
            }
        }   
        for(int xx=0;xx<T;xx++) dp[xx]=tmp[xx];
        for(auto [xx,id]:query[i]){
            int val=dp[xx];
            if(id>0) ans[id]=(ans[id]+val)%mod;
            else ans[-id]=(ans[-id]+mod-val)%mod;
        }
    }
}

int cal(string S,int K,int id){
    int res=0;
    if((int)S.size()>=K){
        int T=0;
        for(char c:S) T=(T*10+c-'0')%mod;
        res=(res+T+1)%mod;
        
        T=1;
        for(int i=1;i<K;i++) T=T*10%mod;
        res=(res+mod-T)%mod;

        S.clear();
        for(int i=1;i<K;i++) S+='9';
    }

    int T=(1<<(K-1)),N=(int)S.length();
    assert(N<K);

    vector<int> pw(N+1,1);
    for(int i=1;i<=N;i++) pw[i]=pw[i-1]*10%mod;

    vector<int> f(N+1);f[N]=1;
    for(int i=N-1;i>=0;i--){
        f[i]=f[i+1];
        int x=S[i]-'0';
        f[i]=(f[i]+x*pw[N-i-1])%mod;
    }
    auto rot = [&](int mask,int x){
        //cout << "rot " << mask << ' ' << x << endl;
        assert(mask>>x&1);
        int d=mask&((1<<x)-1);mask>>=x;
        mask|=(d<<(K-x));mask>>=1;
        return mask;
    };

    int mask=1,x=0;
    //cout << S << ' ' << K << endl;
    for(int i=1;i<N;i++){
        for(int d=1;d<=9;d++){
            int nx=d%K;
            if(nx){
                int mx=(1<<nx)|1;
                //cout << '*' << i << ' ' << mx << ' ' << nx << endl;
                qq[K].push_back({i-1,rot(mx,nx),id});
                
            }
            else res=(res+pw[i-1])%mod;
        }
    }
    for(int i=0;i<N;i++){
        int k=S[i]-'0';
        for(int d=(i==0);d<k;d++){
            int nx=(x+d)%K;
            if(mask>>nx&1) res=(res+pw[N-i-1])%mod;
            else{
                int nmask=(mask|(1<<nx));
                //cout << '#' << (N-i-1) << ' ' << nmask << ' ' << nx << endl;
                qq[K].push_back({N-i-1,rot(nmask,nx),id});
            }
        }
        
        x=(x+k)%K;
        if(mask>>x&1){
            res=(res+f[i+1])%mod;
            break;
        }
        else mask|=(1<<x);
    }
    return res;
}

void solve(int t){
    cerr << t << endl;
    string L,R;cin >> L >> R;
    int K;cin >> K;

    ans[t]=(cal(R,K,t)-cal(L,K,-t)+mod)%mod;

    int mask=1,x=0;
    for(char c:L){
        x=(x+c-'0')%K;
        if(mask>>x&1){
            ans[t]=(ans[t]+1)%mod;
            break;
        }
        else mask|=(1<<x);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++) solve(t);
    for(int k=2;k<=25;k++) build(k);
    for(int t=1;t<=test;t++) cout << "Case #" << t << ": " << ans[t] << '\n';
}
