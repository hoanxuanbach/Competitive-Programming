#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n,m;
int na[maxn],nb[maxn],nc[maxn];
int ma[maxn],mb[maxn],mc[maxn];
map<string,int> mn,mm;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        string a,b,c,op;
        cin >> a >> op >> b >> op >> c;
        na[i]=mn[a];mn[a]=2*i+1;
        nb[i]=mn[b];mn[b]=2*i+2;
        nc[i]=mn[c];mn[c]=2*i+2;
        if(nb[i]>nc[i]) swap(nb[i],nc[i]);
    }
    for(int i=0;i<m;i++){
        string a,b,c,op;
        cin >> a >> op >> b >> op >> c;
        ma[i]=mm[a];mm[a]=2*i+1;
        mb[i]=mm[b];mm[b]=2*i+2;
        mc[i]=mm[c];mm[c]=2*i+2;
        if(mb[i]>mc[i]) swap(mb[i],mc[i]);
        //cout << ma[i] << ' ' << mb[i] << ' ' << mc[i] << '\n';
    }
    int res=0;
    for(int k=-(n-1);k<m;k++){
        //cout << '*' << d << endl;
        for(int i=max(0,-k);i<min(n,m-k);i++){
            int j=i+k,p=i;
            //cout << i << ' ' << j << endl;
            while(p<min(n,m-k)){
                int a=max(i*2,na[p])-i*2,b=max(i*2,nb[p])-i*2,c=max(i*2,nc[p])-i*2;
                int d=max(j*2,ma[p+k])-j*2,e=max(j*2,mb[p+k])-j*2,f=max(j*2,mc[p+k])-j*2;
                if(a!=d || b!=e || c!=f) break;
                p++;
            }
            res=max(res,p-i);
        }
    }
    cout << res << '\n';
}
