#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

struct Query{
    int t,m,k,x,y;
};

struct BIT{
    int sz;
    vector<int> bit;
    BIT(int _sz=0):sz(_sz){
        bit.assign(sz+1,0);
    }
    void update(int x,int val){
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};

void solve(){
    int n,M,K,q;cin >> n >> M >> K >> q;
    vector<int> a(n),com;
    for(int i=0;i<n;i++) cin >> a[i],com.push_back(a[i]);
    vector<Query> Q;
    for(int i=0;i<q;i++){
        int t;cin >> t;
        if(t==1){
            int m,k,x;cin >> m >> k >> x;
            Q.push_back({t,m,k,x,-1});
        }
        else if(t==2){
            int p,v;cin >> p >> v;
            Q.push_back({t,p-1,v,-1,-1});
            com.push_back(v);
        }
        else{
            int m,k,l,r;cin >> m >> k >> l >> r;
            Q.push_back({t,m,k,l,r});
        }
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    /*
    cout << "*com\n";
    for(int x:com) cout << x << ' ';
    cout << '\n';
    */
    int total=0;
    BIT sum(sz),cnt(sz);

    auto get_all = [&](int x){
        int pos=lower_bound(com.begin(),com.end(),x)-com.begin();
        //cout << "get_all " << x << ' ' << pos << ' ' << sum.query(pos) << ' ' << cnt.query(pos) << '\n';
        return pii{total-sum.query(pos),n-cnt.query(pos)};
    };

    auto get = [&](int m,int k){
        auto check = [&](int x){
            pii A=get_all(x),B=get_all(x+m+1);
            //cout << A.fi << ' ' << A.se << ' ' << B.fi << ' ' << B.se << '\n';
            if(B.se>=k) return true;
            if(A.se<k) return false;
            int nk=k-B.se;A.fi-=B.fi;A.se-=B.se;
            //cout << '*' << x << ' ' << m << ' ' << k << ' ' << x*A.se << '\n';
            if(A.fi-m*nk<x*A.se) return false;
            else return true;
        };
        
        //check(-1);check(0);check(1);check(2);
        int l=-2e9,r=1e9,res=-inf;
        
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) res=mid,l=mid+1;
            else r=mid-1;
        }
        
        return res;
    };

    vector<int> A=a;

    for(int i=0;i<n;i++){
        total+=a[i];
        int pos=lower_bound(com.begin(),com.end(),a[i])-com.begin();
        sum.update(pos+1,a[i]);
        cnt.update(pos+1,1);
        a[i]=pos;
    }  

    int X=get(M,K);
    int cur=total-M*K;
    for(int i=0;i<n;i++){
        if(A[i]>=X+M+1) A[i]-=M;
        else if(A[i]>=X) A[i]=X;
        cur-=A[i];
    }
    for(int i=0;i<n;i++) if(A[i]==X && cur) cur--,A[i]++;
    sort(A.begin(),A.end());

    for(int i=0;i<n;i++) cout << A[i] << ' ';
    cout << '\n';

    auto get_sum = [&](int x){
        int res=0,pos=0;
        for(int i=(1<<20);i>=1;i>>=1){
            if(pos+i>sz) continue;
            if(x>=cnt.bit[pos+i]) x-=cnt.bit[pos+i],res+=sum.bit[pos+i],pos+=i;
        }
        return res+x*(pos<sz?com[pos]:0);
    };

    auto query = [&](int d,int x,int m,int k){
        pii fst = get_all(d),lst=get_all(d+m+1);
        //cout << '*' << d << ' ' << x << ' ' << get_sum(x) << ' ';
        if(x<=n-fst.se) return get_sum(x);
        if(x>=n-lst.se) return get_sum(x)-m*(k-n+x);
        int res=total-fst.fi;x-=n-fst.se;

        int middle=fst.fi-lst.fi-m*(k-lst.se),ss=fst.se-lst.se;
        int num=(middle%ss+ss)%ss,val=(middle-num)/ss;num=ss-num;
        //cout << "MID " << val << ' ' << x << ' ' << num << ' ' << middle << ' ';
        return res+val*x+max(x-num,0LL);
    };

    for(int i=0;i<q;i++){
        if(Q[i].t==1){
            int d=get(Q[i].m,Q[i].k);
            //cout << query(d,Q[i].x,Q[i].m,Q[i].k) << ' ' << query(d,Q[i].x-1,Q[i].m,Q[i].k) << '\n';
            int res=query(d,Q[i].x,Q[i].m,Q[i].k)-query(d,Q[i].x-1,Q[i].m,Q[i].k);
            cout << res << '\n';
        }
        else if(Q[i].t==2){
            int x=Q[i].m,val=Q[i].k;
            int pos=lower_bound(com.begin(),com.end(),val)-com.begin();
            total-=com[a[x]];
            sum.update(a[x]+1,-com[a[x]]);
            cnt.update(a[x]+1,-1);
            a[x]=pos;
            total+=val;
            sum.update(pos+1,val);
            cnt.update(pos+1,1);
        }
        else{
            int d=get(Q[i].m,Q[i].k);
            //cout << query(d,Q[i].y,Q[i].m,Q[i].k) << ' ' << query(d,Q[i].x-1,Q[i].m,Q[i].k) << '\n';
            int res=query(d,Q[i].y,Q[i].m,Q[i].k)-query(d,Q[i].x-1,Q[i].m,Q[i].k);
            cout << res << '\n';
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
