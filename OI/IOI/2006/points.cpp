#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+5;
struct point{
    int x=0,y=0;
    point(int x=0,int y=0):x(x),y(y){}
    friend point operator+(point a,point b){
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator-(point a,point b){
        return point(a.x-b.x,a.y-b.y);
    }
    friend int operator*(point a,point b){
        return a.x*b.y-a.y*b.x;
    }
    int dot(point &a){
        return x*a.x+y*a.y;
    }
};
int area(point a,point b,point c){
    return abs(a*b+b*c+c*a);
}
bool in(point a,point b,point c,point d){
    return area(a,b,c)==(area(a,b,d)+area(b,c,d)+area(a,c,d));
};

int n,m;
point p[maxn];
vector<pair<int,int>> res;

void add(int a,int b,int c){
    if((a<=n) == (b<=n)) res.push_back({a,b});
    if((a<=n) == (c<=n)) res.push_back({a,c});
    if((b<=n) == (c<=n)) res.push_back({b,c});
}

void dnc(int a,int b,int c,vector<int> x){
    add(a,b,c);
    int val=a^b^c;
    tie(a,b)=res.back();
    c=val^a^b;
    vector<int> nx;
    for(int i:x) if(in(p[a],p[b],p[c],p[i]) && i!=a && i!=b && i!=c) nx.push_back(i);
    if(nx.empty() || nx.back()<=n || nx[0]>n){
        for(int i:nx) add(a,c,i);
        return;
    }
    for(int i:nx){
        if((i<=n)==(c<=n)){
            dnc(a,b,i,nx);
            dnc(a,c,i,nx);
            dnc(b,c,i,nx);
            break;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> p[i].x >> p[i].y;
    cin >> m;
    for(int i=1;i<=m;i++) cin >> p[n+i].x >> p[n+i].y;
    vector<int> c(n+m);
    iota(c.begin(),c.end(),1);
    dnc(1,2,n+1,c);dnc(n+1,n+2,2,c);
    sort(res.begin(),res.end());
    res.erase(unique(res.begin(),res.end()),res.end());
    for(auto [x,y]:res){
        char k='g';
        if(x>n) x-=n,y-=n,k='r';
        cout << x << ' ' << y << ' ' << k << '\n';
    }
}
