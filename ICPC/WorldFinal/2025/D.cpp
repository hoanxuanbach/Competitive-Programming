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

int dx[]={-1,0,1,0},
    dy[]={0,1,0,-1};

void solve(){
    int n,m;cin >> n >> m;
    int X=0,Y=0;
    vector<vector<char>> C(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> C[i][j];
            if(C[i][j]=='S') X=i,Y=j,C[i][j]='.';
        }
    }
    vector<int> F(256);
    F['N']=0;F['E']=1;F['S']=2;F['W']=3;

    string S;cin >> S;
    int k=(int)S.length();
    int cnt=0,pos=0;
    while(pos<k){
        vector<int> ord={0,1,2,3};

        pair<int,vector<int>> P={-1,ord};
        do{
            int x=X,y=Y,end=-1;
            for(int i=pos;i<k;i++){
                for(int t:ord){
                    int xt=x+dx[t],yt=y+dy[t];
                    if(xt<0 || yt<0 || xt>=n || yt>=m || C[xt][yt]=='#') continue;
                    if(t!=F[S[i]]) end=i;
                    break;
                }
                if(end!=-1) break;
                int t=F[S[i]];
                x+=dx[t];y+=dy[t];
            }
            if(end==-1) end=k;
            P=max(P,{end,ord});
        }while(next_permutation(ord.begin(),ord.end()));

        cnt++;
        while(pos<P.first){
            int t=F[S[pos++]];
            X+=dx[t];Y+=dy[t];
        }
    }
    cout << cnt-1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
