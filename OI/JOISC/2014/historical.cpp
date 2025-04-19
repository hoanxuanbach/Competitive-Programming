#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxs 325
#define int long long
const int bl=315;
struct que{
    int l,r,id;
};
vector<que> query[maxs][maxs];
int n,x[maxn],num[maxn],ans[maxn];
vector<int> p;
void add(int l,int r,int id,int res){
    //cout << l << ' ' << r << ' ' << res << '\n';
    for(int i=l;i<=r;i++){
        if(i%bl==0 && i+bl-1<=r) i+=bl-1;
        else{
            num[x[i]]++;
            res=max(res,num[x[i]]*p[x[i]]);
        }
    }
    for(int i=l;i<=r;i++){
        if(i%bl==0 && i+bl-1<=r) i+=bl-1;
        else num[x[i]]--;
    }
    ans[id]=res;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int q;cin >> n >> q;
    for(int i=1;i<=n;i++){cin >> x[i];p.push_back(x[i]);}
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    for(int i=1;i<=n;i++) x[i]=lower_bound(p.begin(),p.end(),x[i])-p.begin();
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        int down=(l-1)/bl+1,up=(r+1)/bl-1;
        if(down>up) add(l,r,i,0);
        else query[down][up].push_back({l,r,i});
    }
    for(int i=0;i<=n/bl;i++){
        for(int j=0;j<(int)p.size();j++) num[j]=0;
        int res=0;
        for(int j=i;j<=n/bl;j++){
            for(int k=max(1LL,j*bl);k<=min(n,j*bl+bl-1);k++){
                num[x[k]]++;
                res=max(res,p[x[k]]*num[x[k]]);
            }
            for(que v:query[i][j]) add(v.l,v.r,v.id,res);
        }
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}
