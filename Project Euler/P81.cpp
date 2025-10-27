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
    int N=80;
    vector<vector<int>> a(N+1,vector<int>(N+1,inf));
    for(int i=1;i<=N;i++){

        string S;
        cin >> S;

        string cur;
        
        int j=1;
        for(char c:S){
            if(c>='0' && c<='9') cur+=c;
            else{
                if(!cur.empty()) a[i][j++]=stoi(cur);
                cur.clear();
            }
        }
        if(!cur.empty()) a[i][j++]=stoi(cur);
    }
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) if(i!=1 || j!=1) a[i][j]+=min(a[i-1][j],a[i][j-1]);
    cout << a[N][N] << '\n';
}
 
signed main(){
    freopen("81.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
