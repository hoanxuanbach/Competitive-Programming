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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=100000000069;
const int maxn=500015;
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
}
const int iroot=power(3,mod-2);
const int base=101;

struct Palindrome_Tree{
    struct node{
        int len,slink,nxt[26];
    }tree[maxn];
    int par[maxn][maxl];
    Palindrome_Tree(){
        tree[1].slink=tree[2].slink=1;
        tree[1].len=-1;tree[2].len=0;
    }
    int lst=2,cnt=2;
    string s;
    void add(int p,int c){
        s+=char(c+26);
        while(tree[lst].len==p || (s[p]!=s[p-tree[lst].len-1])) lst=tree[lst].slink;
        if(tree[lst].nxt[c]){
            lst=tree[lst].nxt[c];
            return;
        }
        tree[lst].nxt[c]=++cnt;
        tree[cnt].len=tree[lst].len+2;
        if(tree[cnt].len==1){
            tree[cnt].slink=2;lst=cnt;
            return;
        }
        lst=tree[lst].slink;
        while(tree[lst].len==p || (s[p]!=s[p-tree[lst].len-1])) lst=tree[lst].slink;
        tree[cnt].slink=tree[lst].nxt[c];lst=cnt;
    }
    void build(){
        for(int i=1;i<=cnt;i++){
            par[i][0]=tree[i].slink;
            for(int j=1;j<20;j++) par[i][j]=par[par[i][j-1]][j-1];
        }
    }
    int f(int u,int len){
        if(tree[u].len<=len) return tree[u].len;
        for(int j=19;j>=0;j--){
            if(tree[par[u][j]].len>len) u=par[u][j];
        }
        return tree[par[u][0]].len;
    }
}P,S;
int pos_P[maxn],pos_S[maxn];


int h1[maxn],h2[maxn],pw[maxn];

int get_hash1(int l,int r){
    return (h1[r]-(__int128)h1[l-1]*pw[r-l+1]%mod+mod)%mod;
}
int get_hash2(int l,int r){
    return (h2[l]-(__int128)h2[r+1]*pw[r-l+1]%mod+mod)%mod;
}
string s;
int n,q;

void solve(){
    cin >> n >> s;
    s="$"+s;
    pw[0]=1;
    for(int i=1;i<=n;i++){
        h1[i]=((__int128)h1[i-1]*base%mod+(s[i]=='#'?0:s[i]-'a'+1))%mod;
        pw[i]=(__int128)pw[i-1]*base%mod;
    }
    for(int i=n;i>=1;i--){
        h2[i]=((__int128)h2[i+1]*base%mod+(s[i]=='#'?0:s[i]-'a'+1))%mod;
    }
    for(int i=1;i<=n;i++){
        P.add(i-1,s[i]-'a');
        pos_P[i]=P.lst;
    }
    P.build();
    for(int i=n;i>=1;i--){
        S.add(n-i,s[i]-'a');
        pos_S[i]=S.lst;
    }
    S.build();
    cin >> q;
    for(int i=1;i<=q;i++){
        int L,R;cin >> L >> R;
        int l=0,r=R-L,res=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(get_hash1(L,L+mid)==get_hash2(R-mid,R)) res=mid,l=mid+1;
            else r=mid-1;
        }
        int ans=0,way=0;
        if(res<R-L){
            int lt=L+res+1,rt=R-res-1;
            int sl=S.f(pos_S[lt],rt-lt+1);
            int sr=P.f(pos_P[rt],rt-lt+1);
            ans=rt-lt+1-max(sl,sr);
            if(sl==max(sl,sr)){
                int pl=lt+sl;
                l=0,r=res;
                int pos=-1;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(get_hash1(pl,pl+mid)==get_hash1(rt+1,rt+mid+1)) pos=mid,l=mid+1;
                    else r=mid-1;
                }
                way+=pos+2;
            }
            if(sr==max(sl,sr)){
                int pr=rt-sr;
                l=0,r=res;
                int pos=-1;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(get_hash1(pr-mid,pr)==get_hash1(lt-mid-1,lt-1)) pos=mid,l=mid+1;
                    else r=mid-1;
                }
                way+=pos+2;
            }
        }
        cout << ans << ' ' << way << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
