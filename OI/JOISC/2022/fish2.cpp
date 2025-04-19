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
- insert(x),
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=35;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
int n,f[maxn];
struct node{
    int pl[maxl],pr[maxl],cl[maxl],cr[maxl],sl[maxl],sr[maxl];
    int szl,szr,sum,cnt;
    node(){}
    void reset(int x){
        szl=szr=1;
        pl[0]=pr[0]=x;
        sl[0]=sr[0]=cl[0]=cr[0]=0;
        sum=f[x];cnt=1;
    }
    void print(int l,int r){
        cout << '*' << l << ' ' << r << '\n';
        cout << sum << ' ' << cnt << '\n';
        cout << "#rr\n";
        for(int i=0;i<szr;i++) cout << pr[i] << ' ' << cr[i] << ' ' << sr[i] << '\n';
        cout << "#ll\n";
        for(int i=0;i<szl;i++) cout << pl[i] << ' ' << cl[i] << ' ' << sl[i] << '\n';
    }
};

namespace Segtree{
    node tree[4*maxn];
    node s[2];
    int st=-1;
    int add(int a,int b){
        return min(a+b,inf);
    }
    void merge(node &res,node &a,node &b){
        res.szl=a.szl;res.szr=b.szr;
        res.sum=add(a.sum,b.sum);
        res.cnt=0;
        for(int i=0;i<res.szl;i++) res.pl[i]=a.pl[i],res.cl[i]=a.cl[i],res.sl[i]=a.sl[i];
        for(int i=0;i<res.szr;i++) res.pr[i]=b.pr[i],res.cr[i]=b.cr[i],res.sr[i]=b.sr[i];
        int len=0,ok=0;
        if(a.sum>b.sum){
            int cur=b.sum;len=res.szr;ok=0;
            for(int i=0;i<a.szr;i++){
                if(cur+a.sr[i]<f[a.pr[i]]){
                    res.pr[res.szr]=a.pr[i];
                    res.sr[res.szr]=add(cur,a.sr[i]);
                    res.cr[res.szr++]=0;
                }
            }
        }
        else{
            int cur=a.sum;len=res.szl;ok=1;
            for(int i=0;i<b.szl;i++){
                if(cur+b.sl[i]<f[b.pl[i]]){
                    res.pl[res.szl]=b.pl[i];
                    res.sl[res.szl]=add(cur,b.sl[i]);
                    res.cl[res.szl++]=0;
                }
            }
        }
        b.sl[b.szl]=b.sum;b.cl[b.szl]=b.cnt;
        a.sr[a.szr]=a.sum;a.cr[a.szr]=a.cnt;
        int ca=0,cb=0,cc=len;
        auto fix = [&](int val){
            while(true){
                if(ca<a.szr && a.sr[ca]+b.sl[cb]>=f[a.pr[ca]]) ca++;
                else if(cb<b.szl && a.sr[ca]+b.sl[cb]>=f[b.pl[cb]]) cb++;
                else break;
            }
            if(ok && ca==a.szr){
                while(cc<res.szl && (cb==b.szl || res.pl[cc]<b.pl[cb])) cc++;
                if(cc<res.szl) res.cl[cc]+=val;
                else res.cnt+=val;
            }
            if(!ok && cb==b.szl){
                while(cc<res.szr && (ca==a.szr || res.pr[cc]>a.pr[ca])) cc++;
                if(cc<res.szr) res.cr[cc]+=val;
                else res.cnt+=val;
            }
        };
        for(int i=1;i<=a.szr;i++){
            ca=max(ca,i);
            fix(a.cr[i]);
        }
        ca=cb=0;cc=len;
        for(int i=1;i<=b.szl;i++){
            cb=max(cb,i);
            fix(b.cl[i]);
        }
    }
    void query(int l,int r,int id,int tl,int tr){
        if(r<tl || tr<l) return;
        if(tl<=l && r<=tr){
            if(st==-1) s[0]=tree[id],st=0;
            else st^=1,merge(s[st],s[st^1],tree[id]);
            return;
        }
        int mid=(l+r)>>1;
        query(l,mid,id<<1,tl,tr);query(mid+1,r,id<<1|1,tl,tr);
    }
    int query(int l,int r){
        st=-1;query(1,n,1,l,r);
        return s[st].cnt;
    }
    void update(int l,int r,int id,int pos){
        if(l==r){
            tree[id].reset(l);
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) update(l,mid,id<<1,pos);
        else update(mid+1,r,id<<1|1,pos);
        merge(tree[id],tree[id<<1],tree[id<<1|1]);
    }
    void build(int l,int r,int id){
        if(l==r){
            tree[id].reset(l);
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        merge(tree[id],tree[id<<1],tree[id<<1|1]);
        //tree[id].print(l,r);
    }
}
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> f[i];
    Segtree::build(1,n,1);
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int t,x,y;cin >> t >> x >> y;
        if(t==1) f[x]=y,Segtree::update(1,n,1,x);
        else cout << Segtree::query(x,y) << '\n';
    }
}
signed main(){
    //freopen("input.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
