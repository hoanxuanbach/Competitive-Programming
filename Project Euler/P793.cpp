#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 50515093;
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
    vector<int> S(N);
    S[0]=290797;
    for(int i=1;i<N;i++) S[i]=S[i-1]*S[i-1]%mod;
    sort(S.begin(),S.end());

    int M=N*(N-1)/2;
    M=(M+1)/2;

    auto check = [&](int X){
        int p=N-1,cnt=0;
        for(int i=0;i<N;i++){
            while(p>=0 && S[p]*S[i]>X) p--;
            cnt+=min(p+1,i);
        }
        return (cnt>=M);
    };

    int l=0,r=mod*mod,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
