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
    int n;cin >> n;
    vector<int> L(n+1),R(n+1);
    bool check=true;
    for(int i=1;i<=n;i++){
        cin >> L[i] >> R[i];
        if(R[i] && !L[i]) check=false;
    }
    if(!check){
        cout << "impossible\n";
        return;
    }

    vector<vector<int>> A(n+1),B(n+1);

    function<void(int)> dfs = [&](int u){
        //cout << "dfs " << u << endl;
        if(L[u]) dfs(L[u]);
        if(R[u]) dfs(R[u]);
        int sl=(int)A[L[u]].size(),sr=(int)A[R[u]].size();
        vector<int> X,Y;
        if(sl>sr+1){
            for(int i=0;i<sr;i++) X.push_back(A[L[u]].back()),A[L[u]].pop_back();
            swap(A[u],A[L[u]]);
            swap(Y,A[R[u]]);
            reverse(Y.begin(),Y.end());
        }
        else if(sr>sl){
            for(int i=1;i<sl;i++) Y.push_back(A[R[u]].back()),A[R[u]].pop_back();
            swap(A[u],A[R[u]]);
            swap(X,A[L[u]]);
            reverse(X.begin(),X.end());
        }
        else{
            swap(X,A[L[u]]);
            swap(Y,A[R[u]]);
            reverse(X.begin(),X.end());
            reverse(Y.begin(),Y.end());
        } 
        A[u].push_back(u);
        while(!X.empty() || !Y.empty()){
            if((int)X.size()>(int)Y.size()) A[u].push_back(X.back()),X.pop_back();
            else A[u].push_back(Y.back()),Y.pop_back();
        }

        if(sl>sr){
            for(int i=0;i<sr;i++) X.push_back(B[L[u]].back()),B[L[u]].pop_back();
            swap(B[u],B[L[u]]);
            swap(Y,B[R[u]]);
            reverse(Y.begin(),Y.end());
        }
        else if(sr>sl-1){
            for(int i=1;i<sl;i++) Y.push_back(B[R[u]].back()),B[R[u]].pop_back();
            swap(B[u],B[R[u]]);
            swap(X,B[L[u]]);
            reverse(X.begin(),X.end());
        }
        else{
            swap(X,B[L[u]]);
            swap(Y,B[R[u]]);
            reverse(X.begin(),X.end());
            reverse(Y.begin(),Y.end());
        }
        B[u].push_back(u);
        while(!X.empty() || !Y.empty()){
            if((int)X.size()>(int)Y.size()) B[u].push_back(X.back()),X.pop_back();
            else B[u].push_back(Y.back()),Y.pop_back();
        }
    };
    dfs(1);

    for(int i=0;i<n;i++) cout << A[1][i] << ' ';
    cout << '\n';
    for(int i=0;i<n;i++) cout << B[1][i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
