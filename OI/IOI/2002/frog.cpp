#include<bits/stdc++.h>
using namespace std;
const int maxn = 5005;
int n,m,k;
bool f[maxn][maxn];
pair<int,int> p[maxn];

bool outside(int x,int y){
    return (x<=0 || y<=0 || x>n || y>m);
}

signed main(){
    cin >> n >> m >> k;
    for(int i=1;i<=k;i++) cin >> p[i].first >> p[i].second;
    sort(p+1,p+k+1);
    for(int i=1;i<=k;i++) f[p[i].first][p[i].second]=i;
    int res=0;
    for(int i=1;i<=k;i++) for(int j=i+1;j<=k;j++){
        int cnt=2,x=p[j].first,y=p[j].second;
        int dx=x-p[i].first,dy=y-p[i].second;
        if(!outside(p[i].first-dx,p[i].second-dy)) continue;
        while(!outside(x+dx,y+dy)){
            if(!f[x+dx][y+dy]){
                cnt=-1;
                break;
            }
            x+=dx,y+=dy;cnt++;
        }
        if(cnt>2) res=max(res,cnt);
    }
    cout << res << '\n';
}