#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2=(mod+1)/2;
const int maxn = 100005;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int val[20][2*maxn];
pii tree[4*maxn];

void update(int l,int r,int id,int x,pii v){
    //if(id==1) cout << "update " << x << ' ' << v.first << ' ' << v.second << '\n'; 
    if(l==r){
        tree[id]=v;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,v);
    else update(mid+1,r,id<<1|1,x,v);
    tree[id]={(tree[id<<1].first*tree[id<<1|1].first)%mod,(tree[id<<1].first*tree[id<<1|1].second+tree[id<<1].second)%mod};
}   

void solve(){
    int n,k,q;cin >> n >> k >> q;

    int X=1,S=0;
    while(X<=n) X*=k,S++;

    for(int i=1;i<=S;i++) for(int j=0;j<(1<<(i-1));j++){
        int cnt=i-1-__builtin_popcount(j);
        val[i][j]=power(2,cnt);
    }

    vector<int> a(n),b(n),c(n);
    vector<vector<int>> f(n+1);
    for(int i=0;i<n;i++){
        cin >> c[i];
        while(c[i]%k==0) c[i]/=k,b[i]++;
        f[c[i]].push_back(i);
    }
    for(int i=0;i<n;i++){
        int x;cin >> x;
        while(x%k==0) x/=k,a[i]++;
        assert(x==c[i]);
    }

    int base=1;
    auto build = [&](int i){
        //cout << "build " << i << '\n';
        int sz=(int)f[i].size();
        vector<bool> p(sz);

        auto nxt = [&](int mask,int cb,int ca){
            if(ca==cb-1) mask|=(1<<ca);
            else{
                if(cb>=1) cb--;
                if(ca==sz-1) ca--;
                int xr=((1<<(ca+1))-1)^((1<<cb)-1);
                mask|=xr;
            }
            return mask;
        };

        int cur=0;
        for(int x:f[i]){
            int sum=0;
            for(int j=max(0LL,b[x]-1);j<a[x];j++){
                if(p[j]) continue;
                int mask=nxt(cur,b[x],j);
                if(mask!=-1) sum=(sum+val[sz][mask])%mod;
            }
            p[a[x]]=true;
            int nw=nxt(cur,b[x],a[x]),inv=power(val[sz][cur],mod-2);
            update(0,n-1,1,x,{val[sz][nw]*inv%mod,sum*inv%mod});
            cur=nw;
        }
    };

    base=power(2,n);
    for(int i=1;i<=n;i++){
        build(i);
        if(!f[i].empty()) base=base*inv2%mod;
    }

    auto del = [&](int i,int x){
        f[i].erase(find(f[i].begin(),f[i].end(),x));
    };
    auto add = [&](int i,int x){
        f[i].push_back(x);
        sort(f[i].begin(),f[i].end());
    };

    int res=base*tree[1].second%mod;
    cout << res << ' ';

    for(int i=0;i<q;i++){
        int x,y;cin >> x >> y;
        x--;y--;
        del(c[x],x);add(c[x],y);
        del(c[y],y);add(c[y],x);
        swap(c[x],c[y]),swap(b[x],b[y]),swap(a[x],a[y]);
        build(c[x]);
        if(c[x]!=c[y]) build(c[y]);
        res=base*tree[1].second%mod;
        cout << res << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}
