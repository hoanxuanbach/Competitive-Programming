#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define int long long

int n,q;

struct BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}c0,c1;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++) c0.update(i,1),c1.update(i,1);
    vector<array<int,3>> a;
    for(int i=1;i<=q;i++){
        int x,d,w;cin >> x >> d >> w;w*=2;
        a.push_back({x,d,w});
    }
    reverse(a.begin(),a.end());
    for(auto [x,d,w]:a){
        if(d==1){
            int l=1,r=n;
            while(l<r){
                int m=(l+r+1)>>1;
                if(c0.query(m)<=x) l=m;
                else r=m-1;
            }
            if(c0.query(l)<=x) c1.update(1,-w),c1.update(l+1,w);
        }
        else{
            int l=1,r=n;
            while(l<r){
                int m=(l+r)>>1;
                if(c1.query(m)>x) r=m;
                else l=m+1;
            }
            if(c1.query(l)>x) c0.update(l,w);
        }
    }
    for(int i=1;i<=n;i++) cout << (c0.query(i)-c1.query(i))/2 << '\n';
}
