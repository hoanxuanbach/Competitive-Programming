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
const int inf=1e9;
const int mod=1e9+7;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
int power_mod(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int power_max(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=min(inf,res*a);
        a=min(a*a,inf);n>>=1;
    }
    return res;
}
const int base=101;

int n,m,a[maxn],d[maxn];
bool check,lt[maxn],rt[maxn];
int cl[maxn],cr[maxn];

vector<pii> Min;

bool get_Min(vector<pii> cur){
    int num=0;
    for(int i=0;i<(int)cur.size();i++) num+=cur[i].fi;
    int Min_num=0;
    for(int i=0;i<(int)Min.size();i++) Min_num+=Min[i].fi;
    if(num<Min_num) return true;
    else if(num>Min_num) return false;

    int pcur=(int)cur.size()-1,ccur=cur.back().fi;
    int pmin=(int)Min.size()-1,cmin=Min.back().fi;
    while(pcur>=0 && pmin>=0){
        if(cur[pcur].se>Min[pmin].se) return false;
        if(cur[pcur].se<Min[pmin].se) return true;
        int k=min(ccur,cmin);
        ccur-=k;cmin-=k;
        if(ccur==0){
            pcur--;
            if(pcur<0) ccur=0;
            else ccur=cur[pcur].fi;
        }
        if(cmin==0){
            pmin--;
            if(pmin<0) cmin=0;
            else cmin=Min[pmin].fi;
        }
    }
    return false;
}

void get_ans(int k,int sum,int p){
    //cout << k << ' ' << sum << ' ' << p << '\n';
    int d=(n-p)/power_max(m,k);
    if(sum==0) sum=m;
    int a=0,b=0;
    if(sum+d<m) a=0,b=sum;
    else a=sum-(m-d-1),b=m-d-1;
    //cout << a << ' ' << b << ' ' << d << '\n';

    vector<pii> cur;
    if(k) cur.push_back({k,0});
    cur.push_back({1,b});
    cur.push_back({1,a});

    while(!cur.empty() && cur.back().se==0) cur.pop_back();

    int del=p-1,carry=0;
    vector<pii> nw;
    for(int i=0;i<(int)cur.size();i++){
        int cnt=cur[i].fi,num=cur[i].se;
        while(del && cnt){
            int x=del%m;del/=m;cnt--;
            int cc=num-x-carry;
            carry=0;
            if(cc<0) cc+=m,carry=1;
            nw.push_back({1,cc});
        }
        if(cnt && carry){
            if(num==0){
                nw.push_back({cnt,m-1});
                cnt=0;carry=1;
            }
            else{
                nw.push_back({1,num-1});
                cnt--;carry=0;
            }
        }
        if(cnt) nw.push_back({cnt,num});
    }
    cur=nw;
    while(!cur.empty() && cur.back().se==0) cur.pop_back();
    if(!check || get_Min(cur)) Min=cur;
    check=true;
}

bool check0(){
    int d=0;
    for(int i=1;i<=n;i++){
        int num=0,cur=d;
        while(cur) num+=cur%m,cur/=m;
        if(num%m!=a[i]) return false;
        d++;
    }
    return true;
}

void solve(){
    cin >> n >> m;
    check=false;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        d[i]=(a[i]-a[i-1]+m)%m;
        //cout << d[i] << ' ';
    }
    //cout << '\n';
    if(m==1){
        cout << 0 << '\n';
        return;
    }
    if(n==1){
        cout << a[1] << '\n';
        return;
    }
    if(check0()){
        cout << 0 << '\n';
        return;
    }
    for(int i=0;i<=n+1;i++) lt[i]=rt[i]=true;
    for(int t=1,cur=1;cur<=n;t++,cur*=m){
        for(int i=2;i<=n;i++){
            cl[i]=cr[i]=0;
            if(lt[i] && (i+cur-1>n || d[i+cur-1]==t%m)) cl[i]=1;
            if(rt[i] && (i-cur+1<2 || d[i-cur+1]==t%m)) cr[i]=1;
        }
        for(int i=n;i>=2;i--){
            if(cl[i] && i+cur<=n) cl[i]+=cl[i+cur];
        }
        for(int i=2;i<=n;i++){
            if(cr[i] && i-cur>=2) cr[i]+=cr[i-cur];
        }
        for(int i=2;i<=n;i++){
            int d=min(m-1,(n-i+1)/cur);
            if(cl[i]>=d && lt[i+d*cur]) lt[i]=true;
            else lt[i]=false;
        }
        for(int i=n;i>=2;i--){
            int d=min(m-1,(i-1)/cur);
            if(cr[i]>=d && rt[i-d*cur]) rt[i]=true;
            else rt[i]=false;
        }
    }

    for(int i=1;i<=n;i++){
        bool tl=(i-1<2 || rt[i-1]);
        bool tr=(i+1>n || lt[i+1]);
        if(!tl || !tr) continue;

        int dl=0,dr=0;
        int cur=m-1;
        while(cur<=n-i) cur*=m,dr++;
        cur=1;
        while(cur<i) cur*=m,dl++;

        int k,md=max(dl,dr);
        if(i==1) k=md;
        else{
            d[i]=(d[i]+m-1)%m;
            k=(md/m)*m+d[i];
            if(k<md) k+=m;
        }
        get_ans(k,a[i],i);
    }
    if(!check) cout << -1 << '\n';
    else{
        int ans=0,cur=1;
        for(int i=0;i<(int)Min.size();i++){
            int mul=(power_mod(m,Min[i].fi)+mod-1)*power_mod(m-1,mod-2)%mod;
            ans=(ans+cur*mul%mod*Min[i].se%mod)%mod;
            cur=cur*power_mod(m,Min[i].fi)%mod;
        }
        cout << ans << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
