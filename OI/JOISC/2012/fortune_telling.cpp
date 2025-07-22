#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){   
    int n,m,k;cin >> n >> m >> k;
    vector<array<int,3>> P;

    vector<int> com={1,m+1};

    for(int i=0;i<k;i++){
        int a,b,c,d;cin >> a >> b >> c >> d;
        P.push_back({a,c,d});
        P.push_back({b+1,c,d});
        com.push_back(c);
        com.push_back(d+1);
    }
    sort(P.begin(),P.end());
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size()-1;


    vector<int> cnt(4*sz),lazy(4*sz);
    function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            cnt[id]=com[r]-com[l-1]-cnt[id];
            lazy[id]^=1;
            return;
        }
        int mid=(l+r)>>1;
        if(lazy[id]){
            cnt[id<<1]=com[mid]-com[l-1]-cnt[id<<1],cnt[id<<1|1]=com[r]-com[mid]-cnt[id<<1|1];
            lazy[id<<1]^=1,lazy[id<<1|1]^=1;lazy[id]=0;
        }
        update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    };

    int pre=1,res=0;
    for(auto [x,l,r]:P){
        //cout << pre << ' ' << x << ' ' << cnt[1] << '\n';
        res+=(x-pre)*cnt[1];pre=x;
        l=lower_bound(com.begin(),com.end(),l)-com.begin()+1;
        r=lower_bound(com.begin(),com.end(),r+1)-com.begin();
        update(1,sz,1,l,r);
    }
    res+=(n+1-pre)*cnt[1];
    cout << n*m-res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
6 5 3
2 4 1 4
4 6 3 5
1 2 3 5
*/