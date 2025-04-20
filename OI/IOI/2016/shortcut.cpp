#include "shortcut.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 1e18;

ll find_shortcut(int n, std::vector<int> _x, std::vector<int> _d, int c)
{
    vector<ll> x(n),d(n);
    for(int i=0;i<n;i++) x[i]=(i?x[i-1]+_x[i-1]:0),d[i]=_d[i];
    auto check = [&](ll S){
        deque<int> dq;
        ll a0=-inf,a1=inf,b0=-inf,b1=inf,m0=-inf,m1=-inf,cS=S-c;
        for(int i=0;i<n;i++){
            if(m0+d[i]+x[i]>S){
                while(!dq.empty() && d[dq.front()]-x[dq.front()]+d[i]+x[i]>S){
                    int t=dq.front();dq.pop_front();
                    m1=max(m1,d[t]+x[t]);
                }
                a0=max(a0,d[i]+x[i]+m1-cS);
                a1=min(a1,cS-d[i]+x[i]-m0);
                b0=max(b0,d[i]-x[i]+m1-cS);
                b1=min(b1,cS-d[i]-x[i]-m0);
            }
            m0=max(m0,d[i]-x[i]);
            while(!dq.empty() && d[dq.back()]-x[dq.back()]<=d[i]-x[i]) dq.pop_back();
            dq.push_back(i);
        }
        //cout << a0 << ' ' << a1 << ' ' << b0 << ' ' << b1 << '\n';
        int la=0,lb=n,ra=-1,rb=n-1;
        for(int i=n-1;i>=0;i--){
            while(la<n && x[i]+x[la]<a0) la++;
            while(ra<n-1 && x[i]+x[ra+1]<=a1) ra++;
            while(lb>0 && x[i]-x[lb-1]<=b1) lb--;
            while(rb>=0 && x[i]-x[rb]<b0) rb--;
            int L=max({la,lb,i}),R=min(ra,rb);
            //cout << la << ' ' << lb << ' ' << ra << ' ' << rb << '\n';
            if(L<=R) return true;
        }
        return false;
    };
    ll l=0,r=1e16,res=r;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
