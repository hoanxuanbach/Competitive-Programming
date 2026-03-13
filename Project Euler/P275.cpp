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

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

void solve(){
    int n;cin >> n;

    int res=0;
    {//all
        vector<vector<bool>> f(4*n,vector<bool>(n));
        vector<pii> T(10*n);
        T[0]={0,0};f[n][0]=1;
        function<void(int,int,int,int,int,int)> dfs = [&](int m,int L,int R,int A,int B,int D){
            //cout << "dfs " << m << ' ' << L << ' ' << R << ' ' << A << ' ' << B << ' ' << D << '\n';
            if(D+(B+n-m)*(n-m)<0) return;
            if(D+(A-n+m)*(n-m)>0) return;
            
            if(m==n){
                if(D==0){
                    res++;
                    if(res%10000==0) cout << res << endl;
                }
                return;
            }
    
            for(int i=L;i<R;i++){
                auto [X,Y]=T[i];
                int nD=D+X,nR=R;
                for(int t=0;t<4;t++){
                    int x=X+dx[t],y=Y+dy[t];
                    if(y<0 || f[x+n][y]) continue;
                    f[x+n][y]=1;
                    T[nR++]={x,y};
                }
                int nA=min(A,X);
                int nB=max(B,X);
                //cout << "add " << X << ' ' << Y << '\n';
                dfs(m+1,i+1,nR,nA,nB,nD);
                for(int t=R;t<nR;t++) f[T[t].first+n][T[t].second]=0;
                //cout << "del " << X << ' ' << Y << '\n';
            }
        };
        dfs(0,0,1,0,0,0);
    }
    //cout << res << '\n';
    {//symmetric
        vector<vector<bool>> f(2*n+2,vector<bool>(n));
        vector<pii> T(10*n);
        T[0]={0,0};f[n][0]=1;
        function<void(int,int,int)> dfs = [&](int m,int L,int R){
            if(m>n) return;
            if(m==n){
                res++;
                if(res%10000==0) cout << res << endl;
                return;
            }
            for(int i=L;i<R;i++){
                auto [X,Y]=T[i];
                int nR=R;
                for(int t=0;t<4;t++){
                    int x=X+dx[t],y=Y+dy[t];
                    if(y<0 || x<0 || f[x+n][y]) continue;
                    f[x+n][y]=1;
                    T[nR++]={x,y};
                }
                dfs(m+1+(X>0),i+1,nR);
                for(int t=R;t<nR;t++) f[T[t].first+n][T[t].second]=0;
            }
        };  
        dfs(0,0,1);
    }
    //cout << res << '\n';
    cout << res/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
