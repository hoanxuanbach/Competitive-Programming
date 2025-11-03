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

void solve(){
    int N=50,T=0;
    int S=(1<<10)-2;
    while(N--){
        string id;cin >> id >> id;
        cout << id << endl;
        vector<vector<int>> c(9,vector<int>(9));
        vector<int> f(1<<10,-1);
        for(int i=0;i<=9;i++) f[1<<i]=i;

        vector<int> row(9),col(9),box(9);
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                char cc;cin >> cc;
                c[i][j]=cc-'0';
                if(c[i][j]){
                    int x=c[i][j];
                    row[i]|=(1<<x);
                    col[j]|=(1<<x);
                    box[(i/3)*3+(j/3)]|=(1<<x);
                }
            }
        }
        function<bool(int,int)> dfs = [&](int x,int y){
            if(x==9) return true;
            int nx=x,ny=y+1;
            if(ny==9) nx++,ny=0;
            if(c[x][y]){
                if(dfs(nx,ny)) return true;
            }
            else{
                int z=(x/3)*3+(y/3);
                int fr=row[x],fc=col[y],fb=box[z];
                int mask=fr|fc|fb;
                for(int i=1;i<=9;i++){
                    if(mask>>i&1) continue;
                    row[x]|=(1<<i);
                    col[y]|=(1<<i);
                    box[z]|=(1<<i);
                    c[x][y]=i;
                    if(dfs(nx,ny)) return true;
                    c[x][y]=0;
                    row[x]=fr;
                    col[y]=fc;
                    box[z]=fb;
                }
            }
            return false;
        };
        dfs(0,0);
        T+=c[0][0]*100+c[0][1]*10+c[0][2];
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++) cout << c[i][j];
            cout << '\n';
        }
    }
    cout << T << '\n';
}
 
signed main(){
    freopen("96.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
