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

int sA,sB;
vector<int> A={5248,1312,2624,5760,3936};
vector<int> B={640,1888,3776,3776,5664};

void solve(){
    for(int a:A) sA+=a;
    for(int b:B) sB+=b;

    set<pair<int,int>> P;
    for(int a=0;a<=A[0];a++) for(int b=0;b<=B[0];b++){
        if(b*A[0]<=a*B[0]) continue;
        int x=b*A[0],y=a*B[0];
        int g=__gcd(x,y);x/=g;y/=g;
        P.insert({x,y});
    }

    int X=1,Y=1;
    int ok=0;
    for(auto [x,y]:P){
        //ok++;
        //if(ok%1000==0) cout << ok << endl;
        bool check=true;

        int ss=0;
        map<int,int> mp;
        for(int i=0;i<=4;i++){
            int bb=x*B[i],aa=y*A[i];
            int gg=__gcd(aa,bb);
            aa/=gg;bb/=gg;
            int k=inf;
            if(aa) k=min(k,A[i]/aa);
            if(bb) k=min(k,B[i]/bb);
            if(!k){
                check=false;
                break;
            }
            int dd=aa*sB*y-bb*sA*x;
            if(dd<0) ss+=dd*(k+1),dd=-dd;
            ss+=dd;k--;
            if(k) mp[dd]+=k;
        }
        if(!check || ss>0) continue;

        ss=-ss;
        int g=ss;
        for(auto [dd,cnt]:mp) g=__gcd(g,dd);
        if((int)mp.size()==1){
            auto [dd,cnt]=*mp.begin();
            if(ss%dd==0 && ss/dd<=cnt){
                cout << x << ' ' << y << endl;
            }
        }
        else if((int)mp.size()==2){
            pii p=*mp.begin();mp.erase(mp.begin());
            pii q=*mp.begin();
            if(p.second>q.second) swap(p,q);

            bool build=false;
            for(int i=0;i<=p.second;i++){
                int ns=ss-i*p.first;
                if(ns<0) continue;
                if(ns%q.first==0 && ns/q.first<=q.second) build=true;
            }
            if(build){
                if(x*Y>X*y) X=x,Y=y;
                cout << x << ' ' << y << endl;
            }
        }
        else if(mp.size()==3){
            pii p=*mp.begin();mp.erase(mp.begin());
            pii q=*mp.begin();mp.erase(mp.begin());
            pii r=*mp.begin();
            if(p.second>q.second) swap(p,q);
            if(p.second>r.second) swap(p,r);
            if(q.second>r.second) swap(q,r);
            
            bool build=false;
            for(int i=0;i<=p.second;i++) for(int j=0;j<=q.second;j++){
                int ns=ss-i*p.first-j*q.first;
                if(ns<0) continue;
                if(ns%r.first==0 && ns/r.first<=r.second) build=true;
            }
            if(build){
                if(x*Y>X*y) X=x,Y=y;
                cout << x << ' ' << y << endl;
            }
        }
        else{
            cout << '*' << x << ' ' << y << ' ' << ss/g << '\n';
            ok+=ss/g;
            for(auto [dd,k]:mp) cout << dd/g << ' ' << k << '\n';
            /*
            ss/=g;
            vector<bool> f(ss+1);f[0]=true;
            vector<int> c(ss+1);
            for(auto [dd,k]:mp){
                int d=dd/g;
                for(int i=0;i<=ss;i++){
                    if(i>=d) c[i]=c[i-d];
                    else c[i]=0;
                    c[i]+=f[i];
                    int cur=c[i]-(i>=d*(k+1)?c[i-d*(k+1)]:0);
                    if(cur) f[i]=1;
                }
            }
            if(f[ss]){
                if(x*Y>X*y) X=x,Y=y;
                cout << x << ' ' << y << endl;
            }
                */
        }
    }
    cout << '*' << ok << endl;
    cout << X << ' ' << Y << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
