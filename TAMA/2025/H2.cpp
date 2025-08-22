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
const int inv5 = (3*P+1)/5;
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
    int S=sqrtl(N),K=6;
    
    auto f = [&](Z x){
        return (x*(x+1)/2);
    };
    auto f2 = [&](Z x){
        return x*(x+1)*(2*x+1)/6;
    };
    auto f3 = [&](Z x){
        x=(x*(x+1)/2);
        return x*x;
    };
    auto f4 = [&](Z x){
        return f2(x)*(3*x*x+3*x-1)*inv5;
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
    auto H = [&](int n,int m){
        Z val=0;
        val+=ff(n-1)*(2*n+1)*m*2;
        val-=(f3(n)-f2(n))*m*2;
        val+=(f(m/2)+f(m-m/2))*n*n;

        Z sum=0;
        if(m<n){
            sum+=f(m)*n*(n+1)*(n-m);
            sum-=f(m)*(f(n)-f(m))*(2*n+1);
            sum+=f(m)*(f2(n)-f2(m));
        }
        {
            auto cal = [&](int d){
                int s=(m+d)/2;
                Z cur=f(s)+f(m-s)+(m-s)*(d-1);
                cur=cur*(n-d)*(n-d+1);
                return cur;
            };
            int k=min(n,m);
            int l=2,r=k;
            if(((m+l)&1) && l<=r) sum+=cal(l),l++;
            if(!((m+r)&1) && l<=r) sum+=cal(r),r--;
            if(l<=r){
                l=(m+l)/2;r=(m+r)/2;
                int lt=m-r,rt=m-l;

                sum+=Z(rt-lt+1)*m*(m+1)*(n-m)*(n-m);
                sum+=(f(rt)-f(lt-1))*m*(m+1)*4*(n-m);
                sum+=(f2(rt)-f2(lt-1))*m*(m+1)*4;

                sum-=(f2(rt)-f2(lt-1))*2*(n-m)*(n-m);
                sum-=(f3(rt)-f3(lt-1))*8*(n-m);
                sum-=(f4(rt)-f4(lt-1))*8;
                //assert(lt);
                sum-=(f(rt)-f(lt-1))*(n-m)*(n-m+1);
                sum-=2*(f2(rt)-f2(lt-1))*(2*n-2*m+1);
                sum-=4*(f3(rt)-f3(lt-1));
            }
        }
        
        if(m<n){
            int k=n-m;
            sum+=2*f2(m-1)*f(k);
            sum+=((f(k+1)-1)*(k+2)-(f2(k+1)-1))*(m-1)*m;

            int x=(k+1)/2;
            sum+=ff(x)*(2*k+3)*m;
            sum-=(f3(x)+f2(x))*2*m;

            x=(k+2)/2;
            sum+=ff(x)*(2*k+5)*m;
            sum-=(f3(x)+f2(x))*2*m;
            sum-=m*(k+1);
        }

        int k=min(n,m)-1;
        sum+=2*ff2(k)*n-(f3(k)+(2*f4(k)+f2(k))/3);
        sum+=(f(k)*n+f2(k)*(n-1)-f3(k))*m;
        sum-=(f2(k)*n+f3(k)*(n-1)-f4(k));

        int l=m-k,r=m-1;
        if((l&1) && l<=r) sum+=f(l/2)*(m-l+1)*(n-m+l),l++;
        if(!(r&1) && l<=r) sum+=f(r/2)*(m-r+1)*(n-m+r),r--; 
        if(l<=r){
            l/=2;r/=2;
            sum+=(ff(r)-ff(l-1))*n;
            sum+=(f(r)-f(l-1))*m*(n-m);
            sum+=(f2(r)-f2(l-1))*(2*m-n)*2;
            sum-=(f3(r)-f3(l-1))*4;

            sum+=(f2(r)-f2(l-1))*m*(n-m);
            sum+=(f3(r)-f3(l-1))*(2*m-n)*2;
            sum-=(f4(r)-f4(l-1))*4;
        }

        l=m-k;r=m-1;
        if(!(l&1) && l<=r) sum+=f(l/2)*(m-l+1)*(n-m+l),l++;
        if((r&1) && l<=r) sum+=f(r/2+1)*(m-r+1)*(n-m+r),r--;
        if(l<=r){
            l=(l+1)/2;r/=2;
            //l<=i<=r (m-2*i+1)*(n-m+2*i-1)+(m-2*i+1)*(n-m+2*i-1);
            sum+=(ff(r)-ff(l-1))*n;
            sum+=(f(r)-f(l-1))*(m+1)*(n-m-1);
            sum+=(f2(r)-f2(l-1))*(2*m-n+2)*2;
            sum-=(f3(r)-f3(l-1))*4;

            sum+=(f2(r)-f2(l-1))*(m+1)*(n-m-1);
            sum+=(f3(r)-f3(l-1))*(2*m-n+2)*2;
            sum-=(f4(r)-f4(l-1))*4;
        }
        val+=sum*2;
        return val;
    };
    auto G = [&](int n,int m){
        Z val=0;
        val+=f2(n)*n-f(n)*n+f2(n)-f3(n);

        int k=(n-2)/2;
        val+=ff(k)*(2*n-3);
        val-=2*(f3(k)+f2(k));
        
        k=(n-1)/2;
        val+=ff(k)*(2*n-1);
        val-=2*(f3(k)+f2(k));

        return val*m;
    };
    auto F = [&](int n,int m){
        Z res=0;

        Z val=0;
        if(m>=2*n){
            for(int a=1;a<=n;a++) for(int b=1;b<=m;b++){
                for(int x=1;x<=n;x++) for(int y=1;y<=m;y++) val+=min(abs(x-a)+y,abs(y-b)+x);
            }
        }
        else{
            auto cal = [&](int n,int m,int a,int b){
                Z cur=2*f2(a-1);

                int d=(a+b)/2;
                cur+=g(a+1,n,0,b-d-1);

                b-=(a-1);
                int x=b/2,y=b-b/2;
                cur+=(f(x)+f(y)+(a-1)*b)*a;

                return cur;
            };
            {
                int k=m-n-1;
                val+=(f2(k)+(n+2)*f(k))*n*n/2;
                val+=(f(n)*m*(n+m+2)-f2(n)*(n+2*m+2)+f3(n))*n/2;
                val+=(f(n)*n*(n+m+2)-f2(n)*(m+2*n+2)+f3(n))*m/2;
                val-=(Z(n)*n*(n+m+2)-f(n)*(m+2*n+2)+f2(n))*m/2;
            }
            {
                Z cur=0;
                for(int i=0;i<=1;i++){
                    if(n>1){
                        {
                            int lt=(3-i)/2,rt=(m-i)/2;
                            cur+=f(n-1)*(f2(rt)-f2(lt-1)+2*(f(rt)-f(lt-1)));
                            cur+=(f(rt)-f(lt-1))*f2(n-1);

                            /*
                            cur-=(f(rt)-f(lt-1))*(n-1)*n;
                            cur+=(f2(rt)-f2(lt-1))*(2*n-1);
                            cur-=(f3(rt)-f3(lt-1));

                            cur-=(f2(rt)-f2(lt-1))*(n-1)*n/2;
                            cur+=(f3(rt)-f3(lt-1))*(2*n-1)/2;
                            cur-=(f4(rt)-f4(lt-1))/2;
                            */
                            //swap(lt,rt);lt=n-lt;rt=n-rt;
                            //cur-=(n-d)*d*d*(2*d-1)/6;
                            //cur+=(n-d)*d*(2*d-1)/6;
                            for(int d=lt;d<=rt;d++){
                                cur-=d*(d+2)*(n-d-1)*(n-d)/2;
                                cur-=d*(n-d-1)*(n-d)*(2*n-2*d-1)/6;
                            }
                            /*
                            cur+=(f2(rt)-f2(lt-1))*n/6;
                            cur-=(f3(rt)-f3(lt-1))*(2*n+1)/6;
                            cur+=(f4(rt)-f4(lt-1))/3;

                            cur-=(f(rt)-f(lt-1))*n/6;
                            cur+=(f2(rt)-f2(lt-1))*(2*n+1)/6;
                            cur-=(f3(rt)-f3(lt-1))/3;
                            */
                        }
                        
                        
                        for(int d=(m+1-i+1)/2;d<=(2*n-1-i)/2;d++){
                            int r=n+m-(2*d+i);
                            int l=n-d;
                            val+=d*(d+2)*(f(r)-f(l-1))/2;
                            val+=d*(f2(r)-f2(l-1))/2;
                        }
                        for(int d=(2*n-i+1)/2;d<=(n+m-1-i)/2;d++){
                            int r=n+m-(2*d+i);
                            int l=1;
                            val+=d*(d+2)*(f(r)-f(l-1))/2;
                            val+=d*(f2(r)-f2(l-1))/2;
                        }
                    }
                    for(int d=(3-i+1)/2;d<=(n-i)/2;d++){
                        int l=m-d-(1-i);
                        int r=m-1;
                        val+=d*(d+2)*(f(r)-f(l-1))/2;
                        val+=d*(f2(r)-f2(l-1))/2;
                    }
                    for(int d=(n+1-i+1)/2;d<=(2*n-i)/2;d++){
                        int l=m-d-(1-i);
                        int r=n+m-(2*d+i);
                        val+=d*(d+2)*(f(r)-f(l-1))/2;
                        val+=d*(f2(r)-f2(l-1))/2;
                    }
                }
                val+=cur/2;
            }
            for(int A=1;A<=n;A++) for(int B=A;B<=m;B++){
                val+=cal(n,m,A,B);
            }
            for(int A=1;A<=n;A++) for(int B=A+1;B<=n;B++){
                val+=cal(m,n,A,B);
            }
        }
    
        res+=4*val;

        val=f(n-1)*n*f(m)+f(m-1)*m*f(n);
        val+=G(n,m)+G(m,n);
        res+=2*val;
        
        res+=H(n,m)+H(m,n);
        return res;
    };

    vector<Z> suf(K+1),dfac(K+1);
    dfac[0]=1;
    for(int i=1;i<=K;i++) dfac[i]=dfac[i-1]/i;
    auto get = [&](vector<Z> &f,int x){
        if(x<K) return f[x];
        suf[K]=1;
        for(int i=K;i>=1;i--) suf[i-1]=suf[i]*(x-i+1);
        Z pre=1,res=0;
        for(int i=0;i<K;i++){
            Z val=f[i]*pre*suf[i+1];
            val*=dfac[i]*dfac[K-1-i];
            if((K-1-i)&1) val=-val;
            res+=val;
            pre*=(x-i);
        }
        return res;
    };

    Z res=0;
    for(int i=1;i<=S;i++){
        int x=N/i;
        if(x<i+2*K){
            for(int j=i;j<=x;j++) res+=F(i,j)*(1+(i!=j));
            continue;
        }
        vector<Z> A(K),B(K);
        for(int j=0;j<K;j++){
            A[j]=F(i,i+2*j);
            B[j]=F(i,i+2*j+1);
            if(j) A[j]+=A[j-1],B[j]+=B[j-1];
        }

        Z sum=0;x-=i;
        if(x&1) sum=get(B,x/2)+get(A,x/2);
        else sum=get(A,x/2)+get(B,x/2-1);
        res+=2*sum-A[0];
    }
    cout << res.x << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}