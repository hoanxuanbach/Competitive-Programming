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
#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("arch=skylake")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf2=1e9+1;
const long long inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int bl=800;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

struct BIT{
    int n;
    long long bit[maxn];
    void build(int N){
        n=N;
        for(int i=1;i<=n;i++) bit[i]=inf;
    }
    long long query(int x){
        long long res=inf;
        for(int i=x;i>=1;i-=(i&(-i))) res=min(res,bit[i]);
        return res;
    }
    void update(int x,long long val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]=min(bit[i],val);
    }

}f1,f2;

vector<int> pv[maxn],sv[maxn];

struct Trie{
    struct node{
        int nxt[2],val=inf2,pos=0;
        node(){memset(nxt,0,sizeof(nxt));}
    };
    vector<node> T;
    void init(){
        T.push_back(node());
    }
    void add(int val,const string &s,int id){
        int u=0;
        bool check=pv[id].empty();
        for(char a:s){
            int c=a-'0';
            if(!T[u].nxt[c]){
                T[u].nxt[c]=(int)T.size();
                T.push_back(node());
            }
            u=T[u].nxt[c];
            if(check) pv[id].push_back(u);
            else sv[id].push_back(u);
            if(val<T[u].val) T[u].val=val,T[u].pos=id;
        }
    }
}pre,suf;

int n,m,L;
long long dp[maxn];

int pw[maxn];
vector<int> h[maxn];
string s[maxn];
int val[maxn];

namespace all{
    void solve(char c){
        vector<pii> p;
        for(int i=1;i<=m;i++) val[i]=inf2;
        for(int i=1;i<=n;i++){
            int vv;string ss;
            cin >> vv >> ss;
            int lt=0,rt=0;
            for(int j=0;j<(int)ss.length();j++){
                if(ss[j]!=c) break;
                else lt++;
            }
            for(int j=(int)ss.length()-1;j>=0;j--){
                if(ss[j]!=c) break;
                else rt++;
            }
            int len=min(m,max(lt,rt));
            val[len]=min(val[len],vv);
            if(len>bl) p.push_back({len,vv});
            //cout << len << ' ' << vv << '\n';
        }
        for(int i=m-1;i>=1;i--) val[i]=min(val[i],val[i+1]);
        for(int i=1;i<=m;i++){
            dp[i]=inf;
            for(int j=1;j<=min(i,bl);j++){
                if(val[j]!=inf2) dp[i]=min(dp[i],dp[i-j]+val[j]);
            }
            for(auto [len,vv]:p) dp[i]=min(dp[i],dp[i-min(i,len)]+vv);
        }
        cout << (dp[m]==inf?-1:dp[m]) << '\n';
    }
}

void solve(){
    cin >> m >> n >> L >> s[0];
    bool check1=false,check0=false;
    for(char c:s[0]){
        if(c=='0') check0=true;
        else check1=true;
    }
    if(!check1){
        all::solve('0');
        return;
    }
    if(!check0){
        all::solve('1');
        return;
    }
    pw[0]=1;
    for(int i=1;i<=m;i++) pw[i]=1LL*pw[i-1]*base%mod;
    pre.init();suf.init();
    for(int i=1;i<=n;i++){
        cin >> val[i] >> s[i];
        pre.add(val[i],s[i],i);
        reverse(s[i].begin(),s[i].end());
        suf.add(val[i],s[i],i);
        reverse(s[i].begin(),s[i].end());
    }

    f1.build(m+1);
    f2.build(m+1);

    for(int i=0;i<=n;i++){
        h[i].resize(s[i].length());
        h[i][0]=s[i][0]-'0';
        for(int j=1;j<s[i].length();j++) h[i][j]=(1LL*h[i][j-1]*base+s[i][j]-'0')%mod;
    }

    auto get_hash = [&](int id,int l,int r){
        return (h[id][r]-(l?1LL*h[id][l-1]*pw[r-l+1]%mod:0)+mod)%mod;
    };

    for(int i=1;i<=m;i++) dp[i]=inf;
    for(int i=1;i<=m;i++){
        {//update dp[i-1]->all
            f1.update(m+1-(i-1),dp[i-1]);
            int u=0;
            for(int j=0;j<min(bl,m-i+1);j++){
                u=pre.T[u].nxt[s[0][i+j-1]-'0'];
                if(!u) break;
                dp[i+j]=min(dp[i+j],dp[i-1]+pre.T[u].val);
            }
            int Max=bl;
            while(u){
                int id=pre.T[u].pos;
                int l=Max,r=min(m-i,(int)s[id].length()-1),p=Max-1;
                while(r>=l){
                    int mid=(l+r)>>1;
                    if(get_hash(0,i-1,i+mid-1)==get_hash(id,0,mid)) p=mid,l=mid+1;
                    else r=mid-1;
                }
                if(Max<=p) f2.update(m+1-(i+p),dp[i-1]+val[id]);
                else break;
                if(p==m-i) break;
                u=pre.T[pv[id][p]].nxt[s[0][i+p]-'0'];Max=p+1;
                //cout << "update " << i << ' ' << id << ' ' << p << '\n';
            }
        }
        {//calculate value of dp[i]
            dp[i]=min(dp[i],f2.query(m+1-i));
            int u=0;
            for(int j=0;j<min(i,bl);j++){
                u=suf.T[u].nxt[s[0][i-j-1]-'0'];
                if(!u) break;
                dp[i]=min(dp[i],dp[i-j-1]+suf.T[u].val);
            }
            int Max=bl+1;
            while(u){
                int id=suf.T[u].pos;
                int len=(int)s[id].length();
                int l=Max,r=min(i,len),p=Max-1;
                while(r>=l){
                    int mid=(l+r)>>1;
                    if(get_hash(0,i-mid,i-1)==get_hash(id,len-mid,len-1)) p=mid,l=mid+1;
                    else r=mid-1;
                }
                if(Max<=p) dp[i]=min(dp[i],f1.query(m+1-(i-p))+val[id]);
                else break;
                if(i==p) break;
                u=suf.T[sv[id][p-1]].nxt[s[0][i-p-1]-'0'];Max=p+1;
                //cout << "query " << i << ' ' << id << ' ' << p << '\n';
            }
        }
        //cout << dp[i] << '\n';
    }

    cout << (dp[m]==inf?-1:dp[m]) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
