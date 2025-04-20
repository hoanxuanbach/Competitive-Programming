#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int A[maxn][maxn],a[maxn][maxn],ans[maxn][maxn],num;
int f[maxn][maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    freopen("09","r",stdin);
    freopen("09.out","w",stdout);
    int m,n;cin >> m >> n;
    for(int i=0;i<m*m;i++){int x;cin >> x;}
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> A[i][j];
    vector<pair<int,int>> ord;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) ord.push_back({i,j});

    for(int t=0;t<10;t++){
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) a[i][j]=A[i][j];
        while(true){
            shuffle(ord.begin(),ord.end(),rng);
            for(int i=0;i<n;i++) for(int j=0;j<n;j++) f[i][j]=0;
            int cnt=0;
            for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) for(int k=j+1;k<n;k++) if(a[i][j] && a[i][k] && a[j][k]){
                cnt++;
                f[i][j]++;
                f[i][k]++;
                f[j][k]++;
            }
            if(!cnt) break;
            int x=-1,y=-1,val=0;
            for(auto [i,j]:ord){
                if(f[i][j]>val) val=f[i][j],x=i,y=j;
            }
            a[x][y]=a[y][x]=0;
        }
        int total=0;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) total+=a[i][j];
        total/=2;
        if(total>num){
            num=total;
            for(int i=0;i<n;i++) for(int j=0;j<n;j++) ans[i][j]=a[i][j];
        }
    }
    cout << n << '\n';
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    //cout << num << '\n';
}
/*
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    freopen("09.out","r",stdin);
    int n,m;
    ifstream fin("09");
    fin >> m >> n;
    for(int i=0;i<m*m;i++) fin >> num;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) fin >> A[i][j];


    cin >> n;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> a[i][j];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cout << a[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
    bool check=true;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) for(int k=j+1;k<n;k++) if(a[i][j] && a[i][k] && a[j][k]) check=false;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) if(a[i][j]!=a[j][i] || (A[i][j]-a[i][j])<0) check=false;
    cout << check << '\n';
}
*/
