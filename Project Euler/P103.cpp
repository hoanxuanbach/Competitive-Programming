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

bool check(vector<int> x){
    int n=(int)x.size();
    vector<int> f(1<<n),s(1<<n);
    for(int i=0;i<(1<<n);i++) for(int j=0;j<n;j++){
        if(i>>j&1) f[i]+=x[j],s[i]++;
    }
    for(int i=1;i<(1<<n);i++){
        int mask=((1<<n)-1)^i;
        for(int j=mask;j;j=(j-1)&mask){
            if(f[i]==f[j]) return false;
            if(s[i]>s[j] && f[i]<f[j]) return false;
        }
    }
    return true;
}

void solve(){

    int res=inf;
    string ss;

    vector<int> S={11,18,19,20,22,25};
    int B=S[2];
    for(int &x:S) x+=B;
    S.insert(S.begin(),B);

    function<void(int)> dfs = [&](int x){
        if(x==7){
            if(check(S)){
                int val=0;
                string cur="";
                for(int x:S) val+=x,cur+=to_string(x);
                if(val<res) res=val,ss=cur;
            }
            return;
        }
        for(int k=-2;k<=2;k++){
            S[x]+=k;
            dfs(x+1);
            S[x]-=k;
        }
    };
    dfs(0);
    cout << res << ' ' << ss << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
