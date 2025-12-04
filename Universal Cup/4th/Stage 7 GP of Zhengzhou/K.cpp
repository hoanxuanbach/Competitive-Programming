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
 
const int maxn = 5e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn];
int C(int n,int k){
    if(n<k || n<0 || k<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;  
}

int n,a[maxn];

pii tree[4*maxn][2];
void build(int l,int r,int id){
    if(l==r){
        tree[id][0]=tree[id][1]={inf,1};
        tree[id][l&1]={a[l],-l};
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id][0]=min(tree[id<<1][0],tree[id<<1|1][0]);
    tree[id][1]=min(tree[id<<1][1],tree[id<<1|1][1]);
}
pii query(int l,int r,int id,int tl,int tr,int t){
    if(tr<l || r<tl) return {inf,-1};
    if(tl<=l && r<=tr) return tree[id][t];
    int mid=(l+r)>>1;
    return min(query(l,mid,id<<1,tl,tr,t),query(mid+1,r,id<<1|1,tl,tr,t));
}

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    a[0]=inf;a[n+1]=-1;

    build(1,n,1);
    vector<int> res(n+1,-1);
    
    vector<pii> S;
    S.push_back({n+1,0});
    for(int i=1;i<=n;i++){
        if(res[i]!=-1){
            S.pop_back();
            continue;
        }
        int r=S.back().first;
        int l=S.back().second;
        pii x=query(1,n,1,i+1,r-1,(i&1)^1);
        int j=-x.second;

        if(a[i]==a[r] && a[j]>=a[l]){
            res[r]=-1;
            res[i]=1;
            S.pop_back();
        }
        else{
            res[i]=0;
            res[j]=1;
            S.push_back({j,i});
        }
    }

    for(int i=1;i<=n;i++) cout << (res[i]?')':'(');
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
