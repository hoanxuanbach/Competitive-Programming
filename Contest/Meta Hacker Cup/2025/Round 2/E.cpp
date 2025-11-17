#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
const int inf = 1e18;
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N,M;cin >> N >> M;
    vector<int> A(N+1);
    for(int i=1;i<=N;i++){
        cin >> A[i];
        A[i]+=A[i-1];
    }

    int S=N*N;
    vector<int> B(S+1,-inf);B[0]=0;
    for(int i=1;i<=S;i++) for(int j=1;j<=min(i,N);j++) B[i]=min(inf,max(B[i],B[i-j]+A[j]));

    int x=1;
    for(int i=2;i<=N;i++) if((__int128)A[i]*x > (__int128)A[x]*i) x=i;

    //cout << x << ' ' << B[1] << ' ' << B[2] << ' ' << B[3] << '\n';

    int res=inf,a=-1,b=-1;
    for(int i=1;i<=S;i++){
        if(B[i]>=M){
            if(i<res) res=i,a=i,b=0;
        }
        else{
            int d=(M-B[i]);
            int k=(d-1)/A[x]+1;
            if(x*k+i<res) res=x*k+i,a=i,b=k;
        }
    }
    vector<int> d(N+1);d[x]+=b;

    while(a){
        int j=-1;
        for(int i=1;i<=min(a,N);i++) if(B[a]==B[a-i]+A[i]) j=i;
        assert(j!=-1);
        d[j]++;a-=j;
    }
    for(int i=N-1;i>=1;i--) d[i]+=d[i+1];
    cout << res << '\n';
    for(int i=1;i<=N;i++) cout << d[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cerr << t << endl;
        cout << "Case #" << t << ": ";
        solve();
    }
}
