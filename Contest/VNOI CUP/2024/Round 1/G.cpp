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
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
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

const int L=29;

struct node{
    int cnt=0,sum=0,val=0;
    int nxt[2];
    node(int d=0){
        val=(1<<d)-1;
        memset(nxt,0,sizeof(nxt));
    }
};

vector<node> T;
void add(int u,int d,int x,int val){
    //cout << u << ' ' << d << ' ' << x << ' ' << val << endl;
    T[u].cnt+=val;
    T[u].sum+=x*val;
    if(d<0) return;
    int t=(x>>d)&1;x^=(t<<d);
    //cout << t << ' ' << endl;
    if(!T[u].nxt[t]){
        T[u].nxt[t]=(int)T.size();
        T.push_back(node());
    }
    add(T[u].nxt[t],d-1,x,val);

    int a=T[u].nxt[0],b=T[u].nxt[1];
    T[u].val=(1<<d)-1;
    if(a) T[u].val&=T[a].val;
    if(b) T[u].val&=T[b].val;
    if(!a || !T[a].cnt) T[u].val+=(1<<d);
}

vector<int> cc,nw[5];
int cnt[5],sum[5],val[5];

int query(int u,int d,int k){
    if(d<0) return 0;
    int a=T[u].nxt[0],b=T[u].nxt[1];
    cnt[0]=cnt[1]=sum[0]=sum[1]=0;
    val[0]=val[1]=(1<<d)-1;
    nw[0].clear();nw[1].clear();
    if(b){
        cnt[1]=T[b].cnt;
        sum[1]=T[b].sum;
        val[1]=T[b].val;
    }
    if(a){
        cnt[0]=T[a].cnt;
        sum[0]=T[a].sum;
        val[0]=T[a].val;
    }

    for(int x:cc){
        int t=(x>>d&1);
        x^=(t<<d);
        cnt[t]++;
        sum[t]+=x;
        val[t]&=x;
        nw[t].push_back(x);
    }

    if(!cnt[1]){
        cc=nw[0];
        if(!a){
            a=T[u].nxt[0]=(int)T.size();
            T.push_back(node(d));
        }
        return query(a,d-1,k);
    }
    else if(!cnt[0]){
        cc=nw[1];
        if(!b){
            b=T[u].nxt[1]=(int)T.size();
            T.push_back(node(d));
        }
        return k*(1<<d)+query(b,d-1,k);
    }
    else if(cnt[1]<k){
        cc=nw[0];
        if(!a){
            a=T[u].nxt[0]=(int)T.size();
            T.push_back(node(d));
        }
        return sum[1]+cnt[1]*(1<<d)+query(a,d-1,k-cnt[1]);
    }
    else{
        int x=val[0];
        cc=nw[1];cc.push_back(x);
        if(!b){
            b=T[u].nxt[1]=(int)T.size();
            T.push_back(node(d));
        }
        return (k-1)*(1<<d)+query(b,d-1,k);
    }
}

void solve(){
    int n,q;cin >> n >> q;
    T.push_back(node());
    for(int i=0;i<n;i++){
        int x;cin >> x;
        add(0,L,x,1);
    }
    for(int i=0;i<q;i++){
        int id,x;cin >> id >> x;
        if(id==1) add(0,L,x,1);
        else if(id==2) add(0,L,x,-1);
        else{
            cc.clear();
            cout << query(0,L,x) << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
