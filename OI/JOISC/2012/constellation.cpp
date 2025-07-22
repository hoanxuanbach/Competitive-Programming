#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

struct point{
    int x,y,c;
    bool operator<(const point p)const{return (x!=p.x?x<p.x:y<p.y);}
    point operator-(point p){return {x-p.x,y-p.y};}
};
int n;
point p[maxn];
int cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
int ori(point a,point b,point c){
    return cross(b-a,c-a);
}
void solve(){
    int n,cnt=0,all=0;cin >> n;
    for(int i=1;i<=n;i++) cin >> p[i].x >> p[i].y >> p[i].c,all|=(1<<p[i].c),cnt+=(!p[i].c);
    sort(p+1,p+n+1);

    int del=0;
    if(!(all>>1&1)) del++;
    if(!(all>>2&1)) del++; 

    point st=p[1],en=p[n];
    vector<point> up,down;
    up.push_back(st);down.push_back(st);
    for(int i=2;i<=n;i++){
        int o=ori(st,en,p[i]);
        if(o>=0){
            while((int)up.size()>=2 && ori(up.back(),p[i],up[(int)up.size()-2])>=0) up.pop_back();
            up.push_back(p[i]);
        }
        if(o<=0){
            while((int)down.size()>=2 && ori(down.back(),p[i],down[(int)down.size()-2])<=0) down.pop_back();
            down.push_back(p[i]);
        }
    }
    for(int i=(int)up.size()-2;i>=1;i--) down.push_back(up[i]);

    vector<point> cht=down;
    for(auto [x,y,c]:cht) cnt-=(!c);
    int sz=(int)cht.size(),res=0;

    vector<int> pos;
    for(int i=0;i<sz;i++){
        if(cht[i].c) pos.push_back(i);
        //cout << cht[i].c << ' ';
    }
    if(pos.empty()) res=(sz*(sz-1)+2)%mod;
    else{
        pos.push_back(pos[0]+sz);
        int ss=(int)pos.size();

        int diff=0;
        for(int i=1;i<ss;i++) if(cht[pos[i-1]].c!=cht[pos[i]%sz].c) diff++;
        if(diff<=2){
            res=1;
            for(int i=1;i<ss;i++){
                int d=pos[i]-pos[i-1];
                //cout << d << '\n';
                if(!diff) res=(res+d*(d-1)/2)%mod;
                else if(cht[pos[i-1]].c!=cht[pos[i]%sz].c) res=res*d%mod;
            }
            //cout << diff << ' ' << res << '\n';
        }
    }
    res=(res*power(2,cnt)+mod-del)%mod;
    cout << res << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
4
1 1 1
2 1 1
1 2 0
2 2 2
*/