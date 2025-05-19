#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
const int inf = 9e18;
const int maxn = 200005;
const int mod = 1000000000169;
const int base = 101;
 
int rand(int l,int r){
    return l+rng()%(r-l+1);
}
 
//100000000069,1000000000169
 
int res=0;
int n,a[maxn],fh[maxn];
int cnt[maxn],pos[maxn],cur[maxn];
int pw[maxn];
 
vector<int> g[maxn];
 
int lmx[maxn],rmx[maxn],lc[maxn],rc[maxn],lim[maxn];
int lh[maxn],rh[maxn],ls[maxn],rs[maxn],lms[maxn];
 
int bit[maxn],nxt[maxn];
void update(int x,int val){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]=(val==1?max(bit[i],x):0);
}
int query(int x){
    int mx=0;
    for(int i=x;i>=1;i-=(i&(-i))) mx=max(mx,bit[i]);
    return mx;
}
 
void dnc(int l,int r){
    if(l==r){
        res++;
        return;
    }
    int mid=(l+r)>>1;
    dnc(l,mid);dnc(mid+1,r);
 
    //S(l->r): the set of different number from l to r
    
    //cerr << "start " << l << ' ' << r << ' ' << res << '\n';
 
    {//merge (l->mid) and (mid+1->r) that S(l->mid)=S(mid+1->r)
 
 
        int h=0,x=0;
 
        map<pair<int,int>,int> mp;
        for(int i=mid+1;i<=r;i++){
            int lt=query(a[i]-1),rt=0;
 
            if(!pos[a[i]]){
                update(a[i],1);
                nxt[a[i]]=nxt[lt],nxt[lt]=a[i];
                rt=nxt[a[i]];
 
                cnt[a[i]]=1;
                pos[a[i]]=i;
                h^=fh[a[i]];
 
                if(lt && rt) x=(x-(cnt[rt]-cnt[lt]+n)*pw[rt]%mod+mod)%mod;
                if(lt) x=(x+(cnt[a[i]]-cnt[lt]+n)*pw[a[i]])%mod;
                if(rt) x=(x+(cnt[rt]-cnt[a[i]]+n)*pw[rt])%mod;
            }
            else{
                cnt[a[i]]++;
                rt=nxt[a[i]];
                if(lt) x=(x+pw[a[i]])%mod;
                if(rt) x=(x-pw[rt]+mod)%mod;
            }
 
            //cerr << "right " << i << ' ' << lt << ' ' << rt << ' ' << h << ' ' << x << '\n';
            mp[{h,x}]++;
            //cerr << "cl " << h << ' ' << x << '\n';
        }
        
        nxt[0]=0;
        for(int i=mid+1;i<=r;i++) if(pos[a[i]]==i) update(a[i],-1),nxt[a[i]]=0;
        h=x=0;
 
        for(int i=mid;i>=l;i--){
            int lt=query(a[i]-1),rt=0;
 
            if(pos[a[i]]<=n){
                update(a[i],1);
                nxt[a[i]]=nxt[lt],nxt[lt]=a[i];
                rt=nxt[a[i]];
 
                cnt[a[i]]=1;
                pos[a[i]]=n+i;
                h^=fh[a[i]];
 
                if(rt && lt) x=(x-(cnt[lt]-cnt[rt]+n)*pw[rt]%mod+mod)%mod;
                if(lt) x=(x+(cnt[lt]-cnt[a[i]]+n)*pw[a[i]])%mod;
                if(rt) x=(x+(cnt[a[i]]-cnt[rt]+n)*pw[rt])%mod;
            }
            else{
                cnt[a[i]]++;
                rt=nxt[a[i]];
 
                if(rt) x=(x+pw[rt])%mod;
                if(lt) x=(x-pw[a[i]]+mod)%mod;
            }
            //cerr << "left " << i << ' ' << lt << ' ' << rt << ' ' << h << ' ' << x << '\n';
 
            res+=mp[{h,x}];
            //cerr << "cr " << h << ' ' << x << '\n';
        }
 
        nxt[0]=0;
        for(int i=mid;i>=l;i--) if(pos[a[i]]==n+i) update(a[i],-1),nxt[a[i]]=0;
        
        for(int i=l;i<=r;i++) cnt[a[i]]=pos[a[i]]=0;
    }
    
    //cerr << "first " << res << '\n';
 
    {//build hash
 
        for(int i=mid+1;i<=r;i++){
            rmx[i]=rmx[i-1],rs[i]=rs[i-1],rc[i]=rc[i-1];
            rh[i]=(rh[i-1]+pw[a[i]])%mod;
            if(!pos[a[i]]){
                pos[a[i]]=i,rc[i]++;
                rs[i]=(rs[i]+pw[a[i]])%mod;
            }
            cnt[a[i]]++;
            if(cnt[a[i]]>rmx[i]) rmx[i]=cnt[a[i]];
        }
 
        for(int i=mid+1;i<=r;i++) cnt[a[i]]=0;
 
        lim[mid+1]=r+1;
        for(int i=mid;i>=l;i--){
            lmx[i]=lmx[i+1],ls[i]=ls[i+1],lc[i]=lc[i+1],lim[i]=lim[i+1],lms[i]=lms[i+1];
            lh[i]=(lh[i+1]+pw[a[i]])%mod;
            if(!cur[a[i]]){
                cur[a[i]]=i,lc[i]++;
                ls[i]=(ls[i]+pw[a[i]])%mod;
            }
            cnt[a[i]]++;
            if(cnt[a[i]]>lmx[i]){
                lmx[i]=cnt[a[i]],lim[i]=(pos[a[i]]?pos[a[i]]:r+1);
                lms[i]=pw[a[i]];
            }
            else if(cnt[a[i]]==lmx[i]){
                lim[i]=min(lim[i],(pos[a[i]]?pos[a[i]]:r+1));
                lms[i]=(lms[i]+pw[a[i]])%mod;
            }
        }
        lim[mid+1]=0;
        for(int i=l;i<=mid;i++) cnt[a[i]]=cur[a[i]]=0;
        for(int i=mid+1;i<=r;i++) pos[a[i]]=0;
    }
 
 
 
    {//merge (l->mid) and (mid+1->r) that only one side has the different elements from another side
        
        //l-mid has different elements
        for(int i=l;i<=mid;i++){
            int rt=mid+lc[i]*lmx[i]-(mid+1-i);
            if(rt>r || rt<=mid) continue;
            //cerr << "lt " << i << ' ' << rt << ' ' << lmx[i] << '\n';
            int val=(lh[i]+rh[rt]-lmx[i]*ls[i]%mod+mod)%mod;
            if(!val) res++;
        }
 
        //mid+1->r has different elements
        for(int i=mid+1;i<=r;i++){
            int lt=mid+1-(rc[i]*rmx[i]-(i-mid));
            if(lt<l || lt>mid) continue;
            //cerr << "rt " << i << ' ' << lt << '\n';
            int val=(rh[i]+lh[lt]-rmx[i]*rs[i]%mod+mod)%mod;
            if(!val) res++;
        }
    }
 
    //cerr << "second " << res << '\n';
 
    {//merge (l->mid) and(mid+1->r) that both sides have different elements
        map<pair<int,int>,int> mp;
        for(int i=l;i<=mid;i++){
            //cout << "lim " << i << ' ' << lim[i] << '\n';
            g[lim[i]-1].push_back(i);
        }
        for(int rt=mid+1;rt<=r;rt++){
            int val=(rmx[rt]*rs[rt]-rh[rt]+mod)%mod;
            mp[{rmx[rt],val}]++;
 
            for(int i:g[rt]){
                val=(lh[i]-lmx[i]*lms[i]%mod+mod)%mod;
                res+=mp[{lmx[i],val}];
            }
        }
        for(int i=mid;i<=r;i++) g[i].clear();
    }
    
 
    for(int i=l;i<=mid;i++) lmx[i]=lim[i]=lc[i]=lh[i]=ls[i]=lms[i]=0;
    for(int i=mid+1;i<=r;i++) rmx[i]=rc[i]=rh[i]=rs[i]=0;
    //cerr << "dnc " << l << ' ' << r << ' ' << res << "\n\n";
 
}
 
void solve(){
    auto st = clock();
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) fh[i]=rand(1,inf);
 
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*base%mod;
    dnc(1,n);
 
    cout << res << '\n';
    cerr << clock()-st << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
