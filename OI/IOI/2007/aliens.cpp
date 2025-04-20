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
const int base=101;

void solve(){
    int N,X,Y;cin >> N >> X >> Y;
    auto query = [&](int x,int y){
        if(x<1 || y<1 || x>N || y>N) return 0LL;
        cout << "examine " << x << ' ' << y << endl;
        string s;cin >> s;
        return (int)(s=="true");
    };
    int lx=-1,rx=-1,ly=-1,ry=-1;
    {
        auto get = [&](int mx){
            int l=X,r=mx,p=mx+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(query(mid,Y)) l=mid+1;
                else p=mid,r=mid-1;
            }
            return p-1;
        };
        rx=get(N);
        int k=(X+rx)/2;
        if(query(k,Y)){
            k=(X+k)/2;
            if(!query(k,Y)) rx=get(k);
        }
        else rx=get(k);
    }
    {
        auto get = [&](int mx){
            int l=Y,r=mx,p=mx+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(query(X,mid)) l=mid+1;
                else p=mid,r=mid-1;
            }
            return p-1;
        };
        ry=get(N);
        int k=(Y+ry)/2;
        if(query(X,k)){
            k=(Y+k)/2;
            if(!query(X,k)) ry=get(k);
        }
        else ry=get(k);
    }
    {
        auto get = [&](int mn){
            int l=mn,r=X,p=mn-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(query(mid,Y)) r=mid-1;
                else p=mid,l=mid+1;
            }
            return p+1;
        };
        lx=get(1);
        int k=(X+lx)/2;
        if(query(k,Y)){
            k=(X+k)/2;
            if(!query(k,Y)) lx=get(k);
        }
        else lx=get(k);
    }
    ly=ry-(rx-lx);
    int M=(rx-lx+1);
    int mx=(lx+rx)/2,my=(ly+ry)/2;

    int ax=0,ay=0,bx=0,by=0;
    for(int i=1;i<=2;i++){
        if(query(mx+2*M*i,my)) ax=i;
        if(query(mx,my+2*M*i)) ay=i;
        if(query(mx-2*M*i,my)) bx=i;
        if(query(mx,my-2*M*i)) by=i;
    }
    if(ax+bx==1){
        if(ax) mx+=M;
        else mx-=M;
    }
    else{
        if(ax==2) mx+=2*M;
        else if(bx==2) mx-=2*M;
    }
    if(ay+by==1){
        if(ay) my+=M;
        else my-=M;
    }
    else{
        if(ay==2) my+=2*M;
        else if(by==2) my-=2*M;
    }
    cout << "solution " << mx << ' ' << my << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

