#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+5;
const int inf = 1e9;

int n;
struct Point{
    int x,y;
    Point(int x=0,int y=0):x(x),y(y){}
    bool operator<(const Point &o)const{
        return (x!=o.x?x<o.x:y<o.y);
    }
};
struct Segment{
    Point a,b;
    Segment(Point a=Point(),Point b=Point()):a(a),b(b){}
    double get(int x)const{
        if(a.x==b.x) return a.y;
        return a.y+(double)(b.y-a.y)/(b.x-a.x)*(x-a.x);
    }
    bool operator<(const Segment &o)const{
        int x=max(a.x,o.a.x);
        return get(x)<o.get(x);
    }
}S[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    vector<pair<Point,int>> p;
    for(int i=1;i<=n;i++){
        Point a,b;cin >> a.x >> a.y >> b.x >> b.y;
        if(b<a) swap(a,b);
        S[i]=Segment(a,b);
        p.push_back({a,i});
        p.push_back({b,i});
    }
    sort(p.begin(),p.end());
    map<Segment,Point> mp;
    mp[Segment(Point(-inf,-inf),Point(-inf,inf))]=Point();
    for(int i=0;i<2*n;i++){
        auto [x,id]=p[i];
        if(x<S[id].b){
            auto it=prev(mp.emplace(S[id],x).first);
            if(i) cout << it->second.x << ' ' << it->second.y << ' ' << x.x << ' ' << x.y << '\n';
            it->second=x;
        }
        else{
            auto it=mp.find(S[id]);
            prev(it)->second=x;
            mp.erase(it);
        }
    }
}