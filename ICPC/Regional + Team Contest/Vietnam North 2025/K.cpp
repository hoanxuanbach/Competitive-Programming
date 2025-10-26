#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n+1),d(n+1),p(n+1);
    for(int i=0;i<n;i++){
        cin >> a[i] >> d[i];
        p[a[i]]=i;
        if(!d[i]) d[i]=-1;
    }
    for(int i=n-1;i>=0;i--){
        d[i]+=d[i+1];
    }

    vector<set<int>> ss(2*n+1);
    vector<int> tree(8*n+8,inf);

    function<void(int,int,int,int)> update = [&](int l,int r,int id,int x){
        if(l==r){
            tree[id]=(ss[x].empty()?inf:*ss[x].begin());
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x);
        else update(mid+1,r,id<<1|1,x);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    };
    function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return inf;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    };

    auto del = [&](int x,int val){
        ss[x].erase(val);
        update(0,2*n,1,x);
    };
    auto add = [&](int x,int val){
        ss[x].insert(val);
        update(0,2*n,1,x);
    };

    int K=0,I=-1;
    if(!d[0]){
        vector<int> P;
        for(int i=0;i<n;i++) if(!d[i+1]) P.push_back(a[i]);
        if(m>(int)P.size()) K=1;
        else{
            int sz=(int)P.size();
            set<pair<int,int>> S;
            for(int i=0;i<=sz-m;i++) S.insert({P[i],i});
            vector<int> res;
            
            int i=0;
            while(m>1){
                auto [x,j]=*S.begin();
                res.push_back(x);
                while(i<=j) S.erase({P[i],i}),i++;
                m--;S.insert({P[sz-m],sz-m});
            }
            res.push_back(P.back());
            for(int x:res) cout << x << ' ';
            cout << '\n';
            return;
        }
    }
    else K=(abs(d[0])-1)/m+1;
    vector<int> res;
    for(int i=0;i<=n-m;i++) add(d[i+1]+n,a[i]);
    while(m>1){
        int l=max(d[I+1]-K,-K*(m-1));
        int r=min(d[I+1]+K,K*(m-1));
        l=max(l,-n);r=min(r,n);

        int J=query(0,2*n,1,l+n,r+n);
        if(J==inf){
            assert(false);
            return;
        }
        J=p[J];
        while(I<J) I++,del(d[I+1]+n,a[I]);
        res.push_back(a[I]);
        m--;add(d[n-m+1]+n,a[n-m]);
    }
    res.push_back(a[n-1]);
    for(int x:res) cout << x << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}