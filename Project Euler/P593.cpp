#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 10007;
int power(int a,int n){
    n%=(mod-1);
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

const int MX = 2e8;
bitset<MX> T;

void solve(){
    int N;cin >> N;
    vector<int> S(N+1);
    int M=20*N;

    int pos=1;
    for(int i=2;i<M;i++){
        if(!T[i]){
            S[pos++]=i;
            if(pos>N) break;
            for(int j=i;j<M;j+=i) T[j]=1;
        }
    }
    for(int i=1;i<=N;i++) S[i]=power(S[i],i);
    for(int i=N;i>=1;i--) S[i]+=S[i/10000+1];

    int K;cin >> K;
    set<pii> A,B;
    for(int i=1;i<=K;i++) B.insert({S[i],i});
    while((int)B.size()>K/2) A.insert(*B.begin()),B.erase(B.begin());
    
    int res=0;
    res+=A.rbegin()->first+B.begin()->first;
    for(int i=K+1;i<=N;i++){
        if(A.find({S[i-K],i-K})!=A.end()) A.erase({S[i-K],i-K}),A.insert({S[i],i});
        else B.erase({S[i-K],i-K}),B.insert({S[i],i});
        if(B.begin()->first<A.rbegin()->first){
            auto fA=*A.rbegin();
            auto fB=*B.begin();
            A.erase(fA);
            B.erase(fB);
            A.insert(fB);
            B.insert(fA);
        }
        int val=A.rbegin()->first+B.begin()->first;
        res+=val;
    }
    cout << res/2;
    if(res&1) cout << ".5";
    else cout << ".0";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
