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
 
const int maxn = 1e5+5;
const int maxl = 20;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,k;cin >> n >> k;
    if(k==1){
        cout << n*(n+1)/2 << '\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++) cout << char('a'+((i+j)&1));
            cout << '\n';
        }
    }
    else if(k==2){
        int cnt=0;
        for(int i=1;i<=n;i++) cnt+=(i+1)/2;
        cout << cnt << '\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++) cout << char('a'+((i+(j+1)/2)&1));
            cout << '\n';
        }
    }
    else{
        int m=n*(n+1)/2;
        cout << (m-1)/k+1 << '\n';

        int T=0;
        vector<vector<int>> f(n+1,vector<int>(n+1,0));
        int dir=0,cur=0;
        int x=1,y=1;
        while(x<=n){
            if(!cur) T++,cur=k;
            f[x][y]=T;cur--;
            if(dir && y==1) x++,dir^=1;
            else if(!dir && x==y){
                if(f[x][1]==f[x][y]) x++,y=1;
                else if(cur!=1) x++,y=x,dir^=1;
                else if(x<n){
                    f[x][x-k+2]=T+1;x++;
                    f[x][x]=T;f[x][x-1]=T;
                    y=x-2;dir^=1;cur=k-1;T++;
                }
                else x++;
            }
            else if(dir) y--;
            else if(!dir) y++;
        }
        vector<vector<int>> g(T+1);
        for(int i=2;i<=n;i++) for(int j=1;j<i;j++){
            int a=f[i][j],b=f[i-1][j];
            if(a!=b) g[max(a,b)].push_back(min(a,b));
            b=f[i][j+1];
            if(a!=b) g[max(a,b)].push_back(min(a,b));
        }
        vector<char> C(T+1);
        for(int i=1;i<=T;i++){
            vector<bool> f(26);
            for(int x:g[i]) f[C[x]-'a']=true;
            int k=0;
            while(k<26 && f[k]) k++;
            assert(k<26);
            C[i]=char('a'+k);
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++) cout << C[f[i][j]];
            cout << '\n';
        }
    }
}
 
signed main(){
    freopen("A.txt","r",stdin);
    freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
