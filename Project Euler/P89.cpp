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
    int N=1000;//cin >> N;
    vector<int> val={1000,900,500,400,100,90,50,40,10,9,5,4,1};
    vector<string> S={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int all=0,mn=0;
    for(int i=0;i<N;i++){
        string s;cin >> s;
        
        int T=0;
        for(int j=0;j<(int)s.size();j++){
            for(int k=0;k<(int)S.size();k++){
                if(s[j]!=S[k][0]) continue;
                int d=(int)S[k].length();
                if(d>1 && ((j+1)==(int)s.size() || s[j+1]!=S[k][1])) continue;
                T+=val[k];
                //cout << s[j] << ' ' << j << ' ' << k << '\n';
                j+=d-1;
                break;
            }
        }
        all+=(int)s.size();
        string res;
        for(int j=0;j<(int)S.size();j++){
            while(T>=val[j]){
                T-=val[j];
                res+=S[j];
            }
        }
        mn+=(int)res.length();
        cout << (int)s.size() << ' ' << (int)res.length() << ' ' << res << '\n';
    }
    cout << all-mn << '\n';
}
 
signed main(){
    freopen("89.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
