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
    string S;getline(cin,S);
    vector<string> ss;

    string cur;
    for(char c:S){
        if(c>='A' && c<='Z') cur+=c;
        else{
            if(!cur.empty()) ss.push_back(cur);
            cur.clear();
        }
    }
    int total=0;
    sort(ss.begin(),ss.end());
    for(int i=0;i<(int)ss.size();i++){
        int sum=0;
        for(char c:ss[i]) sum+=c-'A'+1;
        total+=sum*(i+1);
    }
    cout << total << '\n';
}
 
signed main(){
    freopen("22.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
