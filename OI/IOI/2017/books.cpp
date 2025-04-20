#include "books.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int f[maxn],lt[maxn],rt[maxn],L,R;

void g(int &l,int &r){
    int cl=min(lt[f[r]],lt[f[l]]),cr=max(rt[f[r]],rt[f[l]]);
    while(l>cl || r<cr){
        if(l>cl){
            cl=min(cl,lt[f[--l]]);
            cr=max(cr,rt[f[l]]);
        }
        else{
            cl=min(cl,lt[f[++r]]);
            cr=max(cr,rt[f[r]]);
        }
    }
}

long long minimum_walk(std::vector<int> p, int s) {
    long long ans=0;
    int n=(int)p.size(),cnt=0;
    L=s,R=s;
    for(int i=0;i<n;i++){
        if(!f[i]){
            cnt++;
            int u=i,mn=i,mx=i;
            while(!f[u]){
                f[u]=cnt;
                mn=min(mn,u);
                mx=max(mx,u);
                u=p[u];
            }
            lt[cnt]=mn;
            rt[cnt]=mx;
            if(p[i]!=i) L=min(L,mn),R=max(R,mx);
        }
        ans+=abs(i-p[i]);
    }
    int l=s,r=s;
    while(true){
        g(l,r);
        int al=l,ar=r,bl=l,br=r,ac=0,bc=0;
        while(al>L && ar==r) g(--al,ar),ac+=2;
        while(br<R && bl==l) g(bl,++br),bc+=2;
        //cout << al << ' ' << ar << ' ' << bl << ' ' << br << '\n';
        if(ar==r){ans+=ac+bc;break;}
        ans+=min(ac,bc);l=al,r=ar;
    }
    return ans;
}
