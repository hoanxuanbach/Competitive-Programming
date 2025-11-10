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
    int n,L,k;cin >> n >> L >> k;

    int S=2*n+2*L+1;
    
    vector<int> f(S+1);
    vector<bool> segment(S);
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        f[x]++;f[x+L]--;
        segment[x]=true;
    }
    for(int i=1;i<=S;i++) f[i]+=f[i-1];

    vector<int> g0(S+1),g1(S+1),g2(S+1);
    for(int i=S;i>=0;i--){
        g0[i]=(f[i]==(k-1));
        g1[i]=(f[i]==k);
        g2[i]=(f[i]==(k+1));
        if(i<S){
            g0[i]+=g0[i+1];
            g1[i]+=g1[i+1];
            g2[i]+=g2[i+1];
        }
    }   

    int base=g1[0];
    
    vector<int> tree(4*S),lazy(4*S);
    function<int(int,int,int,int)> get = [&](int l,int r,int id,int x){
        if(l==r) return tree[id];
        int mid=(l+r)>>1;
        if(x<=mid) return get(l,mid,id<<1,x)+lazy[id];
        else return max(tree[id<<1],get(mid+1,r,id<<1|1,x))+lazy[id];
    };
    function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]+=val;
            lazy[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1])+lazy[id];
    };

    int res=base;
    for(int i=0;i<S-L;i++){
        update(0,S-1,1,i,i,(g1[i]-g1[i+L])-(g2[i]-g2[i+L]));
        if(segment[i]){
            int cur=base-(g1[i]-g1[i+L])+(g2[i]-g2[i+L]);
            cur+=get(0,S-1,1,i);
            res=max(res,cur);
        }
        update(0,S-1,1,max(0LL,i-L+1),i,(f[i]==(k-1))+(f[i]==(k+1))-2*(f[i]==k));
    }

    tree.assign(4*S,0);
    lazy.assign(4*S,0);
    for(int i=S;i>=L;i--){
        update(0,S-1,1,S-i,S-i,(g1[i-L]-g1[i])-(g2[i-L]-g2[i]));
        if(segment[i-L]){
            int cur=base-(g1[i-L]-g1[i])+(g2[i-L]-g2[i]);
            cur+=get(0,S-1,1,S-i);
            res=max(res,cur);
        }
        update(0,S-1,1,max(0LL,S-i-L+1),S-i,(f[i-1]==(k-1))+(f[i-1]==(k+1))-2*(f[i-1]==k));
    }

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}