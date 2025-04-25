#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+5;
const int inf = 2e9;

int n[2],k;
vector<pair<int,int>> A[2];
int get(int i,int x){
    return upper_bound(A[i].begin(),A[i].end(),make_pair(x,inf))-A[i].begin();
}
bool inside(int i,int j,int x){
    if(j<0) return false;
    else return A[i][j].first<=x && x<A[i][j].second;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n[0] >> n[1] >> k;
    for(int i=0;i<=1;i++){
        for(int j=0;j<n[i];j++){
            int l,r;cin >> l >> r;
            A[i].push_back({l,r});
        }
        sort(A[i].begin(),A[i].end());
    }
    array<array<int,2>,2> dp={array<int,2>{inf,inf},array<int,2>{inf,inf}};
    dp[0][0]=-1;
    for(int t=0;t<=n[0]+n[1];t++){
        array<array<int,2>,2> ndp={array<int,2>{inf,inf},array<int,2>{inf,inf}};
        //cout << '*' << t << '\n';
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
            int x=dp[i][j];
            //cout << "dp " << i << ' ' << j << ' ' << x << '\n';
            if(x==inf) continue;
            auto [pi,pj]=make_pair(get(i,x),get(i^1,x));
            //cout << pi << ' ' << pj << '\n';
            if(!j && inside(i^1,pj-1,x)) pj--;
            if(pi<n[i]){
                int nx=A[i][pi].first;
                int npj=get(i^1,nx);
                if(inside(i^1,npj-1,nx)) npj--;
                int nj=(npj<pj);
                //cout << i << ' ' << nj << ' ' << nx << '\n';
                ndp[i][nj]=min(ndp[i][nj],nx);
            }
            {
                int nx=max(x,0)+k;
                int npj=get(i^1,nx);
                if(inside(i^1,npj-1,nx)) npj--;
                npj=max(npj,pj);
                if(npj<n[i^1]) nx=max(nx,A[i^1][npj].first);
                else continue;
                int npi=get(i,nx);
                if(inside(i,npi-1,nx)) npi--;
                int nj=(npi<pi);
                //cout << (i^1) << ' ' << nj << ' ' << nx << '\n';
                ndp[i^1][nj]=min(ndp[i^1][nj],nx);
            }
        }
        bool check=false;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) if(ndp[i][j]!=inf) check=true;
        if(!check){
            cout << t << '\n';
            return 0;
        }
        dp=ndp;
    }
}