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

int T=4000;
int f[10005];

int F(int N){
    memset(f,0,sizeof(f));
    int X=T;
    while(true){
        if(f[X]==0 && f[X+1]==0){
            if(N<3) return X-T;
            f[X]=f[X-1]=f[X+1]=1,X-=2,N-=3;
        }
        else if(f[X]==0 && f[X+1]==1) swap(f[X],f[X+1]),X+=2;
        else if(f[X]==1 && f[X+1]==0) f[X]=0,N++,X+=2;
        else f[X+1]=0,N++,X--;
    }
}

const int M = 1000;
void solve(){

    vector<int> f(M+1);
    for(int i=0;i<=M;i++) f[i]=F(i);
    for(int i=M;i>=1;i--) f[i]-=f[i-1];

    int A=-1,T=-1;
    for(int i=1;i<=M;i++) if(f[i]==216){
        if(A==-1) A=i;
        else if(T==-1){
            T=i-A;
            break;
        }
    }

    int base=0,total=0;
    for(int i=0;i<A;i++) base+=f[i];
    for(int i=0;i<T;i++) total+=f[A+i];

    int N;cin >> N;N-=A;
    int res=base+(N/T)*total;
    N%=T;
    for(int i=0;i<=N;i++) res+=f[A+i];

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
