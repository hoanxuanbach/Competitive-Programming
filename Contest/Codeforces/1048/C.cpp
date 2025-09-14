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
 
const int N = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,T;cin >> n >> T;
    vector<bool> leaf(n+1,true);
    vector<int> dep(n+1),cnt(n);

    int K=n;
    for(int i=2;i<=n;i++){
        int p;cin >> p;
        dep[i]=dep[p]+1;
        cnt[dep[i]]++;
        leaf[p]=false;
    }
    for(int i=1;i<=n;i++) if(leaf[i]) K=min(K,dep[i]);

    int S=0,x=0;
    vector<bool> B(n+1);B[0]=true;
    vector<int> C(n+1);

    auto work = [&](int d,int k){
        S+=d*k;
        bool check=false;
        for(int i=0;i<=S;i++){
            C[i]=B[i];
            if(i>=k) C[i]+=C[i-k];
            if(i>=(d+1)*k) C[i]-=B[i-(d+1)*k];
            if(i<=T && S-i<=n-T && C[i]) check=true;
        } 
        if(check){
            for(int i=0;i<=S;i++) B[i]=C[i];
        }
        S-=d*k;
        return check;
    };

    while(x<=K){
        int y=x;
        while(y<=K && cnt[x]==cnt[y]) y++;
        int d=y-x,k=cnt[x];
        
        work(d,k);
        if(work(d,k)) x+=d,S+=d*k;
        else{
            for(int i=20;i>=0;i--){
                if(d>>i&1){
                    if(work(1<<i,k)) x+=(1<<i),d-=(1<<i),S+=(1<<i)*k;
                    else d=(1<<i)-1;
                }
            }
            break;
        }
    }
    cout << x << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
