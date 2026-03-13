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

const int N = 1005;

void solve(){
    int n,m;cin >> n >> m;
    vector<bitset<N>> f(n);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        u--;v--;
        if(u<v) swap(u,v);
        f[u][v]=1;
    }

    int X=0;
    bitset<N> A;

    vector<int> D(n);
    vector<bitset<N>> B(n);

    int cnt=0;
    auto add = [&](bitset<N> S,int K){
        for(int i=n-1;i>=0;i--){
            if(S[i]){
                if(B[i][i]) S^=B[i],K^=D[i];
                else{
                    cnt++;
                    B[i]=S;
                    D[i]=K;
                    return;
                }
            }
        }
        assert(!K);
    };

    auto get = [&](bitset<N> S){
        int K=0;
        for(int i=n-1;i>=0;i--){
            if(S[i]){
                if(B[i][i]) S^=B[i],K^=D[i];
                else return -1LL;
            }
        }
        return K;
    };

    vector<bitset<N>> base(n);
    for(int i=0;i<n;i++) for(int j=0;j<i;j++) base[i][j]=1;

    int res=0;
    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<n;j++) assert(!A[j]);

        bitset<N> cur;cur[i]=1;
        int x=get(cur),y=get(f[i]),k=get(cur^f[i]);
        if(x!=-1 && A[i]) A[i]=0,X^=x;
        if(x!=-1 && y!=-1) X^=(x*y);
        else if(x!=-1){
            if(x) A^=f[i];
        }
        else if(y!=-1){
            A[i]=A[i]^y;
            if(A[i]){
                if(B[i][i]){
                    X^=D[i];
                    A^=B[i];
                }
                else{
                    res=(res+power(2,n-cnt-1))%mod;
                    cout << res << '\n';
                    return;
                }
            }
        }
        else if(k==0){
            if(A[i]) A[i]=0;
            else A^=f[i];
        }
        else if(k==1){
            if(A[i]) A^=(cur^f[i]),X^=k;
        }
        else if(k==-1){
            if(B[i][i]){
                if(D[i]) A^=f[i];
                for(int j=0;j<i;j++){
                    if(B[i][j] && f[i][j]) A[j]=A[j]^1;
                    if(B[i][j]) f[j]^=(f[i]&base[j]);
                    if(f[i][j]) f[j]^=(B[i]&base[j]);
                }
                if(A[i]){
                    X^=D[i];
                    A^=B[i];
                }
            }
            else{
                assert(n-cnt>=2);
                res=(res+power(2,n-cnt-2))%mod;
                add(f[i],A[i]);A[i]=0;
            }
        }
    }
    if(!X) res=(res+power(2,n-cnt))%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
