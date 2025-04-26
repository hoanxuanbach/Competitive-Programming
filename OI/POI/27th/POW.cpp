#include<bits/stdc++.h>
using namespace std;
#define maxn 250005
#define lli long long
#define pii pair<lli,lli>
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(),x.end()
lli n,a[maxn],pre[maxn],suf[maxn],ll[maxn],rr[maxn],num[maxn];
vector<lli> ver[maxn];
vector<pii> s;
struct node{
    vector<pii> lt,rt,lr,col;
    void add(lli p){
        lt.pb({ll[p],suf[p]});
        rt.pb({rr[p],suf[p]});
        col.pb({a[p],suf[p]});
        lr.pb({rr[s[p-1].se],suf[s[p-1].se]});
    }
    void srt(){
        sort(all(lt));sort(all(rt));sort(all(col));sort(all(lr));
        for(lli i=1;i<(lli)lt.size();i++) lt[i].se+=lt[i-1].se;
        for(lli i=1;i<(lli)rt.size();i++) rt[i].se+=rt[i-1].se;
        for(lli i=1;i<(lli)lr.size();i++) lr[i].se+=lr[i-1].se;
    }
    lli query(lli l,lli r){
        lli p1=lower_bound(all(lt),make_pair(l,0LL))-lt.begin()-1,p2=upper_bound(all(rt),make_pair(r,n))-rt.begin()-1;
        lli sum=lt.back().se;
        if(p1!=-1) sum-=lt[p1].se;
        if(p2!=-1) sum+=rt[p2].se;
        return sum;
    }
    lli cal(lli c){
        lli p=lower_bound(all(col),make_pair(c,n))-col.begin()-1;
        if(p!=-1 && col[p].fi==c) return col[p].se;
        else return 0;
    }
    lli get(lli r){
        lli p=lower_bound(all(lr),make_pair(r,n))-lr.begin()-1;
        if(p!=-1) return lr[p].se;
        else return 0;
    }
};
namespace Merge_Sort_Tree{
    node tree[4*maxn];
    void update(lli l,lli r,lli id,lli p){
        tree[id].add(p);
        if(l==r) return;
        lli mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
    }
    void build(lli l,lli r,lli id){
        tree[id].srt();
        if(l==r) return;
        lli mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    lli query(lli l,lli r,lli id,lli tl,lli tr){
        if(tr<l || r<tl) return 0;
        else if(tl<=l && r<=tr) return tree[id].query(tl,tr);
        lli mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
    lli query2(lli l,lli r,lli id,lli tl,lli tr,lli c){
        if(tr<l || r<tl) return 0;
        else if(tl<=l && r<=tr) return tree[id].cal(c);
        lli mid=(l+r)>>1;
        return max(query2(l,mid,id<<1,tl,tr,c),query2(mid+1,r,id<<1|1,tl,tr,c));
    }
    lli query3(lli l,lli r,lli id,lli p,lli tr){
        if(l==r) return tree[id].get(tr);
        lli mid=(l+r)>>1;
        if(p<=mid) return query3(l,mid,id<<1,p,tr)+tree[id<<1|1].get(tr);
        else return query3(mid+1,r,id<<1|1,p,tr);
    }
}
int ile_powtorzen(int L,int R){
    lli l=L+1,r=R+1;
    lli k=pre[r],c=a[r];r-=pre[r]+1;
    if(r<l) return r+k+1-l;
    lli total=Merge_Sort_Tree::query(1,n,1,l,r);
    lli Maxc=Merge_Sort_Tree::query2(1,n,1,l,r,c);
    lli pos=lower_bound(all(s),make_pair(l,0LL))-s.begin()+1;
    total-=Merge_Sort_Tree::query3(1,n,1,pos,r);
    total=(num[r]-num[l-1])-total+max(0LL,k-Maxc);
    return total;
}
void inicjuj(int N,vector<int> t){
    n=N;a[0]=a[n+1]=-1;
    vector<lli> p;
    for(lli i=1;i<=n;i++){
        a[i]=t[i-1];
        p.pb(a[i]);
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    for(lli i=1;i<=n;i++) a[i]=lower_bound(p.begin(),p.end(),a[i])-p.begin()+1;
    for(lli i=1;i<=n;i++){
        if(a[i]==a[i-1]) pre[i]=pre[i-1]+1;
        else pre[i]=0;
    }
    for(lli i=n;i>=1;i--){
        if(a[i]==a[i+1]) suf[i]=suf[i+1]+1;
        else suf[i]=0;
    }
    for(lli i=1;i<=n;i++){
        num[i]=num[i-1]+suf[i];
        while(!ver[a[i]].empty() && suf[ver[a[i]].back()]<=suf[i]) ver[a[i]].pop_back();
        if(!ver[a[i]].empty()) ll[i]=ver[a[i]].back();
        else ll[i]=0;
        ver[a[i]].push_back(i);
    }
    for(lli i=1;i<=n;i++) ver[i].clear();
    for(lli i=n;i>=1;i--){
        while(!ver[a[i]].empty() && suf[ver[a[i]].back()]<suf[i]) ver[a[i]].pop_back();
        if(!ver[a[i]].empty()) rr[i]=ver[a[i]].back();
        else rr[i]=n+1;
        ver[a[i]].push_back(i);
    }
    for(lli i=1;i<=n;i++) s.pb({ll[i],i});
    sort(s.begin(),s.end());
    for(lli i=1;i<=n;i++) Merge_Sort_Tree::update(1,n,1,i);
    Merge_Sort_Tree::build(1,n,1);
}
/*
signed main(){
    ios_base::sync_with_stdio(false);
    inicjuj(10, {1,1,1,1,1,1,1,1,1,1});
    cout << ile_powtorzen(0, 9) << '\n';
    cout << ile_powtorzen(0, 6) << '\n';
    cout << ile_powtorzen(4, 6) << '\n';
    cout << ile_powtorzen(3, 4) << '\n';
}
*/
