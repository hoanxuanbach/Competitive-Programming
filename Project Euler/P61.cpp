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
    int L=1000,R=10000;
    vector<set<int>> S(6);
    for(int i=1;i<=200;i++){
        S[0].insert(i*(i+1)/2);
        S[1].insert(i*i);
        S[2].insert(i*(3*i-1)/2);
        S[3].insert(i*(2*i-1));
        S[4].insert(i*(5*i-3)/2);
        S[5].insert(i*(3*i-2));
    }
    vector<int> p(5);
    iota(p.begin(),p.end(),1);
    do{
        vector<int> X;
        function<void(int,int,int)> dfs = [&](int a,int b,int i){
            if(i==5){
                if(a!=b) return;
                int total=0;
                for(int a:X) total+=a;
                cout << total << '\n';
                for(int a:X) cout << a << ' ';
                cout << '\n';
                for(int a:p) cout << a << ' ';
                cout << '\n';
                return;
            }
            for(int c=10;c<100;c++) if(S[p[i]].find(b*100+c)!=S[p[i]].end()){
                X.push_back(b*100+c);
                dfs(a,c,i+1);
                X.pop_back();
            }
        };
        for(int x=L;x<R;x++) if(S[0].find(x)!=S[0].end()){
            X.push_back(x);
            dfs(x/100,x%100,0);
            X.pop_back();
        }
    }while(next_permutation(p.begin(),p.end()));
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
