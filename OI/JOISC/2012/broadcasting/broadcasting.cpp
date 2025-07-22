#include<bits/stdc++.h>
using namespace std; 
#define ll long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second

template<class T>
struct point{
	T x{}, y{};
	point(){ }
	template<class U> point(const point<U> &otr): x(otr.x), y(otr.y){ }
	template<class U, class V> point(U x, V y): x(x), y(y){ }
	template<class U> point(const array<U, 2> &p): x(p[0]), y(p[1]){ }
	friend istream &operator>>(istream &in, point &p){
		return in >> p.x >> p.y;
	}
	friend ostream &operator<<(ostream &out, const point &p){
		return out << "{" << p.x << ", " << p.y << "}";
	}
	template<class U> operator array<U, 2>() const{
		return {x, y};
	}
	T operator*(const point &otr) const{
		return x * otr.x + y * otr.y;
	}
	T operator^(const point &otr) const{
		return x * otr.y - y * otr.x;
	}
	point operator+(const point &otr) const{
		return {x + otr.x, y + otr.y};
	}
	point &operator+=(const point &otr){
		return *this = *this + otr;
	}
	point operator-(const point &otr) const{
		return {x - otr.x, y - otr.y};
	}
	point &operator-=(const point &otr){
		return *this = *this - otr;
	}
	point operator-() const{
		return {-x, -y};
	}
#define scalarop_l(op) friend point operator op(const T &c, const point &p){ return {c op p.x, c op p.y}; }
	scalarop_l(+) scalarop_l(-) scalarop_l(*) scalarop_l(/)
#define scalarop_r(op) point operator op(const T &c) const{ return {x op c, y op c}; }
	scalarop_r(+) scalarop_r(-) scalarop_r(*) scalarop_r(/)
#define scalarapply(applyop, op) point &operator applyop(const T &c){ return *this = *this op c; }
	scalarapply(+=, +) scalarapply(-=, -) scalarapply(*=, *) scalarapply(/=, /)
#define compareop(op) bool operator op(const point &otr) const{ return pair<T, T>(x, y) op pair<T, T>(otr.x, otr.y); }
	compareop(>) compareop(<) compareop(>=) compareop(<=) compareop(==) compareop(!=)
#undef scalarop_l
#undef scalarop_r
#undef scalarapply
#undef compareop
	double norm() const{
		return sqrt(x * x + y * y);
	}
	long double norm_l() const{
		return sqrtl(x * x + y * y);
	}
	T squared_norm() const{
		return x * x + y * y;
	}
	// [0, 2 * pi]
	double angle() const{
		auto a = atan2(y, x);
		if(a < 0) a += 2 * acos(-1);
		return a;
	}
	// [0, 2 * pi]
	long double angle_l() const{
		auto a = atan2(y, x);
		if(a < 0) a += 2 * acosl(-1);
		return a;
	}
	point<double> unit() const{
		return point<double>(x, y) / norm();
	}
	point<long double> unit_l() const{
		return point<long double>(x, y) / norm_l();
	}
	point perp() const{
		return {-y, x};
	}
	point<double> normal() const{
		return perp().unit();
	}
	point<long double> normal_l() const{
		return perp().unit_l();
	}
	point<double> rotate(double theta) const{
		return {x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)};
	}
	point<long double> rotate_l(double theta) const{
		return {x * cosl(theta) - y * sinl(theta), x * sinl(theta) + y * cosl(theta)};
	}
	point reflect_x() const{
		return {x, -y};
	}
	point reflect_y() const{
		return {-x, y};
	}
	point reflect(const point &o = {}) const{
		return {2 * o.x - x, 2 * o.y - y};
	}
};
template<class T, class U>
point<double> lerp(const point<T> &p, const point<U> &q, double t){
	return point<double>(p) * (1 - t) + point<double>(q) * t;
}
template<class T, class U>
point<long double> lerp_l(const point<T> &p, const point<U> &q, long double t){
	return point<long double>(p) * (1 - t) + point<long double>(q) * t;
}
template<class T>
double distance(const point<T> &p, const point<T> &q){
	return (p - q).norm();
}
template<class T>
long double distance_l(const point<T> &p, const point<T> &q){
	return (p - q).norm_l();
}
template<class T>
T squared_distance(const point<T> &p, const point<T> &q){
	return (p - q).squared_norm();
}
template<class T>
T doubled_signed_area(const point<T> &p, const point<T> &q, const point<T> &r){
	return q - p ^ r - p;
}
template<class T>
T doubled_signed_area(const vector<point<T>> &a){
	if(a.empty()) return 0;
	T res = a.back() ^ a.front();
	for(auto i = 1; i < (int)a.size(); ++ i) res += a[i - 1] ^ a[i];
	return res;
}
// [-pi, pi]
template<class T>
double angle(const point<T> &p, const point<T> &q){
	return atan2(p ^ q, p * q);
}
// [-pi, pi]
template<class T>
long double angle_l(const point<T> &p, const point<T> &q){
	return atan2l(p ^ q, p * q);
}
// Check if p->q->r is sorted by angle with respect to the origin
template<class T>
bool is_sorted_by_angle(const point<T> &origin, const point<T> &p, const point<T> &q, const point<T> &r){
	T x = p - origin ^ q - origin;
	T y = q - origin ^ r - origin;
	if(x >= 0 && y >= 0) return true;
	if(x < 0 && y < 0) return false;
	return (p - origin ^ r - origin) < 0;
}
template<class T>
struct compare_by_angle{
	point<T> origin;
	compare_by_angle(const point<T> &origin = point<T>()): origin(origin){ }
	int side(const point<T> &p) const{
		return p < origin ? -1 : p == origin ? 0 : 1;
	}
	bool operator()(const point<T> &p, const point<T> &q) const{
		int sp = side(p), sq = side(q);
		if(sp != sq) return sp < sq;
		return doubled_signed_area(origin, p, q) > 0;
	}
};
// Check if a is sorted by angle with respect to the origin
template<class T>
bool is_sorted_by_angle(const point<T> &origin, const vector<point<T>> &a){
	for(auto i = 0; i < (int)a.size() - 2; ++ i) if(!is_sorted_by_angle(origin, a[i], a[i + 1], a[i + 2])) return false;
	return true;
}
template<class T>
bool counterclockwise(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) > 0;
}
template<class T>
bool clockwise(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) < 0;
}
template<class T>
bool colinear(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) == 0;
}
template<class T>
bool colinear(const vector<point<T>> &a){
	int i = 1;
	while(i < (int)a.size() && a[0] == a[i]) ++ i;
	if(i == (int)a.size()) return true;
	for(auto j = i + 1; j < (int)a.size(); ++ j) if(!colinear(a[0], a[i], a[j])) return false;
	return true;
}
point<double> polar(double x, double theta){
	assert(x >= 0);
	return {x * cos(theta), x * sin(theta)};
}
point<long double> polar_l(long double x, long double theta){
	assert(x >= 0);
	return {x * cosl(theta), x * sinl(theta)};
}
// T must be able to hold the fourth power of max coordinate
// returns [a, b, c, and d lies in a circle]
template<class T>
bool concircular(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b) == 0;
}
// T must be able to hold the fourth power of max coordinate
// returns [d lies in the interior of the circle defined by a, b, c]
template<class T>
bool inside_of_circle(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return (a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b)) * (doubled_signed_area(a, b, c) > 0 ? 1 : -1) > 0;
}
// T must be able to hold the fourth power of max coordinate
// returns [d lies in the exterior of the circle defined by a, b, c]
template<class T>
bool outside_of_circle(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return (a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b)) * (doubled_signed_area(a, b, c) > 0 ? -1 : 1) > 0;
}

using pointint = point<int>;
using pointll = point<long long>;
using pointlll = point<__int128_t>;
using pointd = point<double>;
using pointld = point<long double>;

#define T double
#define POINTS const point<T> &p, const point<T> &q, const point<T> &r
point<T> weighted_mean(POINTS, T a = 0.5, T b = 0.5, T c = 0.5){
	return (a * p + b * q + c * r) / (a + b + c);
}
point<T> circumcenter(POINTS){
	point<T> a = r - p, b = q - p;
	return p + (a * b.squared_norm() - b * a.squared_norm()).perp() / (2 * a ^ b);
}
T circumradius(POINTS){
	return (p - q).norm() * (q - r).norm() * (r - p).norm() / (2 * doubled_signed_area(p, q, r));
}
point<T> incenter(POINTS){
	return weighted_mean(p, q, r, (q - r).norm(), (r - p).norm(), (p - q).norm());
}
T inradius(POINTS){
	return doubled_signed_area(p, q, r) / ((p - q).norm() + (q - r).norm() + (r - p).norm());
}
point<T> orthocenter(POINTS){
	return weighted_mean(p, q, r, (q - p ^ r - p) / ((q - p) * (r - p)), (r - q ^ p - q) / ((r - q) * (p - q)), (p - r ^ q - r) / ((p - r) * (q - r)));
}
template<int i> point<T> excenter(POINTS){
	return weighted_mean(p, q, r, (i == 0 ? -1 : 1) * (q - r).norm(), (i == 1 ? -1 : 1) * (r - p).norm(), (i == 2 ? -1 : 1) * (p - q).norm());
}
template<int i> T exradius(POINTS){
	return doubled_signed_area(p, q, r) / ((i == 0 ? -1 : 1) * (p - q).norm() + (i == 1 ? -1 : 1) * (q - r).norm() + (i == 2 ? -1 : 1) * (r - p).norm());
}
// https://en.wikipedia.org/wiki/Fermat_point
point<T> fermat_point(POINTS){
	if(distance(p, q) <= 1e-9) return p;
	if(distance(q, r) <= 1e-9) return q;
	if(distance(r, p) <= 1e-9) return r;
	double a = (q - r).norm(), b = (r - p).norm(), c = (p - q).norm();
	double cos_theta_p = min(1.0, (q - p) * (r - p) / b / c);
	double cos_theta_q = min(1.0, (r - q) * (p - q) / c / a);
	double cos_theta_r = min(1.0, (p - r) * (q - r) / a / b);
	if(cos_theta_p < -0.5) return p;
	if(cos_theta_q < -0.5) return q;
	if(cos_theta_r < -0.5) return r;
	double x = 1 / sin(acos(cos_theta_p) + acos(-1) / 3), y = 1 / sin(acos(cos_theta_q) + acos(-1) / 3), z = 1 / sin(acos(cos_theta_r) + acos(-1) / 3);
	return weighted_mean(p, q, r, a * x, b * y, c * z);
}
#undef POINTS
#undef T

template<class T>
pair<point<T>, double> minimum_enclosing_circle(vector<point<T>> a){
	int n = (int)a.size();
	shuffle(a.begin(), a.end(), mt19937(1564));
	point<T> o = a[0];
	double r = 0, EPS = 1 + 1e-8;
	for(auto i = 0; i < n; ++ i) if((o - a[i]).norm() > r * EPS){
		o = a[i], r = 0;
		for(auto j = 0; j < i; ++ j) if((o - a[j]).norm() > r * EPS){
			o = (a[i] + a[j]) / 2, r = (o - a[i]).norm();
			for(auto k = 0; k < j; ++ k) if((o - a[k]).norm() > r * EPS){
				o = circumcenter(a[i], a[j], a[k]), r = (o - a[i]).norm();
			}
		}
	}
	return {o, r};
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
const ll inf = 1e18;
const double TL = 1000.00;
const double Stemp= 1e9;
const double Etemp = 1e-4;
double query_temp(double tm){
    return Stemp*pow(Etemp/Stemp,(double)tm/TL);
}
int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

void solve(){   
    freopen("4.in","r",stdin);
    freopen("4.out","w",stdout);
    ifstream fin("4.txt");

    ll n,k;cin >> n >> k;
    vector<pointll> P(n);
    for(int i=0;i<n;i++) cin >> P[i];

    ll mn=inf;
    vector<ll> dist(k);
    vector<pointll> res(k);

    /*
    while(true){
        vector<pointll> C(k);
        for(int i=0;i<k;i++) C[i]=P[rand_int(0,n-1)];

        int Iter=10000;
        while(Iter--){
            vector<ll> d(k,0);
            vector<int> f(n);
            for(int i=0;i<n;i++){
                ll id=-1,dd=inf;
                for(int j=0;j<k;j++){
                    ll dt=(C[j].x-P[i].x)*(C[j].x-P[i].x)+(C[j].y-P[i].y)*(C[j].y-P[i].y);
                    if(dt<dd) dd=dt,id=j;
                }
                f[i]=id;
                assert(id!=-1);
                d[id]=max(d[id],dd);
            }
            ll score=0;
            for(int i=0;i<k;i++) score+=d[i];

            if(score<mn){
                mn=score,dist=d,res=C;
                cerr << mn << endl;
                for(int i=0;i<k;i++) cout << res[i].x << ' ' << res[i].y << ' ' << dist[i] << '\n'; 
                cout << '\n';
            }

            vector<int> sz(k);
            for(int i=0;i<k;i++) C[i]={0,0};
            for(int i=0;i<n;i++) sz[f[i]]++,C[f[i]]+=P[i];
            for(int i=0;i<k;i++) if(sz[i]) C[i].x/=sz[i],C[i].y/=sz[i];
        }
    }
    */

    //Stimullated Annealing

    auto st = clock();

    vector<int> f(n);
    vector<vector<int>> g(k);
    vector<pointll> C(k);
    vector<ll> d(k);

    auto cal = [&](int id){
        vector<pointll> p;
        for(int i:g[id]) p.push_back(P[i]);
        if(p.empty()) C[id]={0,0};
        else C[id]=minimum_enclosing_circle(p).first;
        d[id]=0;
        for(int i:g[id]) d[id]=max(d[id],(P[i].x-C[id].x)*(P[i].x-C[id].x)+(P[i].y-C[id].y)*(P[i].y-C[id].y));
    };
    /*
    for(int i=0;i<n;i++){
        f[i]=rand_int(0,k-1);
        g[f[i]].push_back(i);
    }
    */
    
    for(int i=0;i<k;i++) fin >> C[i] >> d[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            ll dd=(C[j].x-P[i].x)*(C[j].x-P[i].x)+(C[j].y-P[i].y)*(C[j].y-P[i].y);
            if(dd<=d[j]){
                f[i]=j;
                break;
            }
        }
        g[f[i]].push_back(i);
    }
    
    ll cur=0;
    for(int i=0;i<k;i++) cal(i),cur+=d[i];
    if(cur<mn){
        mn=cur,dist=d,res=C;
        cerr << mn << endl;
        for(int i=0;i<k;i++) cout << res[i].x << ' ' << res[i].y << ' ' << dist[i] << '\n'; 
        cout << '\n';
    }
    while(true){
        auto tm=1.0*(clock()-st)/CLOCKS_PER_SEC;
        if(tm>TL) break;
        auto T=query_temp(tm);
        
        int x=rand_int(0,n-1),s=f[x];
        int t=rand_int(0,k-1);
        if(s==t) continue;
        
        ll nw=cur-d[s]-d[t];
        g[s].erase(find(g[s].begin(),g[s].end(),x));
        
        ll ds=d[s],dt=d[t];
        pointll cs=C[s],ct=C[t];

        g[t].push_back(x);f[x]=t;
        cal(t);cal(s);
        nw+=d[s]+d[t];
        
        
        if(nw<mn){
            mn=nw,dist=d,res=C;
            cerr << mn << endl;
            for(int i=0;i<k;i++) cout << res[i].x << ' ' << res[i].y << ' ' << dist[i] << '\n'; 
            cout << '\n';
        }
        
        if(nw<cur || exp((cur-nw)/T)>=pp(rng)) cur=nw;
        else{
            g[t].pop_back();f[x]=s;
            g[s].push_back(x);

            d[s]=ds,d[t]=dt;
            C[s]=cs,C[t]=ct;
        }
        
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}