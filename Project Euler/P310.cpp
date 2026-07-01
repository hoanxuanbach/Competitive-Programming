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
    int S=sqrtl(N);
    vector<int> g(N+1),cnt;
    for(int x=0;x<=N;x++){
        vector<int> f(S+1);
        for(int i=1;i*i<=x;i++) f[min(g[x-i*i],S)]++;
        while(f[g[x]]) g[x]++;
        while(g[x]>=(int)cnt.size()) cnt.push_back(0);
        cnt[g[x]]++;
    }
    int M=(int)cnt.size(),res=0;
    for(int a=0;a<M;a++) for(int b=a;b<M;b++) for(int c=b;c<M;c++){
        if(a^b^c) continue;
        if(a==c) res=(res+cnt[a]*(cnt[a]+1)*(cnt[a]+2)/6);
        else if(a==b) res=(res+cnt[a]*(cnt[a]+1)/2*cnt[c]);
        else if(b==c) res=(res+cnt[a]*cnt[b]*(cnt[b]+1)/2);
        else res=(res+cnt[a]*cnt[b]*cnt[c]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
