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
    int n;cin >> n;

    int cur=0;
    vector<int> nxt(n+2,-1),pre(n+2,-1);
    for(int i=0;i<n;i++){
        int x;cin >> x;
        nxt[cur]=x;
        pre[x]=cur;
        cur=x;
    }
    nxt[cur]=n+1;
    pre[n+1]=cur;

    int pos=0,cnt=0;
    while(nxt[pos]<=n && nxt[pos]>pos) cnt++,pos=nxt[pos]; 
    int res=cnt;

    for(int x=1;x<=n;x++){
        int a=pre[x],b=nxt[x];
        nxt[a]=b;pre[b]=a;
        if(!a){
            cnt--;
            if(pos==x) pos=0;
        }
        while(nxt[pos]<=n && nxt[pos]>pos) cnt++,pos=nxt[pos];
        res=max(res,cnt);
    }

    cout << n-res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}