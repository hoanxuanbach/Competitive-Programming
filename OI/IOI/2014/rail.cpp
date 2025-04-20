#include "rail.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+5;
#define pii pair<int,int>
#define fi first
#define se second
pii a[maxn];

void findLocation(int N, int S, int P[], int T[])
{
    map<int,int> mp;
    P[0]=S;T[0]=1;
    mp[S]=0;
    for(int i=1;i<N;i++) a[i]={getDistance(0,i),i};
    sort(a+1,a+N);
    int l=0,r=a[1].se;
    P[r]=S+a[1].fi;T[r]=2;
    mp[P[r]]=r;
    for(int i=2;i<N;i++){
        int x=a[i].se;
        int dl=getDistance(l,x),dr=getDistance(r,x);
        int m=(P[l]+dl+P[r]-dr)/2;
        T[x]=(mp.find(m)==mp.end()?(m>S?2:1):(T[mp[m]]^3));
        if(T[x]==2){
            P[x]=P[l]+dl;
            if(P[x]>P[r]) r=x;
        }
        else{
            P[x]=P[r]-dr;
            if(P[x]<P[l]) l=x;
        }
        mp[P[x]]=x;
    }
}
