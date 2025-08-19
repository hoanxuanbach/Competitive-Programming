#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int P = 998244353;
const int inv2 = (P+1)/2;
const int inv3 = (P+1)/3;
const int inv6 = (P+1)/6;

int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x=0) : x(norm(x % P)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        if(x==2) return inv2;
        if(x==3) return inv3;
        if(x==6) return inv6;
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = (int)(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        int v;
        is >> v;
        a = Z(v);
        return is;
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}



void solve(){   
    int N;cin >> N;

    auto f3 = [&](Z x){
        x=(x*(x+1)/2);
        return x*x;
    };
    auto f2 = [&](Z x){
        return x*(x+1)*(2*x+1)/6;
    };
    auto f = [&](Z x){
        return (x*(x+1)/2);
    };
    auto ff2 = [&](int x){
        return f3(x)/3+f2(x)/2+f(x)/6;
    };
    auto ff = [&](Z x){
        return (f2(x)+f(x))/2;
    };
    auto g = [&](Z l,Z r,Z x,Z y){
        return (l+r+x+y)*(r-l+1)*(y-x+1)/2;
    };

    Z total=0;
    Z res=0;
    {
        auto cal = [&](int a,int b){
            if(a>b) swap(a,b);
            Z val=0;
            int t=(b-a)/2,d=(a+b-1)/2;
            val+=Z(b)*(f(d-t-1)-f(d-t-a));
            val+=Z(a)*t*(a-1)+f(a-1)*a-f(a-1)*t-f2(a-1);
            val+=f(a-1)*(d-t)-f2(a-1);
            val+=2*(ff(t+a-1)-ff(t));
            val-=Z(d*(d+1)/2)*(a-1);  
            return val;
        };
        cout << "First" << endl;
        vector<Z> cnt(N+1);
        for(int i=1;i<=N;i++) cnt[i]=cnt[i-1]+N/i;
        for(int a=1;a<=N;a++) for(int b=a;a*b<=N;b++){
            Z sum=cnt[N/b]-cnt[a-1]-Z(b-1)*(N/b-a+1);
            res+=cal(a,b)*sum*(1+(a!=b));
        }
        for(int a=1;a*a<=N;a++){
            int d=(2*a-1)/2;
            for(int n=a;n<=N/a;n++) res+=g(1,d,0,n-a)*(N/n-a+1);
        }
        cout << "Second" << endl;
        /*
        for(int a=1;a<=N;a++) for(int b=a+1;a*b<=N;b++){
            int d=(a+b-1)/2;
            for(int n=a;n<=N/b;n++) res+=Z(d+1+n-a)*(n-a+1)*d*(N/n-b+1);
        }
        */
        for(int n=1;n<=N;n++) for(int d=2;n*d<=2*N;d++){
            int m=N/n;
            int k=(d-1)/2;
            int r=min(m,d-1);
            int l=max(d/2+1,d-n);
            if(l>r) continue;
            Z val=0;
            Z A=k+n-d+1,B=n-d+1,C=m+1;
            val+=C*A*B*(r-l+1)+(C*A+C*B-A*B)*(f(r)-f(l-1))+(C-A-B)*(f2(r)-f2(l-1))-(f3(r)-f3(l-1));
            //for(int b=l;b<=r;b++) val+=Z(C-b)*(A+b)*(B+b);
            res+=val*k;
        }
        for(int n=1;n<=N;n++){
            for(int d=1;n*d<=N;d++){
                int m=N/n;
                int l=d+1,r=min(n+d,m);
                if(l<=r) res+=g(1,n,1,d/2)*2*(f(m-l+1)-f(m-r));
            }
        }
        for(int x=1;x<=N;x++) for(int m=1;x*m<=N;m++){
            int n=N/m,y=min(x,m);
            res+=(f(n-x+1)*m+f2(n-x+1))*m*y/2;

            y=min(x-1,m);
            res+=(f(n-x+1)*m+f2(n-x+1))*m*y/2;
        }
        total+=4*res;
    }
    {   
        cout << "Third" << endl;
        res=0;
        auto get = [&](int n,int m){
            Z val = 0;
            
            val+=f(n)*m*m*n;
            val-=f2(n)*m*m;
            val+=f2(n)*m*n;
            val-=f3(n)*m;
            
            val+=f(n-1)*n*m*(n+m);
            val-=f2(n-1)*n*m;
            val-=f2(n-1)*m*(n+m);
            val+=f3(n-1)*m;
            val/=2;

            val+=g(0,(n-1)/2,1,m)*f(N/m-n);
            val+=g(0,n/2,1,m)*f(N/m-n);
            val-=2*f(m)*f(n-1);
            return val;
        };
        for(int n=1;n<=N;n++) for(int m=1;n*m<=N;m++){
            res+=2*get(n,m);
        }
        total+=2*res;
    }
    {
        cout << "Fourth" << endl;
        res=0;
        auto cal = [&](int m,int s){
            Z val;
            int d=(s+m+1)/2;
            int l=1,r=min(s,d-1);  
            if(d>m){
                int k=min(d-m,r);
                val+=g(1,k,1,m);
                l+=k;
            }
            
            if(l<=r){
                val+=f(d)*Z(r-l+1);
                val-=ff(r)-ff(l-1);

                val+=f(m-d+s)*Z(r-l+1);
                val-=ff(s-l)-ff(max(0LL,s-r-1));
            }
            l=r+1,r=s;
            val+=g(0,r-l,1,m);
            return val;
        };
        for(int s=1;s<=N;s++) for(int m=1;s*m<=N;m++){
            
            int n=N/m;//s->n
            res+=2*cal(m,s)*f(n-s);

            int d=min((s+m+1)/2,m);
            res+=(ff2(n-s)+ff(n-s)*d)*d;
            res+=(ff2(n)-ff2(s)-f2(s)*(n-s)+(ff(n)-ff(s)-f(s)*(n-s))*(m-d))*(m-d);
            res-=f(n-s)*(s+m-d)*s*(m-d);
        
            d=max(0LL,(m-s+1)/2);
            res+=ff2(n-s)*d;
            res+=Z(s+d+2)*(Z(s)*s*(n-s)-(f(n)-f(s))*2*s+f2(n)-f2(s))*d;
            res+=((f(n)-f(s))*s-(f2(n)-f2(s)))*d;
            res+=(ff2(n-s-1)+ff(n-s-1)*(m-d+2))*(m-d);

            res-=ff(n-s)*(2+d)*d;
        }
        cout << "Fifth" << endl;
        for(int a=1;a<=N;a++) for(int m=1;a*m<=N;m++){
            //cout << a << ' ' << m << endl;
            int n=N/m;

            int d=min((m+1)/2,m);
            res+=(g(0,a-1,1,d)+g(0,a-1,1,m-d))*(n-a+1);
    
            d=max(0LL,(m+1)/2);
            res+=(g(1,m-d,1,a-1)+g(1,d,1,a-1))*(n-a+1);
        }
    }

    total+=2*res;
    cout << total.x << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}