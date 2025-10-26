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
    int N=50000000;
    vector<int> p(N,1);p[0]=p[1]=0;

    vector<int> P;
    for(int i=2;i<N;i++){
        if(p[i]){
            P.push_back(i*i);
            for(int j=i*2;j<N;j+=i) p[j]=0;
        }
    }
    int cnt=0,sum=0;
    for(int x:P){
        string s=to_string(x),t=s;
        reverse(t.begin(),t.end());
        if(s==t) continue;
        int y=stoll(t);
        int pos=lower_bound(P.begin(),P.end(),y)-P.begin();
        if(pos<(int)P.size() && P[pos]==y){
            cout << x << '\n';
            cnt++;sum+=x;
        }
        if(cnt==50) break;
    }
    cout << cnt << ' ' << sum << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
