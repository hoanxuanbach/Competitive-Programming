#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
const int maxn = 5e5+5;
template<class T>
struct point{
    T x=-1,y=-1;
    point(T x=-1,T y=-1):x(x),y(y){}
    point operator-(point &a){
        return point(x-a.x,y-a.y);
    }
    point operator+(point &a){
        return point(x+a.x,y+a.y);
    }
    T cross(point &a){
        return x*a.y-y*a.x;
    }
};
struct line{
    int a=0,b=0,c=0;
    line(){}
    line(point<int> p,point<int> q){
        a=q.y-p.y;
        b=p.x-q.x;
        c=p.y*q.x-p.x*q.y;
        int g=__gcd(a,__gcd(b,c));
        a/=g;b/=g;c/=g;
    };
};
int N,R,c[4][maxn];
point<int> S;
vector<point<int>> P;
const double eps = 1e-6;

pair<int,double> get(point<int> p,point<int> q){
    line L(p,q);
    //cout << p.x << ' ' << p.y << ' ' << q.x << ' ' << q.y << '\n';
    //cout << L.a << ' ' << L.b << ' ' << L.c << '\n';
    for(int i=0;i<4;i++){
        point<double> T;
        if(P[i].x==-1){
            if(L.a==0) continue;
            T.y=P[i].y;
            T.x=(double)(-L.c-L.b*T.y)/L.a;
            //cout << T.x << ' ' << T.y << '\n';
            if((P[i].y<p.y)==(q.y>p.y)) continue;
        }
        else{
            if(L.b==0) continue;
            T.x=P[i].x;
            T.y=(double)(-L.c-L.a*T.x)/L.b;
            //cout << T.x << ' ' << T.y << '\n';
            if((P[i].x<p.x)==(q.x>p.x)) continue;
        }
        if(T.x<-eps || T.y<-eps || T.x>N+eps || T.y>N+eps) continue;
        //cout << "****" << i << ' ' << T.x << ' ' << T.y << '\n';
        if(P[i].x==-1) return {i,T.x};
        else return {i,T.y};
    }
    return {-1,-1};
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> R >> S.x >> S.y;
    P={{-1,0},{N,-1},{-1,N},{0,-1}};
    for(int i=1;i<=R;i++){
        int k;cin >> k;
        vector<point<int>> p(k);
        for(int j=0;j<k;j++){
            cin >> p[j].x >> p[j].y;
            p[j]=p[j]-S;
        }
        point<int> lt=p[0],rt=p[0];
        for(int j=1;j<k;j++){
            if(rt.cross(p[j])>0) rt=p[j];
            if(p[j].cross(lt)>0) lt=p[j];
        }
        lt=lt+S;rt=rt+S;
        //cout << lt.x << ' ' << lt.y << ' ' << rt.x << ' ' << rt.y << '\n';
        pair<int,double> L=get(S,lt),R=get(S,rt);
        //cout << L.fi << ' ' << L.se << ' ' << R.fi << ' ' << R.se << '\n';
        if(L.fi!=R.fi){
            for(int j=(L.fi+1)%4;j!=R.fi;j=(j+1)%4){
                c[j][0]++;c[j][N+1]--;
            }
            if(L.fi<=1){
                int lt=ceil(L.se);
                c[L.fi][lt]++;c[L.fi][N+1]--;
            }
            else{
                int rt=floor(L.se);
                c[L.fi][0]++;c[L.fi][rt+1]--;
                //cout << 0 << ' ' << rt << '\n';
            }
            if(R.fi<=1){
                int rt=floor(R.se);
                c[R.fi][0]++;c[R.fi][rt+1]--;
                //cout << 0 << ' ' << rt << '\n';
            }
            else{
                int lt=ceil(R.se);
                c[R.fi][lt]++;c[R.fi][N+1]--;
            }
        }
        else{
            int id=L.fi;
            if(id<=1){
                int lt=ceil(L.se);
                int rt=floor(R.se);
                c[id][lt]++;c[id][rt+1]--;
                //cout << lt << ' ' << rt << '\n';
            }
            else{
                int rt=floor(L.se);
                int lt=ceil(R.se);
                c[id][lt]++;c[id][rt+1]--;
                //cout << lt << ' ' << rt << '\n';
            }
        }
    }
    int cnt=0;
    for(int i=0;i<4;i++) for(int j=1;j<=N;j++) c[i][j]+=c[i][j-1];
    for(int i=0;i<4;i++){
        for(int j=1;j<N;j++) cnt+=!c[i][j];
    }
    cnt+=(!c[0][N] && !c[1][0]);
    cnt+=(!c[1][N] && !c[2][N]);
    cnt+=(!c[2][0] && !c[3][N]);
    cnt+=(!c[3][0] && !c[0][0]);
    cout << cnt << '\n';
}
