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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=9e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=100005;
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
struct line{
    int a,b,c,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a){
            if(l.b<y.b) l.p=inf;
            else if(l.b>y.b) l.p=-inf;
            else l.p=(l.c<y.c?inf:-inf);
        }
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    line query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l;
    }
};
int n,k,c[maxn];
pii dp[maxn];
struct node{
    int num,sz=0,add=0;
    pii Min,pre={inf,-1};
    cvht cht;
    node(int _num):num(_num){}
    pii query(){
        line l=cht.query(sz+1);
        return {(l.a*(sz+1)+l.b+(sz+1)*(sz+1))/2+add,l.c};
    }
    void update(pii x){
        sz++;cht.add({-2*sz+1,2*x.fi+sz*(sz-1)-2*add,x.se,inf});
        line l=cht.query(sz);
        Min={(l.a*sz+l.b+sz*sz)/2+add,l.c};
    }
    void get(int x){
        Min.fi+=x;
        add+=x;pre.fi+=x;
    }
};
pii check(int x){
    vector<node> v={node(0)};
    v.back().update({0,0});
    for(int i=1;i<=n;i++){
        pii Min={inf,-1};
        /*
        cout << c[i] << '\n';
        for(node d:v){
            cout << d.add << ' ' << d.num << ' ' << d.sz << ' ' << d.Min.fi << ' ' << d.Min.se << ' ' << d.pre.fi << ' ' << d.pre.se << '\n';
        }
        */
        while(!v.empty() && v.back().num>c[i]){
            Min=min(Min,v.back().Min);
            int d=v.back().add;v.pop_back();
            if(!v.empty()) v.back().get(d);
        }
        dp[i]=Min;
        //cout << Min.fi << ' ' << Min.se << '\n';
        if(v.empty() || v.back().num!=c[i]){
            v.push_back(node(c[i]));
            if((int)v.size()>=2) v.back().pre=min(v[(int)v.size()-2].Min,v[(int)v.size()-2].pre);
        }
        else dp[i]=min(dp[i],v.back().query());
        v.back().pre.fi+=v.back().sz;
        if((int)v.size()>=2) v[(int)v.size()-2].get(v.back().sz);
        if(!v.empty()){
            dp[i]=min(dp[i],v.back().pre);
            //cout << v.back().pre.fi << ' ' << v.back().pre.se << '\n';
        }
        dp[i].fi+=x;dp[i].se++;Min=min(Min,dp[i]);
        v.back().update(Min);
        //cout << v.back().pre.fi << ' ' << v.back().pre.se << '\n';
        //cout << Min.fi << ' ' << Min.se << '\n';
        //cout << '*' << dp[i].fi << ' ' << dp[i].se << ' ' << Min.fi << ' ' << Min.se << '\n';
    }
    return dp[n];
}
void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        char x;cin >> x;
        c[i]=c[i-1]+(x=='('?1:-1);
    }
    int l=0,r=1e10,ans=1e10,use=-1,Min=-1;
    while(r>=l){
        int mid=(r+l)>>1;
        pii res=check(mid);
        //cout << mid << ' ' << res.fi << ' ' << res.se << '\n';
        if(res.se<=k){
            use=mid;Min=res.fi;
            r=mid-1;
        }
        else l=mid+1;
    }
    cout << Min-k*use << '\n';
}
signed main(){
    //freopen("NAW.INP","r",stdin);
    //freopen("NAW.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
