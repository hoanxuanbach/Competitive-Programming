#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;
int n,d[maxn][maxn];

signed main(){
    cin >> n;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            char c;cin >> c;
            d[i][j]=d[j][i]=(c=='R');
        }
    }
    for(int i=1;i<=n;i++){
        deque<int> dq;
        for(int t=1;t<=n;t++){
            int j=t+(t>=i);
            if(j>n) j=i;
            if((int)dq.size()<=1) dq.push_back(j);
            else{
                int x=dq.back(),y=dq.end()[-2],a=dq[0],b=dq[1];
                int lt=d[a][b],rt=d[x][y];
                if(lt==rt) lt^=1;

                if(rt==d[x][j]) dq.push_back(j);
                else if(lt==d[a][j]) dq.push_front(j);
                else if(d[a][x]==lt){
                    dq.pop_back();
                    dq.push_front(x);
                    dq.push_front(j);
                }
                else{
                    dq.pop_front();
                    dq.push_back(a);
                    dq.push_back(j);
                }
            }
        }
        if(dq.back()==i) reverse(dq.begin(),dq.end());
        cout << (int)dq.size() << '\n';
        for(int x:dq) cout << x << ' ';
        cout << '\n';
    }
}