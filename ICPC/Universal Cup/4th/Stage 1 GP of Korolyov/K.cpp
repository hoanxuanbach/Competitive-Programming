#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e9;
const int LG = 20;

void solve(){
    int n,q,d;cin >> n >> q >> d;

    vector<int> a(n+1),p(n+1),b(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],p[i]=p[i-1]+a[i];
    for(int i=1;i<=n;i++) b[i]=p[i]+a[i];

    vector<vector<int>> mn(n+1,vector<int>(LG,0)),mx(n+1,vector<int>(LG,0));

    for(int i=1;i<=n;i++) mn[i][0]=a[i],mx[i][0]=b[i];
    for(int j=1;j<LG;j++){
        for(int i=0;i<=n+1-(1<<j);i++){
            mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
            mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
        }
    }
    auto querya = [&](int i,int x){
        for(int j=LG-1;j>=0;j--){
            if(i+(1<<j)>n+1) continue;
            if(mn[i][j]>x) i+=(1<<j); 
        }
        return i;
    };
    auto queryb = [&](int i,int x){
        for(int j=LG-1;j>=0;j--){
            if(i+(1<<j)>n+1) continue;
            if(mx[i][j]<=x) i+=(1<<j); 
        }
        return i;
    };


    function<int(int,int)> get = [&](int i,int x){
        if(i==n+1) return i;
        if(x>=a[i] && x<2*a[i]) return i; 
        if(x>=2*a[i]){
            int j=queryb(i,p[i-1]+x);
            return get(j,x-(p[j-1]-p[i-1]));
        }
        else{
            int j=querya(i,x);
            return get(j,x);
        }
    };  

    vector<int> nxt(n+1,n+1);
    for(int i=1;i<=n;i++) if(a[i]) nxt[i]=get(i,a[i]-1);

    vector<vector<int>> jmp(n+2,vector<int>(LG,n+1));
    for(int i=1;i<=n;i++) jmp[i][0]=nxt[i];
    for(int j=1;j<LG;j++) for(int i=1;i<=n;i++) jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    for(int i=0;i<q;i++){
        int l,r,x=d;cin >> l >> r;
        
        
        int nl=get(l,x);
        if(nl<=r){
            l=nl;
            for(int j=LG-1;j>=0;j--){
                if(jmp[l][j]<=r) l=jmp[l][j];
            }
            x=a[l]-1;
            l++;
        }

        while(l<=r){
            if(x>=2*a[l]){
                nl=queryb(l,p[l-1]+x);

                if(nl>r) x-=p[r]-p[l-1],l=r+1;
                else x-=(p[nl-1]-p[l-1]),l=nl;
            }
            else{

                nl=querya(l,x);
                l=nl;
            }
        }

        cout << x << '\n';
    }
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}