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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

string del(string s,int x){
    int carry=0;
    string res;
    for(int i=0;i<(int)s.length();i++){
        int d=s[i]-'0'-carry-x%10;
        x/=10;carry=0;
        if(d<0) d+=10,carry=1;
        res+=char('0'+d);
    }
    return res;
}

void solve(){
    int n,m;cin >> n >> m;
    int add=max(0,5-m);
    vector<vector<vector<bool>>> lt(n+1,vector<vector<bool>>(m+add+1,vector<bool>(10,false)));
    vector<vector<vector<bool>>> rt(n+1,vector<vector<bool>>(m+add+1,vector<bool>(10,false)));
    vector<vector<char>> c(n+1,vector<char>(m+add+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> c[i][m-j+1];
        for(int j=m+1;j<=m+add;j++) c[i][j]='*';
    }
    m+=add;
    for(int i=1;i<=n;i++){
        if(c[i][1]=='*'){
            for(int k=0;k<10;k++) lt[i][1][k]=rt[i][1][k]=true;
        }
        else lt[i][1][c[i][1]-'0']=rt[i][1][c[i][1]-'0']=true;
    }
    vector<vector<int>> cnt(n+2,vector<int>(10,0));
    vector<int> total(n+2,0);
    int p10=1;
    for(int j=2;j<=m;j++){
        for(int i=1;i<=n;i++){
            total[i]=0;
            for(int k=0;k<10;k++) cnt[i][k]=0;
        }
        for(int i=1;i<=n;i++){
            if(c[i][j]!='*'){
                total[i]++;
                cnt[i][c[i][j]-'0']++;
            }
            total[i]+=total[i-1];
            for(int k=0;k<10;k++){
                cnt[i][k]+=cnt[i-1][k];
                lt[i][j][k]=((total[i]-total[max(i-p10*10,0)])==(cnt[i][k]-cnt[max(i-p10*10,0)][k]));
                for(int d=9;d>=0;d--) if(i-(9-d)*p10>=1) lt[i][j][k]=lt[i][j][k]&&lt[i-(9-d)*p10][j-1][d];
            }
        }
        for(int i=1;i<=n;i++){
            total[i]=0;
            for(int k=0;k<10;k++) cnt[i][k]=0;
        }
        for(int i=n;i>=1;i--){
            if(c[i][j]!='*'){
                total[i]++;
                cnt[i][c[i][j]-'0']++;
            }
            total[i]+=total[i+1];
            for(int k=0;k<10;k++){
                cnt[i][k]+=cnt[i+1][k];
                rt[i][j][k]=(total[i]-total[min(i+p10*10,n+1)])==(cnt[i][k]-cnt[min(i+p10*10,n+1)][k]);
                for(int d=0;d<=9;d++) if(i+p10*d<=n) rt[i][j][k]=rt[i][j][k]&&rt[i+p10*d][j-1][d];
            }
        }
        p10=min(p10*10,n+1);
    }
    int Min=1;
    vector<int> num(m+1,0);
    for(int j=1;j<=m;j++){
        num[j]=-1;
        for(int i=1;i<=n;i++){
            if(c[i][j]=='*') continue;
            if(num[j]==-1) num[j]=c[i][j]-'0';
            else if(num[j]!=c[i][j]-'0') num[j]=-2;
        }
        if(num[j]==-2) Min=j;
        if(num[j]==-1) num[j]=0;
    }
    p10=1;
    int ti=-1,tj=-1,tk=-1;
    for(int j=1;j<Min;j++) p10=min(p10*10,n+1);
    for(int j=Min;j<=m;j++){
        for(int i=1;i<=n;i++){
            for(int k=0;k<10;k++){
                if(k==0 && j!=m) continue;
                int p=(k+9)%10;
                bool check=true;
                if(i-1) check&=lt[i-1][j][p];
                int cc=i;
                for(int d=k;d<10;d++){
                    if(cc>n) break;
                    check&=rt[cc][j][d];
                    cc+=p10;
                }
                if(cc<=n) continue;
                if(check) ti=i,tj=j,tk=k;
            }
        }
        p10=min(p10*10,n+1);
    }
    string res;
    for(int j=1;j<tj;j++) res+='0';
    res+=char(tk+'0');
    for(int j=tj+1;j<=m;j++) res+=char('0'+num[j]);
    res=del(res,ti-1);
    for(int i=1;i<=add;i++) res.pop_back();
    reverse(res.begin(),res.end());
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
