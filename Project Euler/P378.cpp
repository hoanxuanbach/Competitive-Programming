#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e18;
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
    int N;cin >> N;

    int S=N+2;
    vector<int> f(S);
    for(int i=2;i<S;i++) if(!f[i]){
        for(int j=i;j<S;j+=i) f[j]=i;
    }

    cout << "first" << endl;
    vector<int> T(N+1),C;
    for(int x=1;x<=N;x++){
        int a=x,b=x+1;
        if(a%2==0) a/=2;
        else b/=2;

        T[x]=1;
        while(a>1){
            int j=f[a],k=0;
            while(a%j==0) a/=j,k++;
            T[x]*=(k+1);
        }
        while(b>1){
            int j=f[b],k=0;
            while(b%j==0) b/=j,k++;
            T[x]*=(k+1);
        }
        C.push_back(T[x]);
    }   

    cout << "second" << endl;
    sort(C.begin(),C.end());
    C.erase(unique(C.begin(),C.end()),C.end());
    for(int x=1;x<=N;x++) T[x]=lower_bound(C.begin(),C.end(),T[x])-C.begin()+1;
    int M=(int)C.size();

    vector<int> bit(M+1);
    auto update = [&](int x){
        for(int i=x;i<=M;i+=(i&(-i))) bit[i]++;
    };
    auto query = [&](int x){
        int cnt=0;
        for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
        return cnt;
    };

    cout << "third" << endl;
    vector<int> L(N+1);
    for(int i=1;i<=N;i++){
        L[i]=query(M-T[i]);
        update(M-T[i]+1);
    }

    cout << "last" << endl;
    int res=0;
    bit.assign(M+1,0);
    for(int i=N;i>=1;i--){
        res=(res+L[i]*query(T[i]-1))%mod;
        update(T[i]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
