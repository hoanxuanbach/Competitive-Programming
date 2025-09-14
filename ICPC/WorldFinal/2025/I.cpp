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
    
    int n,k;cin >> n >> k;
    //vector<int> a(n);
    //for(int i=0;i<n;i++) cin >> a[i];
    auto query = [&](int x,int y){
        cout << x << ' ' << y << endl;
        //a[x-1]=(a[x-1]+y)%n;

        int val=1;cin >> val;
        //vector<int> b=a;
        //sort(b.begin(),b.end());
        //for(int i=1;i<n;i++) if(b[i]!=b[i-1]) val++;
        return val;
    };
    for(int i=1;i<=n;i++){
        int x=k;
        for(int j=0;j<n;j++){
            x=query(i,1);   
            if(x==1) return;
            if(x>k){
                k=x;
                break;
            }
        }
    }
    assert(k==n);

    vector<bool> ins(n+1);
    ins[1]=true;
    for(int i=1;i<n;i++){
        for(int j=1;j<=n;j++) if(ins[j]){
            k=query(j,1);
            if(k==1) return;
        }
        for(int j=1;j<=n;j++){
            if(!ins[j]){
                int x=query(j,n-1);
                if(x==1) return;
                if(x>k) ins[j]=true;
                query(j,1);
            }
        }
    }
    if(k==1) return;
    cout << "no" << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
