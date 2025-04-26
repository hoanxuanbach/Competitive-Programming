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
#include "sprlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int l[55],r[55],n;

void solve(){
    vector<int> cur(n,2*n);
    vector<int> p(n,0);
    iota(p.begin(),p.end(),0);
    for(int i=0;i<n;i++) l[i]=0,r[i]=n;

    while(!p.empty()){
        shuffle(p.begin(),p.end(),rng);
        int sz=(int)p.size();
        vector<pii> pp;
        for(int i=0;i<sz;i+=2){
            if(i+1<sz){
                int m0=(l[p[i]]+r[p[i]])/2+1;
                int m1=(l[p[i+1]]+r[p[i+1]])/2+1;
                cur[p[i]]=m0;cur[p[i+1]]=m1;
                int d=tura(cur);
                if(d==0){
                    r[p[i]]=m0-1;
                    r[p[i+1]]=m1-1;
                }
                else if(d==2){
                    l[p[i]]=m0;
                    l[p[i+1]]=m1;
                }
                else pp.push_back({p[i],p[i+1]});
                cur[p[i]]=2*n;cur[p[i+1]]=2*n;
            }
            else{
                int m0=(l[p[i]]+r[p[i]])/2+1;
                cur[p[i]]=m0;
                int d=tura(cur);
                if(d==0) r[p[i]]=m0-1;
                else l[p[i]]=m0;
                cur[p[i]]=2*n;
            }
        }
        sz=(int)pp.size();
        for(int i=0;i<sz;i+=2){
            if(i+1<sz){
                int mf0=(l[pp[i].fi]+r[pp[i].fi])/2+1;
                int ms0=(l[pp[i].se]+r[pp[i].se])/2+1;
                int mf1=(l[pp[i+1].fi]+r[pp[i+1].fi])/2+1;
                int ms1=(l[pp[i+1].se]+r[pp[i+1].se])/2+1;

                cur[pp[i].fi]=mf0;cur[pp[i+1].fi]=mf1;
                int d=tura(cur);

                if(d==0){
                    r[pp[i].fi]=mf0-1;
                    l[pp[i].se]=ms0;
                    r[pp[i+1].fi]=mf1-1;
                    l[pp[i+1].se]=ms1;
                }
                else if(d==2){
                    l[pp[i].fi]=mf0;
                    r[pp[i].se]=ms0-1;
                    l[pp[i+1].fi]=mf1;
                    r[pp[i+1].se]=ms1-1;
                }
                else{
                    cur[pp[i+1].fi]=2*n;
                    d=tura(cur);
                    if(d==0){
                        r[pp[i].fi]=mf0-1;
                        l[pp[i+1].fi]=mf1;
                        l[pp[i].se]=ms0;
                        r[pp[i+1].se]=ms1-1;
                    }
                    else{
                        l[pp[i].fi]=mf0;
                        r[pp[i+1].fi]=mf1-1;
                        r[pp[i].se]=ms0-1;
                        l[pp[i+1].se]=ms1;
                    }
                }
                cur[pp[i].fi]=2*n;cur[pp[i+1].fi]=2*n;
            }
            else{
                int m0=(l[pp[i].fi]+r[pp[i].fi])/2+1;
                int m1=(l[pp[i].se]+r[pp[i].se])/2+1;
                cur[pp[i].fi]=m0;
                int d=tura(cur);
                if(d==0){
                    r[pp[i].fi]=m0-1;
                    l[pp[i].se]=m1;
                }
                else{
                    l[pp[i].fi]=m0;
                    r[pp[i].se]=m1-1;
                }
                cur[pp[i].fi]=2*n;
            }
        }
        vector<int> np;
        for(int i=0;i<n;i++) if(l[i]<r[i]) np.push_back(i);
        p=np;
    }
    vector<int> res(n,0);
    for(int i=0;i<n;i++) res[i]=l[i];
    koniec(res);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=10;n=dajN();
    while(test--) solve();
}
