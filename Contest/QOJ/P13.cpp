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
 
const int maxn = 5e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
struct line{
    int a,b;
    ld p;
    line(int _a,int _b,ld _p):a(_a),b(_b),p(_p){}
    bool operator<(line o){return a<o.a;}
    bool operator<(ld o){return p<o;}
};

vector<line> g[maxn];
const ld inf = 1/0.000000000000000001;
struct cvht{
    vector<line> X;
    
    ld div(int a,int b){
        return (ld)a/b;
    }
    void isect(line &y,line &l){
        if(y.a==l.a) y.p=(y.b>=l.b)?inf:-inf;
        else y.p=div(y.b-l.b,l.a-y.a);
        return;
    }
    void add_line(line l,int id){
        if(!X.empty()) isect(X.back(),l);
        while((int)X.size()>=2 && X[(int)X.size()-2].p>=X.back().p){
            if(id) g[id].push_back(X.back());
            X.pop_back();isect(X.back(),l);
        }
        X.push_back(l);
    }
    void del_line(int id){
        X.pop_back();
        X.back().p=inf;
        while(!g[id].empty()){
            line L=g[id].back();
            g[id].pop_back();
            L.p=inf;
            add_line(L,0);
        }
    }
    int query(int x,int y){
        auto l=*lower_bound(X.begin(),X.end(),(ld)x/y);
        return l.a*x+l.b*y;
    }
}cht;

void solve(){
    int n;cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=n;i>1;i--) cht.add_line(line(-i,a[i],inf),i);
    
    vector<int> f(n+1);f[1]=f[n]=1;
    for(int i=1,x=2;x<n;x++){
        cht.del_line(x);
        int val=cht.query(a[x]-a[i],x-i);
        if((val-a[i]*x+a[x]*i)<0) f[x]=1,i=x;
    }

    for(int i=1;i<=n;i++) a[i]%=mod;
    int res=a[1],l=1;
    for(int r=2;r<=n;r++) if(f[r]){
        res=(res+a[r])%mod;
        for(int i=l+1;i<r;i++){
            int X=(a[l]*(r-i)+a[r]*(i-l))%mod;
            X=X*power(r-l,mod-2)%mod;
            res=(res+X)%mod;
        }
        l=r;
    } 
    res=res*power(n,mod-2)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
