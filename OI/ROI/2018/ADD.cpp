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
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=300000;
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

namespace Segtree{
    piii tree[4*maxn];
    piii f(piii a,piii b){
        if(b.fi.fi==-1) return a;
        else if(a.fi.fi==-1) return b;
        else return {max(a.fi,{b.fi.fi+a.se,b.fi.se}),a.se+b.se};
    }
    void update(int l,int r,int id,int p,piii val){
        if(l==r){
            tree[id]=val;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=f(tree[id<<1],tree[id<<1|1]);
    }
    piii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {{-1,-1},0};
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return f(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}

int n;
string s[maxn];
vector<int> pre[maxn],pos[maxn],dd[maxn];
pii cpos[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        reverse(s[i].begin(),s[i].end());
        int sz=(int)s[i].length();
        pre[i].assign(sz,-1);
        pos[i].assign(sz,-1);
        for(int j=0;j<sz;j++){
            if(j) pre[i][j]=pre[i][j-1];
            if(s[i][j]=='1') dd[j].push_back(i);
            if(j && s[i][j-1]=='1') pre[i][j]=j-1;
        }
    }
    int cur=0;
    for(int i=0;i<maxa;i++){
        sort(dd[i].begin(),dd[i].end(),[&i](int x,int y){
            int px=pre[x][i],py=pre[y][i];
            if(px!=-1) px=pos[x][px];
            if(py!=-1) py=pos[y][py];
            return px<py;
        });

        for(int x:dd[i]){
            cpos[cur]={x,i};
            pos[x][i]=cur++;
        }
    }
    for(int i=1;i<=4*cur;i++) Segtree::tree[i]={{-1,-1},0};
    for(int i=1;i<=n;i++){
        int sz=(int)s[i].length();
        Segtree::update(1,cur,1,cur-pos[i][sz-1],{{sz-1,pos[i][sz-1]},1});
    }
    string res(Segtree::query(1,cur,1,1,cur).fi.fi+2,'0');
    int l=1;
    while(l<=cur){
        auto [pr,cnt]=Segtree::query(1,cur,1,l,cur);
        auto [d,f1]=pr;

        if(d==-1) break;
        //cout << l << ' ' << d << ' ' << f1 << ' ' << cnt << endl;

        int r=f1,num=0;
        vector<pii> event;

        while(true){
            pii a=cpos[f1];
            event.push_back(a);
            Segtree::update(1,cur,1,cur-pos[a.fi][a.se],{{-1,-1},0});
            a.se=pre[a.fi][a.se];
            if(a.se!=-1) Segtree::update(1,cur,1,cur-pos[a.fi][a.se],{{a.se,pos[a.fi][a.se]},1}),num++;

            if(f1==0){
                r=f1;
                break;
            }

            auto [pr2,cnt2]=Segtree::query(1,cur,1,cur-f1+1,cur);
            auto [d2,f2]=pr2;

            if(d2==-1){
                r=f1;
                break;
            }

            //cout << "nxt " << d2 << ' ' << f2 << ' ' << cnt2 << endl;

            if(d2+cnt-cnt2+num>d){d++;break;}
            else if(d2+cnt-cnt2+num==d) f1=f2;
            else{r=f1;break;}
        }

        r=cur-r;
        //cout << r << endl;
        while(!event.empty()){
            pii a=event.back();event.pop_back();
            Segtree::update(1,cur,1,cur-pos[a.fi][a.se],{{a.se,pos[a.fi][a.se]},1});
            a.se=pre[a.fi][a.se];
            if(a.se!=-1) Segtree::update(1,cur,1,cur-pos[a.fi][a.se],{{-1,-1},0});
        }
        while(l<=r){
            auto [pr,cnt2]=Segtree::query(1,cur,1,l,l);
            auto [d2,f2]=pr;
            Segtree::update(1,cur,1,l,{{-1,-1},0});
            if(d2!=-1){
                if(d2==d){
                    pii a=cpos[f2];
                    a.se=pre[a.fi][a.se];
                    if(a.se!=-1) Segtree::update(1,cur,1,cur-pos[a.fi][a.se],{{a.se,pos[a.fi][a.se]},1});
                }
                res[d--]='1';
            }
            l++;
        }
    }

    while(!res.empty() && res.back()=='0') res.pop_back();
    reverse(res.begin(),res.end());
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
