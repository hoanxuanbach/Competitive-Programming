#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+5;

struct node{
    int sum,x,l,r;
    bool operator<(const node&a)const{
        return sum>a.sum;
    }
};

int n,m,k;
struct group{
    int sz;
    vector<int> c,ans;
    priority_queue<node> pq;
    void get(){
        auto [sum,x,l,r]=pq.top();pq.pop();
        ans.push_back(sum);
        if(x<r && x>0) pq.push({sum+c[x],x+1,l,r});
        if(l<x && l>1) pq.push({sum+c[l-1],l,l-1,x-1});
    }
    bool build(int l,int r){
        sort(c.begin(),c.end());
        sz=(int)c.size();
        if(sz<l) return false;
        r=min(r,sz);
        
        int sum=0;
        for(int i=0;i<=r;i++){
            if(i) sum+=c[i-1];
            if(l<=i) pq.push({sum,i,i,sz});
        }
        for(int i=sz-1;i>=1;i--) c[i]-=c[i-1];
        get();
        if(!pq.empty()) get();
        return true;
    }
    int query(int x){
        if(x<(int)ans.size()) return ans[x]-ans[x-1];
        if(pq.empty()) return -1;
        get();
        return ans[x]-ans[x-1];
    }
}g[maxn];

struct value{
    int sum,x,d;
    bool operator<(const value &a)const{
        return sum>a.sum;
    }
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){
        int x,val;cin >> x >> val;
        g[x].c.push_back(val);
    }
    int total=0;
    vector<int> ord;
    for(int i=1;i<=m;i++){
        int x,y;cin >> x >> y;
        if(!g[i].build(x,y)){
            for(int j=1;j<=k;j++) cout << -1 << '\n';
            return 0;
        }
        total+=g[i].ans[0];
        if((int)g[i].ans.size()>1) ord.push_back(i);
    }
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return g[x].ans[1]-g[x].ans[0]<g[y].ans[1]-g[y].ans[0];
    });
    int sz=(int)ord.size();
    cout << total << '\n';k--;
    priority_queue<value> pq;
    if(sz) pq.push({total+g[ord[0]].query(1),0,1});
    while(k && !pq.empty()){
        auto [sum,x,d]=pq.top();pq.pop();k--;
        cout << sum << '\n';
        if(x+1<sz){
            int val=g[ord[x+1]].query(1);
            if(d==1) pq.push({sum-g[ord[x]].query(1)+val,x+1,1});
            pq.push({sum+val,x+1,1});
        }
        int val=g[ord[x]].query(d+1);
        if(val!=-1) pq.push({sum+val,x,d+1});
    }
    for(int i=1;i<=k;i++) cout << -1 << '\n';
}