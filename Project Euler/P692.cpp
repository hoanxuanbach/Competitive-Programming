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

map<int,int> mp;
int f(int N){
    if(N<=1) return N;
    if(mp.find(N)!=mp.end()) return mp[N];
    int x=1,res=0;
    while(x+(x-1)/2<N){
        res+=x+f((x-1)/2);
        x+=(x-1)/2+1;
    }
    res+=x+f(N-x);
    return mp[N]=res;
}

void solve(){
    int N;cin >> N;

    vector<int> P;
    P.push_back(1);
    P.push_back(1);
    P.push_back(2);
    int A=1,B=2;
    while(A+B<=N){
        swap(A,B);B+=A;
        P.push_back(B);
    }

    map<int,int> mp;
    function<int(int)> f = [&](int n){
        if(n<=1) return n;
        if(mp.find(n)!=mp.end()) return mp[n];
        int res=0;
        for(int i=1;i<(int)P.size();i++){
            if(P[i]>n) break;
            res+=P[i];
            if(P[i]+P[i-1]<=N) res+=f(P[i-1]-1);
            else res+=f(N-P[i]);
        }
        return mp[n]=res;
    };
    cout << f(N) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
