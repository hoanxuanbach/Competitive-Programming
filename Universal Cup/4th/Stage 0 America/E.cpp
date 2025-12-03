#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,k;cin >> n >> k;
    vector<int> a(n),d(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++){
        int x;cin >> x;
        if(x<=a[i]){
            d[i]=(x-a[i])*(k+1);
            a[i]-=x;
        }
        else a[i]=(a[i]-x)*k;
    }
    int res=0;
    vector<int> la(n),ld(n),ra(n),rd(n);
    function<void(int,int)> dnc = [&](int l,int r){
        if(l==r){
            res+=((a[l]+d[l])>=0);
            return;
        }
        int m=(l+r)>>1;
        dnc(l,m);dnc(m+1,r);

        la[m]=a[m];ld[m]=d[m];
        ra[m+1]=a[m+1];rd[m+1]=d[m+1];
        for(int i=m-1;i>=l;i--) la[i]=la[i+1]+a[i],ld[i]=min(ld[i+1],d[i]);
        for(int i=m+2;i<=r;i++) ra[i]=ra[i-1]+a[i],rd[i]=min(rd[i-1],d[i]);

        int ls=m-l+1,rs=r-m;
        vector<pii> fl(ls),fr(rs);
        for(int i=l;i<=m;i++) fl[i-l]={ld[i],la[i]};
        for(int i=m+1;i<=r;i++) fr[i-m-1]={rd[i],ra[i]};

        sort(fl.begin(),fl.end());
        sort(fr.begin(),fr.end());
        
        vector<int> com;
        for(int i=0;i<ls;i++) com.push_back(-fl[i].first-fl[i].second);
        for(int i=0;i<rs;i++) com.push_back(-fr[i].first-fr[i].second);
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        int sz=(int)com.size();
        
        vector<int> bit(sz+1,0);
        auto update = [&](int x){
            for(int i=x;i<=sz;i+=(i&(-i))) bit[i]++;
        };
        auto query = [&](int x){
            int cnt=0;
            for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
            return cnt;
        };


        int pos=0;
        for(int i=0;i<rs;i++){
            while(pos<ls && fl[pos].first<=fr[i].first){
                int id=upper_bound(com.begin(),com.end(),-fl[pos].first-fl[pos].second)-com.begin();
                update(id);pos++;
            }
            int id=upper_bound(com.begin(),com.end(),fr[i].second)-com.begin();
            res+=query(id);
        }

        bit.assign(sz+1,0);
        pos=0;

        for(int i=0;i<ls;i++){
            while(pos<rs && fr[pos].first<fl[i].first){
                int id=upper_bound(com.begin(),com.end(),-fr[pos].first-fr[pos].second)-com.begin();
                update(id);pos++;
            }
            int id=upper_bound(com.begin(),com.end(),fl[i].second)-com.begin();
            res+=query(id);
        }
    };
    dnc(0,n-1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
