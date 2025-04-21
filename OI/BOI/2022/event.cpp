#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int maxl = 20;

int n,q,L[maxn],R[maxn],nxt[maxn][maxl];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> L[i] >> R[i];
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return R[x]<R[y];
    });
    int p=0;
    vector<int> v;
    for(int i:ord){
        while(p<n && R[ord[p]]<=R[i]){
            int id=ord[p++];
            while(!v.empty() && L[v.back()]>=L[id]) v.pop_back();
            v.push_back(id);
        }
        int l=0,r=(int)v.size();
        while(l<r){
            int m=(l+r)>>1;
            if(L[i]<=R[v[m]]) r=m;
            else l=m+1;
        }
        nxt[i][0]=(l==(int)v.size()?i:v[l]);
    }
    for(int i=1;i<18;i++) for(int j=1;j<=n;j++) nxt[j][i]=nxt[nxt[j][i-1]][i-1];
    for(int i=1;i<=q;i++){
        int x,y;cin >> x >> y;
        if(R[x]>R[y]){
            cout << "impossible\n";
            continue;
        }
        else if(R[x]>=L[y]){
            cout << (x!=y) << '\n';
            continue;
        }
        int cnt=2;
        for(int j=17;j>=0;j--){
            int k=nxt[y][j];
            if(R[x]<L[k]) cnt+=(1<<j),y=k;
        }
        y=nxt[y][0];
        if(R[x]>=L[y]) cout << cnt << '\n';
        else cout << "impossible\n";
    }
}
