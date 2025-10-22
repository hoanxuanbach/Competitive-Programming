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

const int L=26;

vector<string> N = {
    "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen", "twenty"
};

void solve(){
    string S;cin >> S;
    if((int)S.size()<=2) cout << N[stoi(S)-1] << '\n';
    else{
        for(int i=0;i<20;i++){
            if((int)S.size()!=(int)N[i].size()) continue;
            int k=0;
            for(int j=0;j<(int)S.size();j++) k+=(S[j]!=N[i][j]);
            if(k<=1){
                cout << i+1 << '\n';
                return;
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
