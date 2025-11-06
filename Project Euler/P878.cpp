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
    int N,K;cin >> N >> K;
    int L=1,X=1;
    while((1LL<<X)<=N) X++;
    while((1LL<<L)<=K) L++;

    int d=10;

    vector<pii> P;
    P.push_back({0,0});
    for(int i=0;i<X;i++){
        cout << i << ' ' << (int)P.size() << endl;
        vector<pii> nP;
        auto add = [&](int a,int b){
            if(b>N) return;
            __int128 T=0;
            for(int j=0;j<=i;j++) if(b>>j&1){
                T^=(__int128(a))<<(j+1);
                T^=(__int128(1))<<(2*j);
            }
            for(int j=0;j<=i;j++) if(a>>j&1) T^=(__int128(1))<<(2*j);

            int c=T%(1LL<<(i+1));
            if(c>=(1LL<<L)) return;
            nP.push_back({a,b});
        };
        for(auto [a,b]:P){
            add(a,b);
            add(a,b|(1LL<<i));
            if(a!=b) add(b,a|(1LL<<i));
            add(a|(1LL<<i),b|(1LL<<i));
        }
        swap(P,nP);
    }
    int res=0;
    for(auto [a,b]:P){
        __int128 T=0;
        for(int j=0;j<X;j++) if(b>>j&1){
            T^=(__int128(a))<<(j+1);
            T^=(__int128(1))<<(2*j);
        }
        for(int j=0;j<X;j++) if(a>>j&1) T^=(__int128(1))<<(2*j);
        if(T<=K) res++;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
