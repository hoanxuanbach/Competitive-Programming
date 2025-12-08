#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


void solve(){
    int n,m;cin >> n >> m;
    vector<vector<char>> c(n,vector<char>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];

    auto g = [&](char x){
        if(x=='I') return 2;
        else if(x=='P') return 1;
        else if(x=='C') return 0;
        return -1;
    };

    vector<char> CC={'C','P','I'};
    vector<vector<char>> res(n,vector<char>(m));

    bool sw=false;
    auto print = [&](){
        cout << "yes\n";
        if(!sw){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++) cout << res[i][j];
                cout << '\n';
            }
        }
        else{
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++) cout << res[j][i];
                cout << '\n';
            }
        }
    };

    {
        auto full = [&](int x,int y,int k){
            for(int i=0;2*i+x<n;i++) for(int j=0;2*j+y<m;j++){
                int id=g(c[2*i+x][2*j+y]);
                if(id!=-1 && id!=k) return false;
                res[2*i+x][2*j+y]=CC[k];
            }
            return true;
        };

        if(full(0,0,0) && full(1,1,0)){
            if(full(0,1,1) && full(1,0,2)){
                print();
                return;
            }
            if(full(0,1,2) && full(1,0,1)){
                print();
                return;
            }
        }
        if(full(0,1,0) && full(1,0,0)){
            if(full(0,0,1) && full(1,1,2)){
                print();
                return;
            }
            if(full(0,0,2) && full(1,1,1)){
                print();
                return;
            }
        }

    }   
    auto construct = [&](){
        auto fill = [&](int i){
            for(int j=0;j<m;j++){
                int id=g(c[i][j]);
                if(id!=-1 && id!=0) return false;
                res[i][j]='C';
            }
            return true;
        };
        auto full = [&](int i,int k){
            for(int j=0;j<m;j++){
                int id=g(c[i][j]);
                if(id!=-1 && id!=((k^j)&1)+1) return false;
                res[i][j]=CC[((k^j)&1)+1];
            }
            return true;
        };
        
        vector<bool> f(2,true);
        for(int i=0;i<n;i++) if(!fill(i)) f[(i&1)^1]=false;
        for(int i=0;i<n;i++){
            if(full(i,0)) continue;
            if(full(i,1)) continue;
            f[i&1]=false;
        }
        if(f[0]){
            bool ok=true;
            for(int i=1;i<n;i+=2) ok&=fill(i);
            if(ok){
                print();
                return true;
            }
        }
        if(f[1]){
            bool ok=true;
            for(int i=0;i<n;i+=2) ok&=fill(i);
            if(ok){
                print();
                return true;
            }
        }
        auto paint = [&](int j,int x,int y){
            for(int i=0;i<n;i++){
                int id=g(c[i][j]);
                if(id!=-1){
                    if((i&1)==(x&1)){
                        if(id!=0) return false;
                    }
                    else if(id!=y+1) return false;
                }
                if((i&1)==(x&1)) res[i][j]=CC[0];
                else res[i][j]=CC[y+1];
            }
            
            return true;
        };
        for(int x=0;x<=1;x++){
            bool ok=true;
            for(int j=0;j<m;j++){
                if(paint(j,0,(x^j)&1)) continue;
                if(paint(j,1,(x^j)&1)) continue;
                ok=false;
            }
            if(ok){
                print();
                return true;
            }
        }
        return false;
    };
    if(construct()) return;

    sw=true;
    res.assign(m,vector<char>(n));
    vector<vector<char>> nc(m,vector<char>(n));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) nc[j][i]=c[i][j];
    swap(c,nc);
    swap(n,m);

    if(construct()) return;
    cout << "no\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}


