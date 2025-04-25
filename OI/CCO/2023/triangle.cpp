// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/

#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
};
const int iroot=power(3,mod-2);
const int base=101;
struct node{
    int Min=0,sum=0;
    node(int cur=0,int val=0){
        sum=val;
        Min=min(cur,0LL);
    }
    friend node operator+(node a,node b){
        return node(min(a.Min,a.sum+b.Min),a.sum+b.sum);
    };
};
struct Segtree{
    node tree[8*maxn];
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]=node(val,val);
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return node();
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}ST[3];

int n,q,a[maxn],aa[maxn];

namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        x=n-x+1;
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        x=n-x+1;
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
/*
ST[0]: total < l
ST[1]: all sticks that odd one out
ST[2]: sticks - total
*/

void update(int i,int val){
    BIT::update(i,val/2-a[i]/2);a[i]=val;
    ST[0].update(1,n,1,i,a[i]);
    ST[1].update(1,n,1,i,a[i]&1);
    val=(2*i-1<=n?(a[2*i-1]&1):0)-(a[i]/2);
    ST[2].update(1,2*n,1,2*i-1,val);
    if(i%2==0) ST[2].update(1,2*n,1,i,a[i]&1);
    else{
        int p=(i+1)/2;
        ST[2].update(1,2*n,1,i,(a[i]&1)-a[p]/2);
    }
}
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> aa[i];
    for(int i=n;i>=1;i--) update(i,aa[i]);
    auto check = [&](int mid){
        node cur;
        if(mid-1) cur=ST[0].query(1,n,1,1,mid-1)+ST[1].query(1,n,1,mid,min(2*mid-2,n));
        cur=cur+ST[2].query(1,2*n,1,2*mid-1,2*n);
        return (cur.Min>=0);
    };
    node st,md,en;
    auto check2 = [&](int mid,int p){
        node mm;
        if(p==2) mm=node(a[p-1]-3*mid,a[p-1]-3*mid);
        else{
            node s=node(a[p-1]-2*mid,a[p-1]-2*mid);
            int val=(2*p-3<=n?(a[2*p-3]&1):0LL)-mid;
            node t=node(val,val);
            mm=s+md+t;
        }
        //cout << mid << ' ' << st.Min << ' ' << st.sum << ' ' << mm.Min << ' ' << mm.sum << ' ' << en.sum << ' ' << en.sum << '\n';
        node res=st+mm+en;
        return (res.Min>=0);
    };
    for(int i=1;i<=q;i++){
        int p,d;cin >> p >> d;update(p,a[p]+d);
        int l=1,r=n;p=n+1;
        while(r>=l){
            int mid=(l+r)>>1;
            if(check(mid)) p=mid,r=mid-1;
            else l=mid+1;
        }
        //cout << '*' << p << '\n';
        if(p==1) cout << BIT::query(p) << '\n';
        else{
            if(p>2) st=ST[0].query(1,n,1,1,p-2);
            else st=node();
            if(p<=2*p-4) md=ST[1].query(1,n,1,p,min(2*p-4,n));
            else md=node();
            en=ST[2].query(1,2*n,1,2*p-2,2*n);
            //cout << st.Min << ' ' << st.sum << ' ' << md.Min << ' ' << md.sum << ' ' << en.Min << ' ' << en.sum << '\n';
            int total=BIT::query(p);
            l=1,r=a[p-1]/2;
            int res=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check2(mid,p)) res=mid,l=mid+1;
                else r=mid-1;
            }
            //cout << total << '\n';
            cout << total+res << '\n';
        }
    }
}

signed main(){
    //freopen("F.INP","r",stdin);
    //freopen("F.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}