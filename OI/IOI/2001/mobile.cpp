#include<bits/stdc++.h>
using namespace std;
const int maxn = 1030;
int S,a[maxn][maxn];

void update(int x,int y,int val){
    for(int i=x;i<=S;i+=(i&(-i))) for(int j=y;j<=S;j+=(j&(-j))) a[i][j]+=val;
}
int query(int x,int y){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) for(int j=y;j>=1;j-=(j&(-j))) res+=a[i][j];
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> S >> S;
    while(true){
        int id;cin >> id;
        if(id==3) break;
        if(id==1){
            int x,y,val;cin >> x >> y >> val;
            update(x+1,y+1,val);
        }
        else{
            int x,y,u,v;cin >> x >> y >> u >> v;
            cout << (query(u+1,v+1)-query(x,v+1)-query(u+1,y)+query(x,y)) << '\n';
        }
    }
}
