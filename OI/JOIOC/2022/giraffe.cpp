#include<bits/stdc++.h>
using namespace std;
const int maxn = 8005;
const int S = 600;
int n,p[maxn],s[maxn][4];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i];
        s[i][0]=min(n-i,n-p[i]);
        s[i][1]=min(i-1,n-p[i]);
        s[i][2]=min(n-i,p[i]-1);
        s[i][3]=min(i-1,p[i]-1);
    }
    int k=0;
    while(true){
        vector<array<int,3>> sq;
        for(int i=1;i<=n;i++) for(int j=0;j<=3;j++) if(s[i][j]!=-1) sq.push_back({-s[i][j],i,j}),s[i][j]=-1;
        if(sq.empty()) break;
        sort(sq.begin(),sq.end());
        if((int)sq.size()>S) sq.erase(sq.begin()+S,sq.end());
        for(auto [d,i,j]:sq){
            d=-d;
            int x=-1,y=-1,u=-1,v=-1;
            if(j&1) x=i-d,u=i-1;
            else x=i+1,u=i+d;
            if(j&2) y=p[i]-d,v=p[i]-1;
            else y=p[i]+1,v=p[i]+d;
            for(int t=x;t<=u;t++){
                if(p[t]<y || p[t]>v) continue;
                s[t][0]=max(s[t][0],min(u-t,v-p[t]));
                s[t][1]=max(s[t][1],min(t-x,v-p[t]));
                s[t][2]=max(s[t][2],min(u-t,p[t]-y));
                s[t][3]=max(s[t][3],min(t-x,p[t]-y));
            }
        }
        k++;
    }
    cout << n-k << '\n';
}
