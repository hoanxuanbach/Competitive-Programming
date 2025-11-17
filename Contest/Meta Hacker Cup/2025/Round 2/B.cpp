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

const int S = 1e6;
int cnt[S+5],d[S+5];

void solve(){
    int N,M;cin >> N >> M;
    for(int i=0;i<=S+1;i++) cnt[i]=0;
    for(int i=0;i<N;i++){
        int x;cin >> x;
        cnt[x]++;
    }
    
    vector<int> A(M);
    for(int i=0;i<M;i++) cin >> A[i];
    sort(A.begin(),A.end());
    for(int i=1;i<M;i++) A[i]+=A[i-1];


    int l=0,r=S,res=0;
    auto check = [&](int x){
        int k=0;
        for(int i=0;i<=S;i++) d[i]=0;

        int T=0;
        for(int i=x;i<=S;i++){
            if(!cnt[i]) continue;
            T++;d[T]=cnt[i];k+=cnt[i];
        }
        if(T>M) return false;
        for(int i=T;i>0;i--) d[i-1]+=d[i];
        for(int i=T;i>0;i--) d[i-1]+=d[i];

        for(int i=1;i<=T;i++) if(d[i]>A[M-i]) return false;

        res=k;
        return true;
    };
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1;
        else l=mid+1; 
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
