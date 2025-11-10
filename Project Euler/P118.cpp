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
    int N=100000000;
    vector<int> p(N);p[0]=p[1]=1;
    for(int i=2;i<N;i++) if(!p[i]){
        for(int j=i*i;j<N;j+=i) p[j]=1;
    }
    
    int S=9;
    vector<int> f(1<<S);
    for(int i=1;i<(1<<S);i++){
        if(__builtin_popcount(i)<=8){
            string s;
            for(int j=0;j<S;j++) if(i>>j&1) s+=char('0'+j+1);
            do{
                if(!p[stoi(s)]) f[i]++;
            }while(next_permutation(s.begin(),s.end()));
        }
    }

    vector<int> g(1<<S);g[0]=1;
    for(int i=1;i<(1<<S);i++){
        int j=S-1;
        while(!(i>>j&1)) j--;
        for(int k=0;k<(1<<j);k++) if((i&k)==k){
            int x=k|(1<<j);
            g[i]+=g[i^x]*f[x];
        }
    }
    cout << g[(1<<S)-1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
