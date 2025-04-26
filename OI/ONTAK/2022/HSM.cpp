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
const int mod=1e9+7;
const int maxn=200005;
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

int inv2=(mod+1)/2;
int p2[35],ip2[35],p2n[35],ip2n[35];

void solve(){
    int n;string s;cin >> n >> s;
    reverse(s.begin(),s.end());
    int len=(int)s.length();
    for(int i=0;i<len;i++) if(s[i]=='1'){
        for(int j=0;j<i;j++) s[j]='1';
        s[i]='0';break;
    }
    while(!s.empty() && s.back()=='0') s.pop_back();
    if(s.empty()){
        cout << 0 << '\n';
        return;
    }
    reverse(s.begin(),s.end());
    int pos=(int)s.length()-1,N=n;
    vector<int> d,cnt;
    while(N){
        if(N&1) cnt.push_back(N/2+1);
        d.push_back(N),N/=2;
    }
    for(int i=0;i<(int)d.size();i++){
        p2[i]=power(2,d[i]+1);
        ip2[i]=power(inv2,d[i]+1);
        p2n[i]=power(p2[i],n);
        ip2n[i]=power(ip2[i],n);
    }
    vector<pii> p;
    for(int i=0;i<(int)cnt.size();i++){
        int dd=(cnt[i]-(i==(int)cnt.size()-1?0:cnt[i+1])),cur=cnt[i];
        while(dd && pos>=i){
            for(int j=0;j<=i;j++){
                if(s[pos]=='1') p.push_back({cur,cnt[j]});
                pos--;
            }
            dd--;cur--;
        }
        if(dd && pos>=0){
            int cc=pos;
            for(int j=0;j<=cc;j++){
                if(s[pos]=='1') p.push_back({cur,cnt[j]});
                pos--;
            }
        }
        if(pos<0) break;
    }
    int ans=0;
    for(auto [i,j]:p){
        vector<vector<int>> a(2,vector<int>(2,0));
        a[0][0]=power(inv2,i*n+j);
        a[0][1]=power(inv2,i*n-j);
        a[1][0]=power(2,i*n-j);
        a[1][1]=power(2,i*n+j);
        for(int t=(int)d.size()-1;t>=0;t--){
            int k=d[t];
            if(k<i || k<j) continue;
            if(k%2==1 && j==k/2+1){
                if(i!=k/2+1){
                    a[0][0]=(a[0][0]+power(inv2,j*n+i)+power(inv2,(k-i+1)*n+j)+power(inv2,j*n+(k-i+1)))%mod;
                    a[0][1]=(a[0][1]+power(inv2,j*n-i)+power(inv2,(k-i+1)*n-j)+power(inv2,j*n-(k-i+1)))%mod;
                    a[1][0]=(a[1][0]+power(2,j*n-i)+power(2,(k-i+1)*n-j)+power(2,j*n-(k-i+1)))%mod;
                    a[1][1]=(a[1][1]+power(2,j*n+i)+power(2,(k-i+1)*n+j)+power(2,j*n+(k-i+1)))%mod;
                }
            }
            else{
                vector<vector<int>> na(2,vector<int>(2,0));
                na[0][0]=(a[0][0]+a[0][1]*ip2[t]+a[1][0]*ip2n[t]+a[1][1]*ip2n[t]%mod*ip2[t])%mod;
                na[0][1]=(a[0][1]+a[0][0]*p2[t]+a[1][1]*ip2n[t]+a[1][0]*ip2n[t]%mod*p2[t])%mod;
                na[1][0]=(a[1][0]+a[1][1]*ip2[t]+a[0][0]*p2n[t]+a[0][1]*p2n[t]%mod*ip2[t])%mod;
                na[1][1]=(a[1][1]+a[1][0]*p2[t]+a[0][1]*p2n[t]+a[0][0]*p2n[t]%mod*p2[t])%mod;
                a=na;
            }
        }
        //cout << a[1][1] << '\n';
        ans=(ans+a[0][0])%mod;
    }
    ans=power(2,n*n+n)*ans%mod;
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
