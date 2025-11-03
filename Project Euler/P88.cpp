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

int n,f[maxn];

int k=1,s=0;
void dfs(int i,int x){
    if(x*i>n){
        if(x>1){
            int d=(s*(x-2))%(x-1);
            int ns=(s+d)/(x-1);
            for(int j=k+d;j<=n;j+=(x-1)) f[j]=min(f[j],ns*x),ns++;
        }
        return;
    }
    dfs(i+1,x);
    k++;s+=i;
    dfs(i,x*i);
    k--;s-=i;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) f[i]=inf;
    dfs(2,1);

    int res=0;
    set<int> ss;
    for(int i=2;i<=n;i++) ss.insert(f[i]);
    for(int x:ss) res+=x;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
