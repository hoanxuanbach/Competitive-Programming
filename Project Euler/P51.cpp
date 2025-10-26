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
    int X=10,res=0;
    vector<int> pw={1};
    while(!res){
        pw.push_back(pw.back()*10);
        vector<int> p(X*10);
        for(int i=X;i<X*10;i++){
            int d=i;
            for(int j=2;j*j<=d;j++){
                if(d%j==0){
                    p[i]=true;
                    break;
                }
            }
        }
        for(int i=X;i<X*10;i++){
            if(p[i] || res) continue;
            string s=to_string(i);
            reverse(s.begin(),s.end());
            vector<vector<int>> pos(3);
            for(int j=0;j<(int)s.length();j++) if(s[j]<='2') pos[s[j]-'0'].push_back(j);
            for(int k=0;k<=2;k++){
                int sz=(int)pos[k].size();
                if(sz<3) continue;
                for(int mask=1;mask<(1<<sz);mask++){
                    if(__builtin_popcount(mask)%3!=0) continue;
                    int add=0;
                    for(int j=0;j<sz;j++) if(mask>>j&1) add+=pw[pos[k][j]];
                    int cnt=1;
                    for(int j=1;j<=9-k;j++) cnt+=!(p[i+add*j]);
                    if(cnt>=8){
                        res=i;
                        //cout << mask << ' ' << k << ' ' << add << '\n';
                    }
                }
            }
        }
        X*=10;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
