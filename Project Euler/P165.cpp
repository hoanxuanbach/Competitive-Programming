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
const double EPS = 1E-7;

struct pt {
    double x, y;

    bool operator<(const pt& p) const
    {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

struct line {
    double a, b, c;

    line() {}
    line(pt p, pt q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(pt p) const { return a * p.x + b * p.y + c; }
};

double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

inline bool betw(double l, double r, double x)
{
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool intersect(pt a, pt b, pt c, pt d, pt& left, pt& right)
{
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;
    line m(a, b);
    line n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS) {
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
            return false;
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}
void solve(){
    int N;cin >> N;
    vector<int> s(4*N+1);
    s[0]=290797;
    for(int i=1;i<=4*N;i++) s[i]=s[i-1]*s[i-1]%50515093;
    vector<pair<pt,pt>> S(N);
    for(int i=0;i<N;i++){
        pt A = {(double)(s[i*4+1]%500),(double)(s[i*4+2]%500)};
        pt B = {(double)(s[i*4+3]%500),(double)(s[i*4+4]%500)};
        S[i]={A,B};
    }
    auto f = [&](pt A,pt B){
        return (abs(A.x-B.x)<EPS && abs(A.y-B.y)<EPS);
    };

    vector<pair<double,double>> P;
    for(int i=0;i<N;i++) for(int j=0;j<i;j++){
        pt A,B;
        bool ins = intersect(S[i].first,S[i].second,S[j].first,S[j].second,A,B);
        if(!ins) continue;
        if(!f(A,B)) continue;
        if(f(S[i].first,A)) continue;
        if(f(S[i].second,A)) continue;
        if(f(S[j].first,A)) continue;
        if(f(S[j].second,A)) continue;
        P.push_back({A.x,A.y});
    }
    sort(P.begin(),P.end());
    int cnt=1;
    for(int i=1;i<(int)P.size();i++){
        bool nw=true;
        for(int j=i-1;j>=max(0LL,i-20);j--) if(f({P[i].first,P[i].second},{P[j].first,P[j].second})) nw=false;
        if(nw) cnt++;
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
