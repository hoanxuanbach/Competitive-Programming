#include "gondola.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 250005;
const int mod=1e9+9;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}

map<int,int> cnt;

int valid(int n, int p[])
{
    int del=-1;
    for(int i=0;i<n;i++){
        if(cnt[p[i]]) return 0;
        cnt[p[i]]++;
        if(p[i]<=n){
            int cur=(i-p[i]+n)%n;
            if(del==-1) del=cur;
            else if(del!=cur) return 0;
        }
    }
    return 1;
}

//----------------------

int replacement(int n, int p[], int res[])
{
    int del=0,sz=0;
    for(int i=0;i<n;i++) if(p[i]<=n) del=(i-p[i]+1+n)%n;
    deque<int> dq(n);
    for(int i=0;i<n;i++) dq[i]=p[i];
    while(del){
        del--;
        dq.push_back(dq.front());
        dq.pop_front();
    }
    vector<pii> pp;
    for(int i=0;i<n;i++) if(dq[i]>n) pp.push_back({dq[i],i});
    sort(pp.begin(),pp.end());
    int pre=n;
    for(auto &[x,id]:pp){
        res[sz++]=id+1;pre++;
        while(pre<x) res[sz++]=pre++;
    }
    return sz;
}

//----------------------

int countReplacement(int n, int p[])
{
    if(!valid(n,p)) return 0;
    vector<int> pp;
    int res=n,cnt=n;
    for(int i=0;i<n;i++){
        if(p[i]<=n) res=1,cnt--;
        else pp.push_back(p[i]);
    }
    int pre=n;
    sort(pp.begin(),pp.end());
    for(int x:pp){
        res=1LL*res*power(cnt,x-pre-1)%mod;
        pre=x;cnt--;
    }
    return res;
}
