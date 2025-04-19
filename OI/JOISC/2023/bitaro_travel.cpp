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
const int inf=2e9;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,q,x[maxn],down[maxn],up[maxn],Maxup[maxn][maxl],Mindown[maxn][maxl],lg2[maxn];
int check_up(int l,int r){
    int p=lg2[r-l+1];
    return max(Maxup[l][p],Maxup[r-(1<<p)+1][p]);
}
int check_down(int l,int r){
    int p=lg2[r-l+1];
    return min(Mindown[l][p],Mindown[r-(1<<p)+1][p]);
}
int cal(int a){
    int r=lower_bound(x+1,x+n+1,a)-x,l=r-1;
    long long ans=0;
    while(true){
        //cout << a << ' ' << l << ' ' << r << '\n';
        if(l==0){ans+=x[n]-a;break;}
        else if(r==n+1){ans+=a-x[1];break;}
        if(x[r]-a<a-x[l]){
            int lt=r,rt=n-1,pos=r;
            while(rt>=lt){
                int mid=(lt+rt)>>1;
                if(check_down(r,mid)>l){pos=mid+1;lt=mid+1;}
                else rt=mid-1;
            }
            ans+=x[pos]-a;
            a=x[pos];r=pos+1;
        }
        else{
            int lt=2,rt=l,pos=l;
            while(rt>=lt){
                int mid=(lt+rt)>>1;
                //cout << '*' << mid << ' ' << l << ' ' << check_up(mid,l) << '\n';
                if(check_up(mid,l)<r){pos=mid-1;rt=mid-1;}
                else lt=mid+1;
            }
            //cout << pos << '\n';
            ans+=a-x[pos];
            a=x[pos];l=pos-1;
        }
    }
    return ans;
}
void buildupdown(){
    for(int i=1;i<n;i++){
        int l=1,r=i;
        while(r>=l){
            int mid=(r+l)>>1;
            if(x[i]-x[mid]<=x[i+1]-x[i]){down[i]=mid;r=mid-1;}
            else l=mid+1;
        }
        Mindown[i][0]=down[i];
    }
    for(int i=2;i<=n;i++){
        int l=i,r=n;
        while(r>=l){
            int mid=(l+r)>>1;
            if(x[mid]-x[i]<x[i]-x[i-1]){up[i]=mid;l=mid+1;}
            else r=mid-1;
        }
        Maxup[i][0]=up[i];
    }
    for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<=18;i++){
        for(int j=1;j<=(n-(1<<i)+1);j++){
            Maxup[j][i]=max(Maxup[j][i-1],Maxup[j+(1<<(i-1))][i-1]);
            Mindown[j][i]=min(Mindown[j][i-1],Mindown[j+(1<<(i-1))][i-1]);
        }
    }
}
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i];
    buildupdown();
    cin >> q;
    for(int i=1;i<=q;i++){
        int a;cin >> a;
        cout << cal(a) << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}