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
#define ld long double 
const ld PI = acosl(-1);
const ld eps = 1e-10;
void solve(){
    int N;cin >> N;
    vector<pii> P(N);
    for(int i=0;i<N;i++) cin >> P[i].first >> P[i].second;

    int res=3;
    vector<pii> f(N);
    vector<ld> g(N);

    vector<int> dist(N);
    vector<vector<bool>> T(N,vector<bool>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(j==i) continue;
            int A=P[j].first-P[i].first,B=P[j].second-P[i].second;
            dist[j]=A*A+B*B;
            int G=abs(__gcd(A,B));A/=G;B/=G;
            f[j]={A,B};
            g[j]=atan2l(B,A);
        }
        for(int j=0;j<N;j++) if(i!=j) for(int k=0;k<N;k++) if(j!=k && k!=i && f[j]==f[k] && dist[j]<dist[k]) T[i][j]=true; 

        for(int j=0;j<N;j++) if(j!=i){
            int cnt=0;
            auto [A,B]=f[j];

            pair<ld,int> up={-1,-1},down={-1,-1};
            for(int k=0;k<N;k++) if(k!=i && k!=j){
                auto [a,b]=f[k];
                ld angle=abs(g[j]-g[k]);
                angle=min(angle,2*PI-angle);
                if(a==A && b==B) cnt++;
                else if(a*B-b*A<0) up=max(up,{angle,k});
                else down=max(down,{angle,k});
            }
            res=max(res,min(cnt+3,N));
            if(up.second!=-1 && down.second!=-1){
                int x=up.second,y=down.second;
                int A=P[x].first-P[i].first,B=P[x].second-P[i].second;
                int C=P[y].first-P[i].first,D=P[y].second-P[i].second;
                if(A*D-B*C>=0) res=max(res,min(cnt+4,N));
            }
        }
    }
    
    if(res==5){
        for(int i=0;i<N;i++) for(int j=i+1;j<N;j++) for(int k=i+1;k<N;k++) if(j!=k){
            if(T[i][j] && T[j][k] && T[k][i]){
                cout << 6 << '\n';
                return;
            }
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}