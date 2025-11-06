#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

    int res=1;
    vector<int> p(N+1);
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        int x=i;
        vector<int> a;
        while(x>1){
            int j=p[x];
            a.push_back(j);
            while(x%j==0) x/=j;
        }
        int cnt=0,sz=(int)a.size();
        for(int mask=0;mask<(1<<sz);mask++){
            int x=1,k=1;
            for(int j=0;j<sz;j++) if(mask>>j&1) x*=a[j],k*=-1;
            cnt+=k*(N/x-i/x);
        }
        res=res*power(i,cnt)%mod;
        if(i%1000000==0) cout << i/1000000 << endl;
    }
    //int f10=23044331520000%mod;
    //cout << f10 << '\n';
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
