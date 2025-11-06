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

int N,S;
vector<int> X;
int sf[maxn],sg[maxn];
vector<int> ff[maxn],gg[maxn];

int cal(int x,int k){
    //cout << "start " << x << ' ' << k << endl;
    if(x>N) return 0LL;
    if(!k) return (N/x);
    if(N/x<S){
        int d=N/x;
        
        int val=0,sub=0;
        if(k>sf[d]) sub=k-sf[d],k=sf[d];
        if(!k) val=N/x;
        else if(k<=(int)ff[d].size()) val=ff[d][k-1];
        else{
            val=cal(x,k-1)-cal(x*X[k-1],k-1);
            ff[d].push_back(val);
        }
        //cout << "cal " << x << ' ' << k << ' ' << val-sub << '\n';
        return val-sub;
    }
    else{
        int val=0,sub=0;
        if(k>sg[x]) sub=k-sg[x],k=sg[x];
        if(!k) val=N/x;
        else if(k<=(int)gg[x].size()) val=gg[x][k-1];
        else{
            val=cal(x,k-1)-cal(x*X[k-1],k-1);
            gg[x].push_back(val);
        }
        //cout << "cal " << x << ' ' << k << ' ' << val-sub << '\n';
        return val-sub;
    }
}

void solve(){

    cin >> N;
    S=sqrtl(N);

    vector<int> p(S),cnt(S);
    for(int i=2;i<S;i++){
        if(!p[i]){
            cnt[i]=1;
            X.push_back(i);
            for(int j=i;j<S;j+=i) p[j]=1;
        }
        cnt[i]+=cnt[i-1];
    }
    int sz=(int)X.size();
    
    for(int i=1;i<S;i++){
        int s=sqrtl(i);
        sf[i]=upper_bound(X.begin(),X.end(),s)-X.begin();
    }
    for(int i=1;i<=S;i++){
        int s=sqrtl(N/i);
        sg[i]=upper_bound(X.begin(),X.end(),s)-X.begin();
    }

    auto get = [&](int x){
        return cal(x,sg[x]);
    };

    int res=N;
    for(int x=1;x<=S;x++){
        cout << x << endl;
        int val=(get(x)-1+sg[x]-cnt[x-1]);
        res-=val;
        //cout << '*' << x << ' ' << sg[x] << ' ' << val << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
