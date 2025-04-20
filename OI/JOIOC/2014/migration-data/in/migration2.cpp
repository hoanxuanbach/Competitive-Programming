#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define mpp make_pair
#define fi first
#define se second
const int maxn = 120005;
const int LOG = 18;

int f(int x){
    return (x?32-__builtin_clz(x):0);
}
int n,m,q,a[maxn];
char s[maxn];

vector<pii> T[4*maxn];
void build(int l,int r,int id){
    if(l==r){
        int x=a[l];
        if(x==n) T[id]={{n-1,0},{n,-1}};
        else if(n-x-1<x-1) T[id]={{n-x-1,x+1},{x-1,x-n},{n,x-n-1}};
        else T[id]={{x-1,x+1},{n-x,x},{n,x-n-1}};
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    int lt=0;
    for(auto [rt,val]:T[id<<1]){
        int pl=lower_bound(T[id<<1|1].begin(),T[id<<1|1].end(),mpp(lt+val,INT_MIN))-T[id<<1|1].begin();
        int pr=lower_bound(T[id<<1|1].begin(),T[id<<1|1].end(),mpp(rt+val,INT_MIN))-T[id<<1|1].begin();
        for(int i=pl;i<=pr;i++){
            auto [lst,nval]=T[id<<1|1][i];
            int pos=min(lst-val,rt);
            T[id].push_back({pos,val+nval});
        }
        lt=rt+1;
    }
}
int query(int l,int r,int id,int tl,int tr,int t){
    if(tr<l || r<tl) return t;
    if(tl<=l && r<=tr){
        auto it=lower_bound(T[id].begin(),T[id].end(),mpp(t,INT_MIN));
        return t+it->se;
    }
    int mid=(l+r)>>1;
    return query(mid+1,r,id<<1|1,tl,tr,query(l,mid,id<<1,tl,tr,t));
}



int nxt[LOG][LOG][maxn],cnt[maxn];
ll ca[LOG][maxn],cb[LOG][maxn];
int pa[maxn],sa,pb[maxn],sb;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> s[i];
    for(int i=1;i<=m;i++) cin >> a[i];
    for(int i=1;i<=n+1;i++) if(s[i]!='R') pa[++sa]=i-1;
    for(int i=n;i>=0;i--) if(s[i]!='B') pb[++sb]=n-i;
    for(int i=1;i<=n;i++) cnt[i]=cnt[i-1]+(s[i]=='B');
    for(int x=0;x<LOG;x++){
        int X=(x?(1<<(x-1)):0);
        for(int y=0;y<LOG;y++){
            int Y=(y?(1<<(y-1)):0);
            nxt[x][y][m+1]=m+1;
            for(int i=m;i>=1;i--) nxt[x][y][i]=(X<a[i] && a[i]<=n-Y)?i:nxt[x][y][i+1];
        }
        for(int i=1;i<=m;i++){
            ca[x][i]=(a[i]<=X?a[i]:0)+ca[x][i-1];
            cb[x][i]=(a[i]>n-X?n-a[i]:0)+cb[x][i-1];
        }
    }
    build(1,m,1);
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        int ta=1,tb=1,t=-1;
        while(true){
            auto g = [&](int x){
                if(x<=pa[ta]) return 0;
                else if(x>n-pb[tb]) return 1;
                else return (int)(s[x]=='B');
            };
            int xa=f(pa[ta]),xb=f(pb[tb]);
            int i=min(nxt[xa][xb][l],r+1);
            int da=min(ca[xa][i-1]-ca[xa][l-1],1LL*n);
            int db=min(cb[xb][i-1]-cb[xb][l-1],1LL*n);
            //cout << i << ' ' << da << ' ' << db << ' ' << pa[ta] << ' ' << pb[tb] << '\n';
            if(pa[min(sa,ta+da)]+pb[min(sb,tb+db)]<n){
                ta+=da,tb+=db;
                if(i==r+1) break;
                int bc=cnt[n-pb[tb]]-cnt[pa[ta]]+pb[tb],x=a[i]+g(a[i]);
                //cout << x << ' ' << bc << '\n';
                if(x<=bc){
                    if(x>=bc-pb[tb]){t=n-bc+x,l=i+1;break;}
                    else ta+=x;
                }
                else{
                    x=n-a[i]+(g(a[i])^1);
                    if(x>=n-bc-pa[ta]){
                        t=n-bc-x,l=i+1;
                        break;
                    }
                    else tb+=x;
                }
            }
            else{
                int lt=l,rt=i-1;
                while(lt<rt){
                    int mid=(lt+rt)>>1;
                    int da=min(ca[xa][mid]-ca[xa][l-1],1LL*n);
                    int db=min(cb[xb][mid]-cb[xb][l-1],1LL*n);
                    if(pa[min(sa,ta+da)]+pb[min(sb,tb+db)]<n) lt=mid+1;
                    else rt=mid;
                }
                int da=min(ca[xa][lt-1]-ca[xa][l-1],1LL*n);
                int db=min(cb[xb][lt-1]-cb[xb][l-1],1LL*n);
                ta+=da;tb+=db;l=lt+1;
                int bc=cnt[n-pb[tb]]-cnt[pa[ta]]+pb[tb],x=a[lt]+g(a[lt]);
                if(x<=bc) t=n-bc+x;
                else t=n-bc-(n-a[lt]+(g(a[lt])^1));
                break;
            }
            l=i+1;
        }
        //cout << t << ' ' << pb[tb] << ' ' << pa[ta] << '\n';
        if(t==-1) cout << n-pb[tb]-(cnt[n-pb[tb]]-cnt[pa[ta]]) << '\n';
        else cout << ((l<=r)?query(1,m,1,l,r,t):t) << '\n';
    }
}

