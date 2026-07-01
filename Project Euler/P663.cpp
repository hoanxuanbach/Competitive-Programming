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
    int N;cin >> N;
    int L,R;cin >> L >> R;
    vector<int> t(2*R);t[2]=1;
    for(int i=3;i<2*R;i++) t[i]=(t[i-1]+t[i-2]+t[i-3])%N;

    vector<int> A(N);
    for(int i=1;i<=L;i++) A[t[2*i-2]]+=2*t[2*i-1]-N+1;

    vector<int> T(4*N),lt(4*N),rt(4*N),S(4*N);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            S[id]=A[l];
            T[id]=lt[id]=rt[id]=max(0LL,A[l]);
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        T[id]=max({T[id<<1],T[id<<1|1],rt[id<<1]+lt[id<<1|1]});
        lt[id]=max(lt[id<<1],S[id<<1]+lt[id<<1|1]);
        rt[id]=max(rt[id<<1|1],S[id<<1|1]+rt[id<<1]);
        S[id]=S[id<<1]+S[id<<1|1];
    };
    function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int x,int val){
        if(l==r){
            A[l]+=val;
            S[id]=A[l];
            T[id]=lt[id]=rt[id]=max(0LL,A[l]);
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,val);
        else update(mid+1,r,id<<1|1,x,val);
        T[id]=max({T[id<<1],T[id<<1|1],rt[id<<1]+lt[id<<1|1]});
        lt[id]=max(lt[id<<1],S[id<<1]+lt[id<<1|1]);
        rt[id]=max(rt[id<<1|1],S[id<<1|1]+rt[id<<1]);
        S[id]=S[id<<1]+S[id<<1|1];
    };
    build(0,N-1,1);

    int res=0;
    for(int i=L+1;i<=R;i++){
        update(0,N-1,1,t[2*i-2],2*t[2*i-1]-N+1);
        res+=T[1];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
