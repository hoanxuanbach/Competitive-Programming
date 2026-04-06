#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 1e8+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int T[maxn];

void solve(){
    int N;cin >> N;
    vector<int> P;
    for(int i=2;i<=N;i++) if(!T[i]){
        if(i%5==1 || i%5==4) P.push_back(i);
        for(int j=i;j<=N;j+=i) T[j]=i;
    }

    auto tonelli_shanks = [&](int n,int p){
        if(n==0) return 0LL;
        if(power(n,(p-1)/2,p)==p-1) return -1LL;
        
        int Q=p-1,S=0;
        while(Q%2==0) Q/=2,S++;

        int z=2;
        while(power(z,(p-1)/2,p)==1) z++;

        int M=S;
        int c=power(z,Q,p);
        int t=power(n,Q,p);
        int R=power(n,(Q+1)/2,p);

        while(true){
            if(t==0) return 0LL;
            if(t==1) return R;

            int i=1;
            int tt=t*t%p;
            while(tt!=1) tt=tt*tt%p,i++;

            int b=power(c,1<<(M-i-1),p);

            R=(R*b)%p;
            c=(b*b)%p;
            t=(t*c)%p;
            M=i;
        }
    };

    int res=5,cnt=0;
    for(int p:P){
        cnt++;
        if(cnt%1000==0) cout << p << ' ' << cnt << endl;
        bool check=false;

        vector<int> S;
        int d=p-1;
        while(d>1){
            int j=T[d];
            S.push_back(j);
            while(d%j==0) d/=j;
        }

        auto f = [&](int x){
            x++;
            if(x%2==0) x/=2;
            else x=(x+p)/2;
            for(int k:S) if(power(x,(p-1)/k,p)==1) return;
            check=true;
        };
        if(p%3==4){
            int x=power(5,(p+1)/4,p);
            //cout << p << ' ' << x << endl;
            if(x!=-1) f(x),f(p-x);
        }
        else{
            int x=tonelli_shanks(5,p);
            //cout << p << ' ' << x << endl;
            if(x!=-1) f(x),f(p-x);
        }
        if(check) res+=p;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
