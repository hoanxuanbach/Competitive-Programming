#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
int n,m,x,k,d,sz,pp[maxn],pd[maxn];
void f(int a,int b,int p){
    if(k==1){x+=p;return;}
    if(p<=a){
        d=(n-1)%(a+b-1)+1;k--;
        if(p+d<=a+b) f(a-1,b,p+d-1);
        else f(a-1,b,p+d-a-b);
        if(x>=p) x++;
    }
    else{
        d=(m-1)%(a+b-1)+1;k--;
        if(p+d<=a+b) f(a,b-1,p+d-1);
        else f(a,b-1,p+d-a-b);
        if(x>=p) x++;
    }
}
void solve(int a,int b,int p){
    while(k>=1){
        if(k==1){x+=p;break;}
        if(a+b<=max(n,m)){f(a,b,p);break;}
        if(p<=a){
            d=(a-p)/n+1;
            if(d>=k){x+=p+(k-1)*n;break;}
            pp[++sz]=p;pd[sz]=d;
            k-=d;p=(p+d*n-d-1)%(a+b-d)+1;a-=d;
        }
        else{
            d=(b-(p-a))/m+1;
            if(d>=k){x+=p+(k-1)*m;break;}
            pp[++sz]=-p;pd[sz]=d;
            k-=d;p=(p+d*m-1)%(a+b)+1;b-=d;
        }
    }
    while(sz>0){
        d=pd[sz];p=pp[sz];
        if(p>0){
            a+=d;
            if(x>a-d) x+=d;
            else if(x<p) x+=0;
            else if(n==1) x+=d;
            else x+=(x-p)/(n-1)+1;
        }
        else{
            b+=d;p=-p;
            if(x<p) x+=0;
            else if(m==1) x+=d;
            else x+=(x-p)/(m-1)+1;
        }
        sz--;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int a,b;
    cin >> a >> b >> n >> m >> k;solve(a,b,n);
    cout << x << '\n';
}
