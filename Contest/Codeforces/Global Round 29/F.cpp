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

const int B = 330;
void solve(){
    int n,q;cin >> n >> q;
    vector<int> p(n+1),s(n+1);
    for(int i=1;i<=n;i++) cin >> p[i];
    for(int i=1;i<=n;i++) cin >> s[i];

    vector<int> a(n+1);
    for(int i=1;i<=n;i++) a[p[i]]=s[i];

    vector<int> L(B),R(B);
    
    vector<int> mx(B),pos(n+1),total(n+1),nxt(n+1),pre(n+1);
    auto build = [&](int id){
        mx[id]=0;
        for(int i=L[id];i<=R[id];i++) mx[id]=max(mx[id],a[i]);
        for(int i=L[id];i<=R[id];i++){
            pre[i]=a[i];
            if(i>L[id]) pre[i]=max(pre[i],pre[i-1]);
        }
        //cout << "build " << id << '\n';
        for(int i=R[id];i>=L[id];i--){
            pos[i]=total[i]=nxt[i]=-1;
            if(pre[i]<=i) pos[i]=i;
            else if(i<R[id]) pos[i]=pos[i+1];
            if(pos[i]==i){
                total[i]=0;nxt[i]=i;
                if(i<R[id] && pos[i+1]!=-1){
                    int j=pos[i+1];
                    nxt[i]=nxt[j];
                    total[i]=total[j]+(j-i)*(j-i-1)/2;
                }
            }
            //cout << i << ' ' << a[i] << ' ' << pos[i] << ' ' << nxt[i] << ' ' << total[i] << '\n';
        }
    };
    for(int i=0;i<=n/B;i++){
        L[i]=max(1LL,i*B);
        R[i]=min((i+1)*B-1,n);
        build(i);
    }

    auto update = [&](int x,int y){
        swap(a[x],a[y]);
        build(x/B);build(y/B);

        int cnt=0,l=0,k=0;
        for(int i=0;i<=n/B;i++){
            k=max(k,a[L[i]]);
            if(k<=R[i]){  
                int p=pos[k];
                if(p!=-1){
                    cnt+=(p-l)*(p-l-1)/2;
                    cnt+=total[p];
                    l=nxt[p];
                }
            }
            k=max(k,mx[i]);
        }
        cout << cnt+n*(n+1)/2 << '\n';
    };

    for(int i=0;i<q;i++){
        int t,x,y;cin >> t >> x >> y;
        if(t==1){
            swap(p[x],p[y]);
            update(p[x],p[y]);
        }
        else{
            swap(s[x],s[y]);
            update(p[x],p[y]);
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
