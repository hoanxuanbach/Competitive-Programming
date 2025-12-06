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

vector<char> C = {'N','W','S','E'};

void solve(){
    int n;cin >> n;

    map<char,int> mp;
    for(int i=0;i<4;i++) mp[C[i]]=i;

    char start,cur;
    vector<pair<char,int>> op;
    for(int i=0;i<n;i++){
        int d;char c;cin >> c >> d;
        if(!i) start=c,cur=c;
        else{
            int k=(mp[cur]-mp[c]+4)%4;
            if(k==1) op.push_back({'R',-1});
            else op.push_back({'L',-1});
            cur=c;
        }
        op.push_back({'Z',d});
    }
    cout << (int)op.size() << ' ' << start << '\n';
    for(auto [c,x]:op){
        if(x!=-1) cout << c << ' ' << x << '\n';
        else cout << c << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
