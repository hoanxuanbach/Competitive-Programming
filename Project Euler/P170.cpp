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
    int N=1000000;
    vector<vector<int>> d(N);
    for(int i=1;i<N;i++) for(int j=i;j<N;j+=i) d[j].push_back(i);

    string base;
    for(int i=0;i<=9;i++) base+=to_string(i);

    string S=base;
    reverse(S.begin(),S.end());

    auto check = [&](){
        for(int x=1;x<10;x++){
            if(S[x]=='0') continue;
            int a=stoll(S.substr(0,x)),b=stoll(S.substr(x,10-x));
            int g=__gcd(a,b);
            for(int k:d[g]){
                string T=to_string(k)+to_string(a/k)+to_string(b/k);
                sort(T.begin(),T.end());
                if(T==base) return true;
            }
        }
        return false;
    };

    do{
        if(check()) break;
    }while(prev_permutation(S.begin(),S.end()));

    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
