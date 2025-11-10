#include<bits/stdc++.h>
using namespace std;
#define ll long long

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
	int n = (int)poly.size(), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
bool lineHull(P a, P b, vector<P>& poly) {
	int endA = extrVertex(poly, (a - b).perp());
	int endB = extrVertex(poly, (b - a).perp());
	if((cmpL(endA) < 0 || cmpL(endB) > 0)) return true;
    int n=(int)poly.size();
    array<int, 2> res;
	for(int i=0;i<=1;i++){
		int lo = endB, hi = endA;
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return true;
    if (!cmpL(res[0]) && !cmpL(res[1]))
        switch ((res[0] - res[1] + n + 1) % n) {
            case 0: return true;
            case 2: return true;
        }
    return false;
}

#define int long long 
#define pii pair<int,int>
void solve(){
    int n;cin >> n;
    vector<Point<ll>> P(n);
    for(int i=0;i<n;i++) cin >> P[i].x >> P[i].y;

    int m;cin >> m;
    vector<Point<ll>> Q(m);
    for(int i=0;i<m;i++) cin >> Q[i].x >> Q[i].y;

    vector<int> l(n),r(n);
    
    int p=0;
    for(int i=0;i<n;i++){
        
        while(max({P[i].cross(Q[2],P[(p+1)%n]),P[i].cross(Q[1],P[(p+1)%n]),P[i].cross(Q[0],P[(p+1)%n])})<=0 && lineHull(P[i],P[(p+1)%n],Q)) p=(p+1)%n;
        r[i]=p;
    }

    p=n-1;
    for(int i=n-1;i>=0;i--){
        while(min({P[i].cross(Q[1],P[(p+n-1)%n]),P[i].cross(Q[2],P[(p+n-1)%n]),P[i].cross(Q[0],P[(p+n-1)%n])})>=0 && lineHull(P[i],P[(p+n-1)%n],Q)) p=(p+n-1)%n;
        l[i]=p;
    }

    for(int i=0;i<n;i++){
        r[i]=(r[i]+n-i)%n;
        l[i]=(i-l[i]+n)%n;
    }

    vector<int> pre(n);
    for(int i=0;i<n;i++){
        pre[i]=r[i];
        if(i) pre[i]+=pre[i-1];
    }

    int res=0;
    for(int i=0;i<n;i++){
        int lt=1,rt=r[i],pos=rt+1;
        while(lt<=rt){
            int x=(lt+rt)>>1;
            if(l[i]+1+x+r[(i+x)%n]>n) pos=x,rt=x-1;
            else lt=x+1;
        }
        if(pos>r[i]) continue;
        int add=0,cnt=r[i]-pos+1;
        add+=(l[i]+1-n)*cnt+(pos+r[i])*cnt/2;

        lt=(i+pos)%n,rt=(i+r[i])%n;
        if(lt<=rt){
            add+=pre[rt];
            if(lt) add-=pre[lt-1];
        }
        else{
            add+=pre[n-1]+pre[rt];
            if(lt) add-=pre[lt-1];
        }
        res+=add;
        //cout << '*' << i << ' ' << l[i] << ' ' << r[i] << ' ' << add << '\n';
        //sum(pos<=j<=r[i]) l[i]+1+j+r[(i+j)%n]-n
    }
    cout << res/3 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}