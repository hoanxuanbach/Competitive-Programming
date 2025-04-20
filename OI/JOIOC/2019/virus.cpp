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
const int inf=1e9;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

int mx[25],c[maxn];
int dx[]={-1,1,0,0},
    dy[]={0,0,-1,1};

void solve(){
    int M,R,C;cin >> M >> R >> C;
    string s;cin >> s;s+=s;M*=2;
    for(int i=0;i<M;i++){
        if(s[i]=='N') c[i]=0;
        else if(s[i]=='S') c[i]=1;
        else if(s[i]=='W') c[i]=2;
        else c[i]=3;
    }
    for(int i=0;i<16;i++){
        int cnt=0;
        for(int j=0;j<M;j++){
            if(i>>c[j]&1) cnt++;
            else cnt=0;
            mx[i]=max(mx[i],cnt);
        }
        if(mx[i]==M) mx[i]=inf;
        //cout << i << ' ' << mx[i] << '\n';
    }
    vector<vector<int>> U(R,vector<int>(C,0));
    for(int i=0;i<R;i++) for(int j=0;j<C;j++) cin >> U[i][j];
    vector<int> ord(R*C);
    iota(ord.begin(),ord.end(),0);
    shuffle(ord.begin(),ord.end(),rng);

    vector<vector<bool>> used(R,vector<bool>(C,false));
    auto check = [&](int x,int y){
        if(x<0 || y<0 || x>=R || y>=C || used[x][y] || !U[x][y]) return false;
        int mask=0;
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<0 || yt<0 || xt>=R || yt>=C || !used[xt][yt]) continue;
            mask|=(1<<t);
        }
        return mx[mask]>=U[x][y];
    };

    int res=inf,cnt=0;
    for(int i:ord){
        if(!U[i/C][i%C]) continue;
        queue<int> q;
        vector<int> cc;
        q.push(i);
        cc.push_back(i);
        used[i/C][i%C]=true;
        bool flag=true;
        while(!q.empty()){
            if((int)cc.size()>res){flag=false;break;}
            int x=q.front()/C,y=q.front()%C;q.pop();
            for(int t=0;t<4;t++){
                int xt=x+dx[t],yt=y+dy[t];
                if(!check(xt,yt)) continue;
                if(xt*C+yt<i){flag=false;break;}
                q.push(xt*C+yt);
                cc.push_back(xt*C+yt);
                used[xt][yt]=true;
            }
            if(!flag) break;
        }
        for(int x:cc) used[x/C][x%C]=false;
        if(!flag) continue;
        if((int)cc.size()<res) res=(int)cc.size(),cnt=0;
        if((int)cc.size()==res) cnt++;
    }
    cout << res << '\n' << res*cnt << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
