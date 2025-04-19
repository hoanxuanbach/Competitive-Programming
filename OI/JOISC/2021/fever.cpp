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
const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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

int dx[]={2,1,0,-1,-2,-1,0,1},
    dy[]={0,1,2,1,0,-1,-2,-1};

vector<int> c[8][3];
vector<pii> edge[maxn][4];
int dt[maxn][4];

void solve(){
    int n;cin >> n;
    vector<pii> p(n+1);
    for(int i=1;i<=n;i++){
        cin >> p[i].fi >> p[i].se;
        if(i>=2){
            p[i].fi-=p[1].fi,p[i].se-=p[1].se;
            p[i].fi<<=1;p[i].se<<=1;
        }
    }
    p[1]={0,0};
    //0:right 2:up 4:left 6:down
    //1:right-up 3:left-up 5:left-down 7:right-down
    auto cal = [&](){
        auto dist = [&](int i,int j){
            return abs(p[i].fi-p[j].fi)+abs(p[i].se-p[j].se);
        };

        auto get = [&](int i,int t){
            return p[i].fi*dx[t]+p[i].se*dy[t];
        };

        vector<int> dir(n+1,0);
        for(int i=1;i<=n;i++){
            int X=p[i].fi,Y=p[i].se;
            if(X<=-Y && Y>=X) dir[i]=0;
            else if(X<=-Y && Y<X) dir[i]=2;
            else if(X>-Y && Y<X) dir[i]=4;
            else if(X>-Y && Y>=X) dir[i]=6;
            //cout << p[i].fi << ' ' << p[i].se << ' ' << dir[i] << '\n';
        }
        //cout << '\n';
        for(int i=0;i<8;i++) for(int t=0;t<3;t++) c[i][t].clear();
        for(int i=1;i<=n;i++) for(int t=0;t<4;t++) edge[i][t].clear();
        memset(dt,-1,sizeof(dt));

        for(int i=1;i<=n;i++){
            for(int t=0;t<3;t++) c[(dir[i]+2*(t+1))%8][t].push_back(i);
        }

        for(int i=0;i<8;i++){
            for(int t=0;t<3;t++){
                int xt=(i-t+7)%8,yt=(i-t+9)%8;

                sort(c[i][t].begin(),c[i][t].end(),[&get,&xt,&yt](int a,int b){
                    return mpp(get(a,xt),get(a,yt))<mpp(get(b,xt),get(b,yt));
                });
                for(int j=0;j+1<(int)c[i][t].size();j++){
                    int a=c[i][t][j],b=c[i][t][j+1];
                    if(get(a,xt)==get(b,xt)) edge[a][t].push_back({b,dist(a,b)/2});
                }
            }
        }
        priority_queue<piii,vector<piii>,greater<piii>> pq;
        pq.push({0,{1,3}});

        int cnt=0;
        vector<int> check(n+1,0);

        while(!pq.empty()){
            auto [d,pr]=pq.top();pq.pop();
            auto [u,k]=pr;
            //cout << d << ' ' << u << ' ' << k << '\n';
            if(dt[u][k]!=-1) continue;
            dt[u][k]=d;
            if(!check[u]) check[u]=1,cnt++;

            for(auto [v,w]:edge[u][k]) pq.push({d+w,{v,k}});

            int i=dir[u];
            for(int t=0;t<3;t++){
                int xt=(i-t+7)%8,yt=(i-t+9)%8;
                p[0]={p[u].fi+d*dx[yt],p[u].se+d*dy[yt]};
                //cout << p[0].fi << ' ' << p[0].se << '\n';
                auto it=lower_bound(c[i][t].begin(),c[i][t].end(),0,[get,xt,yt](int a,int b){
                    pii aa={get(a,xt),get(a,yt)};
                    pii bb={get(b,xt),get(b,yt)};
                    return aa==bb?a<b:aa<bb;
                });
                //if(it!=c[i][t].end()) cout << i << ' ' << t << ' ' << u << ' ' << *it << '\n';
                if(it==c[i][t].end() || get(0,xt)!=get(*it,xt)) continue;
                pq.push({dist(u,*it)/2,{*it,t}});
            }
        }
        //cout << cnt << '\n';
        return cnt;
    };

    int ans=0;
    for(int t=0;t<4;t++){
        ans=max(ans,cal());
        for(int i=1;i<=n;i++) swap(p[i].fi,p[i].se),p[i].se=-p[i].se;
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
