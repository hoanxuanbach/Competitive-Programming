#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 400005
int d[maxn],n,t,x,y,sum,k,cnt,sx,sy;
int dx[]={0,1,0,-1},
    dy[]={1,0,-1,0};
int cal(int a,int sa,int l,int r){
    l++;
    if(sa>0){
        if(a<l) return 0;
        if(a<=r) return (a-l)/sa+1;
        else return (a-l)/sa-(a-r-1)/sa;
    }
    else{
        sa=-sa;
        if(a>r) return 0;
        if(a>=l) return (r-a)/sa+1;
        else return (r-a)/sa-(l-1-a)/sa;
    }
}
void solve(){
    int cx=0,cy=0;
    for(int i=0;i<n;i++){
        if(i%4==0){
            if(sx==0 && sy==0 && x==cx && y>cy && y<=cy+d[i]) cnt+=k;
            if(sx==0 && sy!=0 && x==cx) cnt+=cal(y,sy,cy,cy+d[i]);
            if(sx!=0 && (x-cx)%sx==0){
                int p=(x-cx)/sx;
                if(p>=0 && p<k && y-p*sy>cy && y-p*sy<=cy+d[i]) cnt++;
            }
        }
        if(i%4==1){
            if(sx==0 && sy==0 && y==cy && x>cx && x<=cx+d[i]) cnt+=k;
            if(sx!=0 && sy==0 && y==cy) cnt+=cal(x,sx,cx,cx+d[i]);
            if(sy!=0 && (y-cy)%sy==0){
                int p=(y-cy)/sy;
                if(p>=0 && p<k && x-p*sx>cx && x-p*sx<=cx+d[i]) cnt++;
            }
        }
        if(i%4==2){
            if(sx==0 && sy==0 && x==cx && y<cy && y>=cy-d[i]) cnt+=k;
            if(sx==0 && sy!=0 && x==cx) cnt+=cal(y,sy,cy-d[i]-1,cy-1);
            if(sx!=0 && (x-cx)%sx==0){
                int p=(x-cx)/sx;
                if(p>=0 && p<k && y-p*sy<cy && y-p*sy>=cy-d[i]) cnt++;
            }
        }
        if(i%4==3){
            if(sx==0 && sy==0 && y==cy && x<cx && x>=cx-d[i]) cnt+=k;
            if(sx!=0 && sy==0 && y==cy) cnt+=cal(x,sx,cx-d[i]-1,cx-1);
            if(sy!=0 && (y-cy)%sy==0){
                int p=(y-cy)/sy;
                if(p>=0 && p<k && x-p*sx<cx && x-p*sx>=cx-d[i]) cnt++;
            }
        }
        cx+=dx[i%4]*d[i];cy+=dy[i%4]*d[i];
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> t;
    for(int i=0;i<n;i++){cin >> d[i];d[n+i]=d[2*n+i]=d[3*n+i]=d[i];}
    n*=4;
    for(int i=0;i<n;i++){
        sum+=d[i]+1;
        sx+=dx[i%4]*d[i];sy+=dy[i%4]*d[i];
    }
    cin >> x >> y;
    k=t/sum;t%=sum;
    if(x==0 && y==0) cnt++;
    if(k>=1) solve();
    int cx=sx*k,cy=sy*k;
    for(int i=0;i<n;i++){
        if(i%4==0 && cx==x && y>cy && y<=cy+min(d[i],t)) cnt++;
        if(i%4==2 && cx==x && y<cy && y>=cy-min(d[i],t)) cnt++;
        if(i%4==1 && cy==y && x>cx && x<=cx+min(d[i],t)) cnt++;
        if(i%4==3 && cy==y && x<cx && x>=cx-min(d[i],t)) cnt++;
        cx+=dx[i%4]*min(d[i],t);cy+=dy[i%4]*min(d[i],t);
        t-=min(t,d[i]);
        if(t==0) break;
        else t--;
    }
    cout << cnt << '\n';
}


