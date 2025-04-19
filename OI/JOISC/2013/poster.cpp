#include<bits/stdc++.h>
using namespace std;
#define maxn 55
#define int long long
int n,w,h,x[maxn],y[maxn],num=0;
int dist(int i,int j){
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
bool check(int i,int j,int k,int l){
    double r1=dist(i,j),r2=dist(k,l),d=dist(i,k);
    if(x[i]*x[i]<r1 || (w-x[i])*(w-x[i])<r1) return false;
    if(x[k]*x[k]<r2 || (w-x[k])*(w-x[k])<r2) return false;
    if(y[i]*y[i]<r1 || (h-y[i])*(h-y[i])<r1) return false;
    if(y[k]*y[k]<r2 || (h-y[k])*(h-y[k])<r2) return false;
    if(r1<r2) return false;
    if(r1+r2-d<=0) return false;
    int x=(r1+r2-d)*(r1+r2-d);
    if(x>4*r1*r2) return true;
    return false;
}
signed main(){
    cin >> n >> w >> h;
    for(int i=1;i<=n;i++) cin >> x[i] >> y[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            for(int k=1;k<=n;k++){
                if(k==i || k==j) continue;
                for(int l=1;l<=n;l++){
                    if(l==i || l==k || l==j) continue;
                    if(check(i,j,k,l)) num++;
                }
            }
        }
    }
    cout << num << '\n';
}
