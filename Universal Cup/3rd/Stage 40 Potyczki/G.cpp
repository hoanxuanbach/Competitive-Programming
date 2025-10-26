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

const int N = 1e6+5;
void solve(){
    int A,B,n;cin >> A >> B >> n;
    vector<array<int,3>> X;

    int S=0,T=0;
    for(int i=0;i<n;i++){
        int a,b;cin >> a >> b;S+=a;
        if(b>B/2) X.push_back({b,0,a}),T+=a;
        else X.push_back({B-b,1,a});
    }
    if(S>2*A || T>A){
        cout << "NIE\n";
        return;
    }
    if(S<=A){
        cout << "TAK\n";
        return;
    }
    T=A-T;S=0;
    sort(X.begin(),X.end());

    bitset<N> C;C[0]=1;
    auto lim = [&](int L,int R){
        if(L>R) C.reset();
        else{
            C=(C>>L)<<L;
            C=(C<<(N-R-1))>>(N-R-1);
        }
    }; 
    for(auto [_,t,x]:X){
        if(!t){
            T+=x;
            lim(max(0LL,S-T),T);
        }
        S+=x;C|=(C<<x);
        lim(max(0LL,S-T),T);
    }
    if(C.any()) cout << "TAK\n";
    else cout << "NIE\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
