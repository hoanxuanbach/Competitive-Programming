#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

struct event{
    int x,y1,y2;
    bool open;
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    int n,m;cin >> n >> m;
    vector<pii> p(n);
    for(int i=0;i<n;i++) cin >> p[i].fi >> p[i].se;
    vector<event> E;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        if(p[i].fi!=p[j].fi) continue;
        if(p[i].se>p[j].se) E.push_back({p[i].fi,p[j].se,p[i].se,false});
        else E.push_back({p[i].fi,p[i].se,p[j].se,true});
    }
    sort(E.begin(),E.end(),[&](event a,event b){return a.x>b.x;});
    if(!E.back().open) for(auto &x:E) x.open^=true;

    int ans=0,x=0;
    set<pii> A,B;
    vector<pii> C;
    while(x<=m){
        if(!E.empty()){
            int nx=E.back().x;
            if((nx&1)!=(x&1)) nx--;
            nx-=2;
            if(nx>=x) x=nx;
        }
        if(B.empty()) ans=x;
        auto check = [&](pii a){
            return ((a.se-a.fi)&1);
        };
        int cnt=0;
        while(!E.empty()){
            if(E.back().x!=x) break;
            event e=E.back();E.pop_back();
            int l=e.y1,r=e.y2;
            if(e.open){
                while(true){
                    auto it=A.lower_bound({l,r});
                    if(it!=A.end() && it->fi==r){
                        r=it->se;
                        cnt-=check(*it);
                        A.erase(it);
                        continue;
                    }
                    if(it!=A.begin() && prev(it)->se==l){
                        it=prev(it);
                        l=it->fi;
                        cnt-=check(*it);
                        A.erase(it);
                        continue;
                    }
                    break;
                }
                cnt+=check({l,r});
                A.insert({l,r});
            }
            else C.push_back({l,r});
        }
        bool ok=true;
        for(auto [l,r]:C){
            auto it=A.lower_bound({l+1,-1});
            if(it!=A.begin()){
                it=prev(it);
                auto [lt,rt]=*it;
                if(lt<=l && r<=rt){
                    cnt-=check({lt,rt});
                    A.erase(it);
                    if(lt<l){
                        cnt+=check({lt,l});
                        A.insert({lt,l});
                    }
                    if(r<rt){
                        cnt+=check({r,rt});
                        A.insert({r,rt});
                    }
                }
                else{
                    ok=false;
                    break;
                }
            }
            else{
                ok=false;
                break;
            }
        }
        if(!ok || cnt) break;
        swap(A,B);C.clear();
        x++;
    }
    cout << ans << '\n';
}
