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
    int M=20300713;
    vector<int> s={14025256};
    
    vector<int> f(M);
    while(!f[s.back()]){
        f[s.back()]=(int)s.size();
        s.push_back(s.back()*s.back()%M);
    }
    s.pop_back();


    string S;
    for(int x:s) S+=to_string(x);
    
    int T=0;
    for(char c:S) T+=c-'0';
    
    int n=(int)S.size();
    vector<int> p(T);p[0]=1;
    for(int i=0;i<100;i++){
        cout << '*' << i << endl;
        int x=0;
        for(int j=0;j+1<n;j++){
            x+=S[(i+j)%n]-'0';
            if(!p[x]) p[x]=i+1;
        }
    }

    int N,res=0;cin >> N;
    for(int i=0;i<min(T,N+1);i++){
        if(!p[i]){
            assert(false);
        }
        res+=((N-i)/T+(i>0))*p[i];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
