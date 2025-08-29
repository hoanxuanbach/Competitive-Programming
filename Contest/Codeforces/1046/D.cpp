#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
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

int T,val[maxn];
vector<int> A;
vector<int> P={134,132,131,130,129,128,127,126,125,124,123};

void build(){
    int N=100000,M=25000;
    
    for(int x:P){
        int k=(N-1)/x+1;
        while(k--) A.push_back(x);
    }

    int p=1;
    for(int i=1;i<=N;i++){
        int cnt=1,d=0;
        for(int x:P){
            if(i<x){
                cnt=0;
                break;
            }
            int k=(N-1)/x+1;
            int t=min((i-d)/x,k);
            k-=t;d+=x*t;
            if(k){
                int s=k/(i/x);
                cnt+=s;k-=(i/x)*s;d=(i/x)*x;
                if(k){
                    cnt++;d=0;
                    d+=k*x;
                }
            }
        }
        val[i]=cnt;
        if(val[i]!=val[p]){
            assert(p<=2*i);
            T=max(T,2*(p-i));
            p=i;
        }
    }
    T=max(T,2*(N-p+1));
    assert(T+(int)A.size()<=M);
    T=M-(int)A.size();
    //cout << "T " << T << endl;
}

void solve(){
    int sum=0;
    auto query = [&](vector<int> x){
        sum+=(int)x.size();
        cout << "? " << (int)x.size() << ' ';
        for(int d:x) cout << d << ' ';
        cout << endl;
        int ret=1;cin >> ret;
        /*
        int cnt=0;
        for(int d:x){
            if(d>W) return 0LL;
            if(cnt+d<=W) cnt+=d;
            else ret++,cnt=d;
        }
        */
        return ret;
    };



    int N=100000,M=25000;
    int X=query(A);
    int l=-1,r=-1;
    for(int i=1;i<=N;i++){
        if(val[i]==X){
            if(l==-1) l=i;
            r=i;
        }
    }
    vector<int> a;
    int res=-1;
    if(l==r) res=l;
    else if(r<P[0]){
        a.clear();   
        vector<int> num(r+1);
        for(int i=1;i<=T;i++) a.push_back(1);

        auto get = [&](int w){
            int ret=1;
        
            int cnt=0;
            for(int d:a){
                if(d>w) return 0LL;
                if(cnt+d<=w) cnt+=d;
                else ret++,cnt=d;
            }
            return ret;
        };

        bool check=true;
        for(int i=1;i<=r;i++){
            num[i]=get(i);
            if(num[i]==num[i-1]) check=false;
        }
        assert(check);

        X=query(a);
        if(X==0) res=1;
        else{
            for(int i=l;i<=r;i++){
                if(num[i]==X){
                    res=i;
                    break;
                }
            }
        }
    }
    else{
        a.clear();
        for(int i=1;i<=r-l;i++) a.push_back(l),a.push_back(i);
        X=query(a);
        res=(r-(X-(r-l)));
    }
    cout << "! " << res << endl;
    assert(sum<=M);
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    build();
    int test=1;cin >> test;
    while(test--) solve();
}
