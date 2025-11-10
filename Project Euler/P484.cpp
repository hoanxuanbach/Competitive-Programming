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
    int N;cin >> N;
    /*
    int T=0;
    vector<int> f(N+1);
    for(int i=2;i<=N;i++){
        if(!f[i]){
            for(int j=i;j<=N;j+=i) f[j]=i;
        }
        int d=i,x=i;
        while(x>1){
            int j=f[x],k=0;
            while(x%j==0) x/=j,k++;
            if(k%j!=0) d/=j;
        }
        T+=d;
    }
    cout << T << '\n';
    */
    int S=sqrtl(N)+1;

    __int128 res=N-1;
    vector<int> p(S);
    for(int i=2;i<S;i++){
        if(i%100000==0) cout << i/100000 << endl;
        if(!p[i]){
            for(int j=i;j<S;j+=i) p[j]=i;
        }
        vector<array<int,3>> X;
        int x=i;
        while(x>1){
            int j=p[x],k=0,d=1;
            while(x%j==0) x/=j,d*=j,k++;
            X.push_back({j,d*d,2*k});
        }
        int m=(int)X.size();
        for(int j=0;j<(1<<m);j++){
            int d=i*i;

            bool ok=true;
            for(int k=0;k<m;k++) if(j>>k&1){
                if(d>N/X[k][0]) ok=false;
                else d*=X[k][0];
            }
            if(!ok) continue;

            for(int k=0;k<m;k++){
                if(j>>k&1) X[k][1]*=X[k][0],X[k][2]++;
            }
            int val=1;
            for(int k=0;k<m;k++){
                int a=X[k][1]/X[k][0],b=X[k][2];
                if(b%X[k][0]==0) a*=X[k][0];
                int cur=a;
                a=X[k][1]/X[k][0]/X[k][0];
                b=X[k][2]-1;
                if(b%X[k][0]==0) a*=X[k][0];
                cur-=a;
                val*=cur; 
            }
            if(ok) res+=(__int128)(N/d)*val;
            for(int k=0;k<m;k++) if(j>>k&1) X[k][1]/=X[k][0],X[k][2]--;
        }
    }
    string ans;
    while(res) ans+=char('0'+res%10),res/=10;
    reverse(ans.begin(),ans.end());
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
