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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int maxn=200005;
const int maxsz=3e7+5;
const int bl=450;
int n,sz,st[maxn],up[maxn],down[maxn],p[maxn];
long long res[maxsz],total[maxn];
vector<pii> edge,q[maxn];
namespace Block{
    int cur[maxn],num[bl];
    void reset(){
        for(int i=0;i<=n;i++) cur[i]=i;
        for(int i=0;i<=n/bl;i++) num[i]=0;
    }
    int query(int x){
        return num[x/bl]+cur[x];
    }
    void update(int x){
        for(int i=x/bl+1;i<=n/bl;i++) num[i]--;
        for(int i=x;i<=min((x/bl+1)*bl-1,n);i++) cur[i]--;
    }
}
void calupdown(){
    vector<int> cup;
    int pup=0,Max=0;
    for(int i=1;i<=n;i++){
        if(Max>p[i]){
            int l=0,r=(int)cup.size()-1;
            while(r>=l){
                int mid=(r+l)>>1;
                if(p[cup[mid]]>p[i]){up[i]=cup[mid];r=mid-1;}
                else l=mid+1;
            }
        }
        else{up[i]=i;cup.push_back(i);Max=p[i];}
    }
    int Min=n+1,pdown=n+1;
    for(int i=n;i>=1;i--){
        if(p[i]>Min) down[i]=pdown;
        else{down[i]=i;pdown=i;Min=p[i];}
    }
}
void f(){
    Block::reset();
    edge.clear();
    for(int i=1;i<=n;i++) q[i].clear();
    calupdown();
    int cur=n;
    for(int i=n;i>=1;i--){
        Block::update(p[i]);
        res[i]=Block::query(p[i]-1);
        int pos=0;
        for(pii x:q[up[i]]){
            if(x.fi==down[i]) pos=x.se;
        }
        if(pos) edge.push_back({i,pos});
        else{
            pos=(int)q[up[i]].size();
            for(int j=0;j<(int)q[up[i]].size();j++){
                if(q[up[i]][j].fi>down[i]){pos=j;break;}
            }
            q[up[i]].insert(q[up[i]].begin()+pos,{down[i],++cur});
            edge.push_back({i,cur});
        }
        while(!q[i].empty()){
            pii x=q[i].back();q[i].pop_back();
            int cu=up[x.fi],cd=down[i];
            res[x.se]=Block::query(p[x.fi]-1);
            if(cu==i && cd==x.fi) continue;
            if(q[cu].empty() || q[cu].back().fi!=cd) q[cu].push_back({cd,++cur});
            edge.push_back({x.se,q[cu].back().se});
        }
    }
    for(int i=(int)edge.size()-1;i>=0;i--) res[edge[i].fi]+=res[edge[i].se];
}
void solve(){
    cin >> sz;
    for(int i=1;i<=sz;i++) cin >> st[i];
    int Max=0,pre=0;
    for(int i=1;i<=sz;i++){
        Max=max(Max,st[i]);
        if(Max==i){
            n=0;
            for(int j=pre+1;j<=i;j++) p[++n]=st[j]-pre;
            f();
            for(int j=1;j<=n;j++) total[j+pre]+=res[j]+j-1;
            reverse(p+1,p+n+1);
            for(int j=1;j<=n;j++) p[j]=n-p[j]+1;
            f();
            for(int j=1;j<=n;j++) total[n-j+1+pre]+=res[j]+j-1;
            Max=0;pre=i;
        }
    }
    for(int i=1;i<=sz;i++) cout << total[i] << ' ';
    cout << '\n';
}
signed main(){
    //freopen("LIN.INP","r",stdin);
    //freopen("LIN.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
