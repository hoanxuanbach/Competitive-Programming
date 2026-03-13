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

#define double long double
double PI = acos(-1.0);
void solve(){
    int la=0,lb=1,ra=90,rb=1;

    auto fmax = [&](int a,int b,int x,int y){
        if(a*y>b*x) return pii{a,b};
        else return pii{x,y};
    };
    auto fmin = [&](int a,int b,int x,int y){
        if(a*y<b*x) return pii{a,b};
        else return pii{x,y};
    };

    int La=0,Lb=0,Ra=0,Rb=0;
    int N=20,d=1,k=0;
    for(int i=0;i<=N;i++){
        //0>(-d)*a+k>-90
        if(d<0) tie(la,lb)=fmax(la,lb,-90-k,-d),tie(ra,rb)=fmin(ra,rb,-k,-d); 
        else tie(la,lb)=fmax(la,lb,k,d),tie(ra,rb)=fmin(ra,rb,90+k,d);
        //180-2*(d*a-k)
        k=-2*k-180;
        d=-2*d;
        if(i==N-1) La=la,Lb=lb,Ra=ra,Rb=rb;
    }

    double L=(double)La/Lb,R=(double)Ra/Rb;
    double l=(double)la/lb,r=(double)ra/rb;

    cout << setprecision(10) << fixed << L << ' ' << R << ' ' << l << ' ' << r << '\n';

    int res=inf,S;cin >> S;
    auto check = [&](int A,int B,int C){
        double fA = acos((double)(B*B+C*C-A*A)/(2*B*C))/PI*180;
        double fB = acos((double)(A*A+B*B-C*C)/(2*A*B))/PI*180;
        double fC = acos((double)(A*A+C*C-B*B)/(2*A*C))/PI*180;
        if(fA<L || fA>R) return false;
        if(fB<L || fB>R) return false;
        if(fC<L || fC>R) return false;
        //cout << A << ' ' << B << ' ' << C << ' ' << fA << ' ' << fB << '\n';
        if(fA<l || fA>r) return true;
        if(fB<l || fB>r) return true;
        if(fC<l || fC>r) return true;
        return false;
    };
    for(int N=2;N<=S;N++){;
        for(int a=0;a<=5;a++) for(int b=0;b<=5;b++){
            if(N-a<=0) continue;
            if(2*N-a<=N+b) continue;
            if(check(N-a,N,N+b)){
                if(3*N-a+b<res){
                    res=3*N-a+b;
                    cout << N-a << ' ' << N << ' ' << N+b << '\n';
                }
            }
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
