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
 
const int maxn = 1e7+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int M=50515093;
int N,S[maxn],A[maxn];

void dnc(int l,int r){
    if(l+1==r) return;
    int m=(l+r)>>1;
    dnc(l,m);dnc(m,r);
    if(A[m]>=A[m-1]) return;

    int rt=m,T=0;

    int S=0;
    for(int lt=m-1;lt>=l;lt--){
        S+=A[lt];
        int dl=(lt>l?A[lt]-A[lt-1]:A[lt]);
        int kl=m-lt;
        int fl=S-kl*A[lt];

        bool flag=false;
        while(rt<r){
            int cur=A[rt]*(rt-m)-T;
            if(cur>fl+dl*kl) break;
            if(cur>=fl){
                int nval=A[lt]-(cur-fl)/kl;
                if(nval<=A[rt]) break;
            }
            T+=A[rt];
            rt++;
        }
        int dr=(rt<r?A[rt]-A[rt-1]:M-A[rt-1]);
        int kr=rt-m;
        int fr=kr*A[rt-1]-T;
        //fr+i*kr i<=dr
        //fl+j*kl j<=dl

        //cout << '*' << lt << ' ' << rt << ' ' << kl << ' ' << kr << ' ' << dl << ' ' << dr << '\n';
        //cout << '*' << fl << ' ' << fr << '\n';
        int mx=fl+dl*kl;

        int add=(mx-fr)/kr;
        if(A[rt-1]+add>=A[lt]-dl){
            //cout << '*' << lt << ' ' << rt << ' ' << kl << ' ' << kr << ' ' << dl << ' ' << dr << '\n';
            //cout << '*' << S << ' ' << T << ' ' << fl << ' ' << fr << '\n';
            int L=max(fl,fr),R=fl+dl*kl;
            while(L<R){
                int K=(L+R)>>1;
                int al=A[lt]-(K-fl)/kl,ar=A[rt-1]+(K-fr)/kr;
                if(al<=ar) R=K;
                else L=K+1;
            }
            //cout << '*' << R << '\n';
            S-=R;T+=R;
            for(int i=m;i<rt;i++) A[i]=T/kr+(rt-i<=T%kr);
            for(int i=lt;i<m;i++) A[i]=S/kl+(m-i<=S%kl);
            break;
        }
    }
    //cout << "dnc " << l << ' ' << r << '\n';
    //for(int i=l;i<r;i++) cout << A[i] << ' ';
    //cout << '\n';
}

void solve(){
    cin >> N;
    S[0]=290797;
    for(int i=1;i<N;i++) S[i]=S[i-1]*S[i-1]%M;
    for(int i=0;i<N;i++){
        //cin >> S[i];
        A[i]=S[i];
    }
    dnc(0,N);

    int res=0,cnt=0;
    for(int i=0;i<N;i++){
        res+=abs(cnt);
        cnt+=(A[i]-S[i]);
    }
    cout << res << '\n';
    //for(int i=0;i<N;i++) cout << A[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
