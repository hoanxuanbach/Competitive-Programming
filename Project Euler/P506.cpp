#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 123454321;
const int phi = 41*40*271*270;
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
    int N;cin >> N;
    
    int M=15;
    vector<int> T={1,2,3,4,3,2};
    vector<vector<int>> S(M);

    int t=0;
    for(int x=1;x<=2*M;x++){
        int val=0,cnt=0;
        while(cnt<x) val=val*10+T[t],cnt+=T[t],t=(t+1)%6;
        S[x%M].push_back(val);
    }

    int res=0;
    for(int i=0;i<M;i++){
        if(i>N) break;
        int a=S[i][0],d=S[i][1];
        
        int k=1,g=1;
        while(k<=a) k*=10;
        d=(d-a)/k;
        while(g<=d) g*=10;

        int m=(N-i)/M+(i>0);
        res=(res+m%mod*a)%mod;
        d=d*k%mod;

        if(__gcd(mod,g)!=1){
            cout << '*' << i << '\n';
        }
        int inv=power(g-1,phi-1);
        int val=power(g,m)-1;
        val=val*inv%mod;
        val=(val+mod-m)%mod;
        val=val*inv%mod;

        res=(res+d*val%mod+mod)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
