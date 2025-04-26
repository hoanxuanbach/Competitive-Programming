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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=1e6+5;
const int bl=650;
const int maxs=650;
const int maxm=(1<<20)+5;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
struct qry{
    int l,r,id;
    bool operator<(qry o){
        if(l!=o.l) return l<o.l;
        else return id<o.id;
    }
};
vector<qry> que;
map<char,int> mp;
string s1,s2;
int m,len1,len2;
int nxt1[maxn][5],pre1[maxn][5],nxt2[maxn][5],pre2[maxn][5],bit[maxn];
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int x){
    for(int i=x;i<=len2+2;i+=(i&(-i))) bit[i]++;
}
void backtrack_nxt(int pos1,int pos2,int t,int Max){
    if(t==Max){
        que.push_back({pos1,pos2,1});
        //cout << pos1 << ' ' << pos2 << '\n';
        return;
    }
    for(int i=0;i<4;i++) backtrack_nxt(nxt1[pos1][i]+1,nxt2[pos2][i]+1,t+1,Max);
}
void backtrack_pre(int pos1,int pos2,int t,int Max){
    if(t==Max){
        que.push_back({pos1+1,pos2+1,2});
        return;
    }
    for(int i=0;i<4;i++){
        int npos1=(pos1==-1?-1:pre1[pos1][i]-1);
        int npos2=(pos2==-1?-1:pre2[pos2][i]-1);
        backtrack_pre(npos1,npos2,t+1,Max);
    }
}
void solve(){
    cin >> s1 >> s2 >> m;
    len1=s1.length();len2=s2.length();
    s1="#"+s1;s2="#"+s2;
    mp['A']=0;mp['C']=1;mp['G']=2;mp['T']=3;
    for(int i=1;i<=len1;i++){
        for(int j=0;j<4;j++) pre1[i][j]=pre1[i-1][j];
        pre1[i][mp[s1[i]]]=i;
    }
    for(int i=1;i<=len2;i++){
        for(int j=0;j<4;j++) pre2[i][j]=pre2[i-1][j];
        pre2[i][mp[s2[i]]]=i;
    }
    for(int i=0;i<4;i++){
        nxt1[len1+1][i]=nxt1[len1+2][i]=len1+1;
        nxt2[len2+1][i]=nxt2[len2+2][i]=len2+1;
    }
    for(int i=len1;i>=1;i--){
        for(int j=0;j<4;j++) nxt1[i][j]=nxt1[i+1][j];
        nxt1[i][mp[s1[i]]]=i;
    }
    for(int i=len2;i>=1;i--){
        for(int j=0;j<4;j++) nxt2[i][j]=nxt2[i+1][j];
        nxt2[i][mp[s2[i]]]=i;
    }
    backtrack_nxt(1,1,0,m/2);
    backtrack_pre(len1,len2,0,m-m/2);
    sort(que.begin(),que.end());
    int ans=0;
    for(auto x:que){
        if(x.id==1) update(x.r);
        else ans+=query(x.r);
    }
    for(int i=0;i<=len2+2;i++) bit[i]=0;
    for(int i=(int)que.size()-1;i>=0;i--){
        auto x=que[i];
        if(x.id==1) update(len2+3-x.r);
        else ans+=query(len2+2-x.r);
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
