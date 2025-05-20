#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
const int inf = 9e18;
const int maxn = 200005;
const int S = 2;
const int mod[] = {998244353,1000000007};
const int base[] = {101,31};
int rand(int l,int r){
    return l+rng()%(r-l+1);
}
 
//100000000069,1000000000169
 
int res=0;
int n,a[maxn],fh[maxn];
int cnt[maxn],pos[maxn],cur[maxn];
array<int,S> pw[maxn];
 
vector<int> g[maxn];
 
int lmx[maxn],rmx[maxn],lc[maxn],rc[maxn],lim[maxn];
array<int,S> lh[maxn],rh[maxn],ls[maxn],rs[maxn],lms[maxn];
 
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
 
        set<int> ss;
 
        int h=0;
        array<int,S> x;
        for(int i=0;i<S;i++) x[i]=0;
 
        map<pair<int,array<int,S>>,int> mp;
        for(int i=mid+1;i<=r;i++){
            int lt=-1,rt=-1;
            auto it=ss.upper_bound(a[i]);
            if(it!=ss.end()) rt=*it;
            it=ss.lower_bound(a[i]);
            if(it!=ss.begin()) lt=*prev(it);
 
            if(!pos[a[i]]){ 
                ss.insert(a[i]);
                cnt[a[i]]=1;
                pos[a[i]]=i;
                h^=fh[a[i]];
 
                for(int j=0;j<S;j++){
                    if(rt!=-1 && lt!=-1) x[j]=(x[j]-(cnt[rt]-cnt[lt]+n)*pw[rt][j]%mod[j]+mod[j])%mod[j];
                    if(lt!=-1) x[j]=(x[j]+(cnt[a[i]]-cnt[lt]+n)*pw[a[i]][j])%mod[j];
                    if(rt!=-1) x[j]=(x[j]+(cnt[rt]-cnt[a[i]]+n)*pw[rt][j])%mod[j];
                }
            }
            else{
                cnt[a[i]]++;
                for(int j=0;j<S;j++){
                    if(lt!=-1) x[j]=(x[j]+pw[a[i]][j])%mod[j];
                    if(rt!=-1) x[j]=(x[j]-pw[rt][j]+mod[j])%mod[j];
                }
            }
            mp[{h,x}]++;
            //cerr << "cl " << h << ' ';
            //for(int j=0;j<S;j++) cerr << x[j] << ' ';
            //cerr << '\n';
        }
        
        ss.clear();
        h=0;
        for(int i=0;i<S;i++) x[i]=0;
 
        for(int i=mid;i>=l;i--){
 
            int lt=-1,rt=-1;
            auto it=ss.upper_bound(a[i]);
            if(it!=ss.end()) rt=*it;
            it=ss.lower_bound(a[i]);
            if(it!=ss.begin()) lt=*prev(it);
 
            if(pos[a[i]]<=n){
                ss.insert(a[i]);
                cnt[a[i]]=1;
                pos[a[i]]=n+i;
                h^=fh[a[i]];
 
                for(int j=0;j<S;j++){
                    if(rt!=-1 && lt!=-1) x[j]=(x[j]-(cnt[lt]-cnt[rt]+n)*pw[rt][j]%mod[j]+mod[j])%mod[j];
                    if(lt!=-1) x[j]=(x[j]+(cnt[lt]-cnt[a[i]]+n)*pw[a[i]][j])%mod[j];
                    if(rt!=-1) x[j]=(x[j]+(cnt[a[i]]-cnt[rt]+n)*pw[rt][j])%mod[j];
                }
            }
            else{
                cnt[a[i]]++;
                for(int j=0;j<S;j++){
                    if(rt!=-1) x[j]=(x[j]+pw[rt][j])%mod[j];
                    if(lt!=-1) x[j]=(x[j]-pw[a[i]][j]+mod[j])%mod[j];
                }
            }
 
            res+=mp[{h,x}];
            //cerr << "cr " << h << ' ';
            //for(int j=0;j<S;j++) cerr << x[j] << ' ';
            //cerr << '\n';
        }
 
        for(int i=l;i<=r;i++) cnt[a[i]]=pos[a[i]]=0;
    }
    
    //cerr << "first " << res << '\n';
 
    {//build hash
 
        for(int i=mid+1;i<=r;i++){
            rmx[i]=rmx[i-1],rs[i]=rs[i-1],rh[i]=rh[i-1],rc[i]=rc[i-1];
            for(int j=0;j<S;j++) rh[i][j]=(rh[i][j]+pw[a[i]][j])%mod[j];
            if(!pos[a[i]]){
                pos[a[i]]=i,rc[i]++;
                for(int j=0;j<S;j++) rs[i][j]=(rs[i][j]+pw[a[i]][j])%mod[j];
            }
            cnt[a[i]]++;
            if(cnt[a[i]]>rmx[i]) rmx[i]=cnt[a[i]];
        }
 
        for(int i=mid+1;i<=r;i++) cnt[a[i]]=0;
 
        lim[mid+1]=r+1;
        for(int i=mid;i>=l;i--){
            lmx[i]=lmx[i+1],ls[i]=ls[i+1],lh[i]=lh[i+1],lc[i]=lc[i+1],lim[i]=lim[i+1],lms[i]=lms[i+1];
            for(int j=0;j<S;j++) lh[i][j]=(lh[i][j]+pw[a[i]][j])%mod[j];
            if(!cur[a[i]]){
                cur[a[i]]=i,lc[i]++;
                for(int j=0;j<S;j++) ls[i][j]=(ls[i][j]+pw[a[i]][j])%mod[j];
            }
            cnt[a[i]]++;
            if(cnt[a[i]]>lmx[i]){
                lmx[i]=cnt[a[i]],lim[i]=(pos[a[i]]?pos[a[i]]:r+1);
                lms[i]=pw[a[i]];
            }
            else if(cnt[a[i]]==lmx[i]){
                lim[i]=min(lim[i],(pos[a[i]]?pos[a[i]]:r+1));
                for(int j=0;j<S;j++) lms[i][j]=(lms[i][j]+pw[a[i]][j])%mod[j];
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
            bool check=true;
            for(int j=0;j<S;j++){
                int val=(lh[i][j]+rh[rt][j]-lmx[i]*ls[i][j]%mod[j]+mod[j])%mod[j];
                if(val){
                    check=false;
                    break;
                }
            }
            //cout << check << '\n';
            res+=check;
        }
 
        //mid+1->r has different elements
        for(int i=mid+1;i<=r;i++){
            int lt=mid+1-(rc[i]*rmx[i]-(i-mid));
            if(lt<l || lt>mid) continue;
            //cerr << "rt " << i << ' ' << lt << '\n';
            bool check=true;
            for(int j=0;j<S;j++){
                int val=(rh[i][j]+lh[lt][j]-rmx[i]*rs[i][j]%mod[j]+mod[j])%mod[j];
                if(val){
                    check=false;
                    break;
                }
            }
            res+=check;
        }
    }
 
    //cerr << "second " << res << '\n';
 
    {//merge (l->mid) and(mid+1->r) that both sides have different elements
        map<pair<int,array<int,S>>,int> mp;
        for(int i=l;i<=mid;i++){
            //cout << "lim " << i << ' ' << lim[i] << '\n';
            g[lim[i]-1].push_back(i);
        }
        for(int rt=mid+1;rt<=r;rt++){
            array<int,S> val;
            for(int j=0;j<S;j++) val[j]=(rmx[rt]*rs[rt][j]-rh[rt][j]+mod[j])%mod[j];
            mp[{rmx[rt],val}]++;
 
            for(int i:g[rt]){
                for(int j=0;j<S;j++) val[j]=(lh[i][j]-lmx[i]*lms[i][j]%mod[j]+mod[j])%mod[j];
                res+=mp[{lmx[i],val}];
            }
        }
        for(int i=mid;i<=r;i++) g[i].clear();
    }
 
    for(int i=l;i<=mid;i++){
        lmx[i]=lim[i]=lc[i]=0;
        for(int j=0;j<S;j++) lh[i][j]=ls[i][j]=lms[i][j]=0;
    }
    for(int i=mid+1;i<=r;i++){
        rmx[i]=rc[i]=0;
        for(int j=0;j<S;j++) rh[i][j]=rs[i][j]=0;
    }
    //cerr << "dnc " << l << ' ' << r << ' ' << res << "\n\n";
 
}
 
void solve(){
    auto st = clock();
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=0;i<=n;i++) fh[i]=rand(1,inf);
 
    for(int i=0;i<S;i++) pw[0][i]=1;
    for(int i=1;i<=n;i++) for(int j=0;j<S;j++) pw[i][j]=pw[i-1][j]*base[j]%mod[j];
 
    for(int i=1;i<=n;i++) for(int j=0;j<S;j++) lh[i][j]=ls[i][j]=lms[i][j]=rh[i][j]=rs[i][j]=0;
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
