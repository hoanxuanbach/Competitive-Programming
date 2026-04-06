#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 123456789;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 1e8+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int ff[maxn],p[maxn];
const int M=100000;

void solve(){
    int N;cin >> N;

    int L=0,S=0;
    map<int,int> mp;
    vector<int> s(M);
    mp[s[0]]=0;
    for(int i=1;i<M;i++){
        int d=s[i-1]-1;
        s[i]=(d*d%mod*d+2)%mod;
        if(mp.find(s[i])!=mp.end()){
            L=mp[s[i]];
            S=i-L;
            cout << L << ' ' << i << endl;
            break;
        }
        mp[s[i]]=i;
    }

    int L2=0,S2=0;
    vector<int> s2(M);

    mp.clear();
    mp[s2[0]]=0;
    for(int i=1;i<M;i++){
        int d=s2[i-1]-1;
        s2[i]=(d*d%S*d+2)%S;
        if(mp.find(s2[i])!=mp.end()){
            L2=mp[s2[i]];
            S2=i-L2;
            cout << L2 << ' ' << i << endl;
            break;
        }
        mp[s2[i]]=i;
    }


    auto f = [&](int x){
        if(x<=4) return s[s[x]];
        x=L2+(x-L2)%S2;x=s2[x];
        return s[(x<L?x+S:x)];
    };

    ff[1]=1;
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        if((i/p[i])%p[i]==0) ff[i]=ff[i/p[i]]*p[i];
        else ff[i]=ff[i/p[i]]*(p[i]-1);
    }
    for(int i=1;i<=N;i++) ff[i]=(ff[i-1]+ff[i])%mod;

    int res=0;
    for(int x=1;x<=N;x++) res=(res+(ff[N/x]*2-1)*f(x)%mod)%mod;

    cout << res << '\n';
}   
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
