#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int maxk = 1e6+10;

int n,K;
int cnt[maxn][maxn];
int A[3][maxn],B[3][maxn];
int da[maxn][maxn],db[maxn][maxn],dt[maxn][maxn];
vector<pair<int,int>> p[3][maxn];

vector<int> cand[3][2];
vector<array<int,2>> f[3];
int num[3][maxk];

int inv(int x){
    int d=K-2,res=1;
    while(d){
        if(d&1) res=1LL*res*x%K;
        x=1LL*x*x%K;d>>=1;
    }
    return res;
}

void solve(){
    cin >> n >> K;
    for(int i=0;i<=2;i++) for(int j=0;j<=2*n;j++) p[i][j].clear();
    for(int i=0;i<=2*n;i++){
        int l=max(i-n,0),sz=(i<=n?n+i+1:3*n-i+1);
        for(int j=l;j<l+sz;j++){
            cin >> db[i][j];
            da[i][j]=cnt[i][j]=0,dt[i][j]=3;
            db[i][j]=(K-db[i][j])%K;
            p[0][i].push_back({i,j});
            p[1][j].push_back({i,j});
            p[2][i-j+n].push_back({i,j});
        }
    }
    memset(A,-1,sizeof(A));
    memset(B,-1,sizeof(B));
    function<void(int,int,int,int)> add = [&](int x,int y,int a,int b){
        if(A[x][y]!=-1) return;
        A[x][y]=a,B[x][y]=b;
        for(auto [i,j]:p[x][y]){
            cnt[i][j]++;dt[i][j]^=x;
            da[i][j]=(da[i][j]+K-a)%K;
            db[i][j]=(db[i][j]+K-b)%K;
            if(cnt[i][j]==2){
                int pos=-1;
                if(dt[i][j]==0) pos=i;
                else if(dt[i][j]==1) pos=j;
                else pos=i-j+n;
                add(dt[i][j],pos,da[i][j],db[i][j]);
            }
        }
    };
    add(0,n,0,0);
    add(1,n,0,0);
    add(0,n+1,1,0);

    bool check=true;
    for(int i=0;i<=2*n;i++){
        int l=max(i-n,0),sz=(i<=n?n+i+1:3*n-i+1);
        for(int j=l;j<l+sz;j++) if(db[i][j]) check=false;
    }
    if(!check){
        cout << -1 << '\n';
        return;
    }

    int mx=0;
    array<int,4> best={-1,-1,-1,-1};

    if(K<=2*n){
        for(int x=0;x<K;x++){
            for(int i=0;i<=2;i++){
                for(int j=0;j<=2*n;j++){
                    int d=(x*A[i][j]+B[i][j])%K;
                    num[i][d]++;
                }
            }
            for(int i=0;i<K;i++) for(int j=0;j<K;j++){
                int k=(2*K-i-j)%K;
                int total=num[0][i]+num[1][j]+num[2][k];
                if(total>mx) mx=total,best={i,j,k,x};
            }
            for(int i=0;i<=2;i++) for(int j=0;j<K;j++) num[i][j]=0;
        }
    }
    else{
        for(int t=0;t<=2;t++){
            f[t].clear();
            map<pair<int,int>,int> mp;
            for(int i=0;i<=2*n;i++) for(int j=i+1;j<=2*n;j++){
                int a=(A[t][i]-A[t][j]+K)%K;
                int b=(B[t][j]-B[t][i]+K)%K;
                int x=1LL*b*inv(a)%K;
                int val=(1LL*A[t][i]*x+B[t][i])%K;
                mp[{x,val}]++;
            }
            for(auto [x,val]:mp) f[t].push_back({x.first,x.second});
        }
        while(!f[0].empty() || !f[1].empty() || !f[2].empty()){
            int X=0;
            for(int i=0;i<=2;i++){
                if(!f[i].empty()) X=max(X,f[i].back()[0]);
                for(int j=0;j<=1;j++) cand[i][j].clear();
            }
            for(int i=0;i<=2;i++){
                while(!f[i].empty() && f[i].back()[0]==X) cand[i][1].push_back(f[i].back()[1]),f[i].pop_back();
                for(int j=0;j<=2*n;j++){
                    int val=(1LL*A[i][j]*X+B[i][j])%K;
                    if(++num[i][val]==1) cand[i][0].push_back(val);
                }
            }
            for(int i=0;i<=2;i++) for(int j=0;j<=2;j++){
                if(i==j) continue;
                for(int x:cand[i][1]) for(int y:cand[j][0]){
                    int z=(2*K-x-y)%K,k=3^i^j;
                    int total=num[i][x]+num[j][y]+num[k][z];
                    int nx=(i==0)*x+(j==0)*y+(k==0)*z;
                    int ny=(i==1)*x+(j==1)*y+(k==1)*z;
                    int nz=(i==2)*x+(j==2)*y+(k==2)*z;
                    if(total>mx) mx=total,best={nx,ny,nz,X};
                }
            }
            for(int i=0;i<=2;i++) for(int val:cand[i][0]) num[i][val]=0;
        }
    }
    vector<array<int,3>> res;
    for(int i=0;i<=2;i++){
        for(int j=0;j<=2*n;j++){
            int d=(1LL*best[3]*A[i][j]+B[i][j])%K;
            if(d!=best[i]) res.push_back({i,j,(d+K-best[i])%K});
        }
    }
    cout << (int)res.size() << '\n';
    for(auto [i,j,d]:res){
        if(i==0) cout << j-n << " r " << d << '\n';
        else if(i==1) cout << n-j << " s " << d << '\n';
        else cout << n-j << " q " << d << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}
