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
    int N=1000;

    int cnt=0;

    vector<bool> C(10);
    vector<int> P={17,13,11,7,5,3,2};

    vector<int> pw={1};
    for(int i=1;i<=10;i++) pw.push_back(pw.back()*10);
    function<void(int,int,int)> dfs = [&](int i,int x,int val){
        if(i==(int)P.size()){
            for(int k=0;k<=9;k++) if(!C[k]) val+=k*pw[i+2];
            cout << val << '\n';
            cnt+=val;
            return;
        }
        for(int k=0;k<=9;k++){
            if(C[k]) continue;
            int d=k*100+x;
            if(d%P[i]==0){
                C[k]=true;
                dfs(i+1,d/10,val+k*pw[i+2]);
                C[k]=false;
            }
        }
    };
    for(int i=17;i<N;i+=17){
        C.assign(10,false);
        int d=i;
        bool check=true;
        while(d){
            if(C[d%10]) check=false;
            else C[d%10]=true;
            d/=10;
        }
        if(!check) continue;
        dfs(1,i/10,i);
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
