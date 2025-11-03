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
    int n,m,k;cin >> n >> m >> k;
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];
    vector<int> fa(n),fb(m);
    iota(fa.begin(),fa.end(),0);
    iota(fb.begin(),fb.end(),0);
    sort(fa.begin(),fa.end(),[&](int x,int y){
        return a[x]<a[y];
    });
    sort(fb.begin(),fb.end(),[&](int x,int y){
        return b[x]<b[y];
    });

    auto check = [&](int x){
        int i=n-1,j=m-1,cur=x,t=0;

        bool ok=true;cur-=k;
        while(i>=0 || j>=0){
            if(!t){
                if(i>=0 && a[fa[i]]>cur){
                    ok=false;
                    break;
                }
                i--;
            }
            if(t){
                if(j>=0 && b[fb[j]]>cur){
                    ok=false;
                    break;
                }
                j--;
            }
            cur-=k;t^=1;
        }
        if(ok) return 0;

        cur=x,t=1;
        ok=true;cur-=k;
        i=n-1;j=m-1;
        while(i>=0 || j>=0){
            if(!t){
                if(i>=0 && a[fa[i]]>cur){
                    ok=false;
                    break;
                }
                i--;
            }
            if(t){
                if(j>=0 && b[fb[j]]>cur){
                    ok=false;
                    break;
                }
                j--;
            }
            cur-=k;t^=1;
        }
        if(ok) return 1;
        else return -1;
    };

    int mx=max(a[fa[n-1]],b[fb[m-1]]);
    int l=mx+k,r=mx+3*(n+m)*k,T=r+1,dir=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        int val=check(mid);
        if(val!=-1) T=mid,dir=val,r=mid-1;
        else l=mid+1; 
    }

    vector<array<int,3>> res;

    cout << T << '\n';
    int cur=T-k,t=dir;
    int i=n-1,j=m-1;
    while(i>=0 || j>=0){
        if(!t){
            if(i>=0) res.push_back({cur,0,fa[i]});
            i--;
        }
        if(t){
            if(j>=0) res.push_back({cur,1,fb[j]});
            j--;
        }
        cur-=k;t^=1;
    }
    sort(res.begin(),res.end());
    for(auto [x,y,z]:res) cout << x << ' ' << y << ' ' << z+1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
