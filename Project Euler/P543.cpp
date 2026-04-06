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

const int N = 8e8;
bitset<N+5> P;

void solve(){
    for(int i=2;i<=N;i++) if(!P[i]) for(int j=i*2;j<=N;j+=i) P[j]=1;
    auto f = [&](int N){
        int cnt=0;
        for(int i=2;i<=N;i++) if(!P[i]) cnt++;
        return cnt;
    };
    auto cal = [&](int N){
        int total=(N/2)*(N/2+1);
        if(N%2==0) total-=N/2;
        if(N>=2) total-=N-1-f(N);
        if(N>=4) total-=N-1-f(N-2)-N/2;
        return total;
    };
    //int N;cin >> N;
    int M=44;
    int A=1,B=1,res=0;
    for(int i=3;i<=M;i++){
        cout << i << endl;
        swap(A,B);B+=A;
        res+=cal(B);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
