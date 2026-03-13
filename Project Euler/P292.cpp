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

const int T = 250;
const int M = 500;

int f[2][M][M][T];
bool g[M][M];


void solve(){
    int N;cin >> N;

    vector<pii> P;
    vector<array<int,3>> S;
    for(int x=-N;x<=N;x++) for(int y=-N;y<=N;y++){
        int d=x*x+y*y;
        if(d<=N*N/4) g[T+x][T+y]=1,P.push_back({T+x,T+y});
        int s=sqrtl(d);
        if(0<s && s<=N && s*s==d) S.push_back({x,y,s});
    }
    sort(S.begin(),S.end(),[&](array<int,3> a,array<int,3> b){
        return atan2(a[1],a[0])<atan2(b[1],b[0]);
    });
    //for(auto [x,y,d]:S) cout << x << ' ' << y << ' ' << d << '\n';

    f[0][T][T][0]=1;
    
    int K=(int)S.size(),t=0;
    for(int l=0,r=0;l<K;l=r){
        r=l;
        while(r<K && S[l][0]*S[r][1]==S[r][0]*S[l][1]) r++;
        //cout << '*' << l << ' ' << r << '\n';
        for(auto [x,y]:P) for(int d=0;d<=N;d++) f[t^1][x][y][d]=f[t][x][y][d];
        for(int i=l;i<r;i++){
            auto [dx,dy,dd]=S[i];
            for(auto [x,y]:P) for(int d=0;d<=N-dd;d++) if(g[x+dx][y+dy]) f[t^1][x+dx][y+dy][d+dd]+=f[t][x][y][d];
        }
        t^=1;
    }
    int res=0;
    for(int d=1;d<=N;d++){
        res+=f[t][T][T][d];
        //cout << f[t][T][T][d] << '\n';
    }
    //cout << res << '\n';

    int cnt=0;
    for(auto [x,y,d]:S) if(2*d<=N) cnt++;
    res-=cnt/2;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
