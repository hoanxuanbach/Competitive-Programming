#include<bits/stdc++.h>
using namespace std;
int fake[(1<<20)+5];

vector<int> dnc(vector<pair<int,int>> p){
    
    if((int)p.size()==1) return {p[0].first,p[0].second};
    vector<pair<int,int>> lt,rt,mt;
    
    //cout << "dnc " << k << endl;
    int D=p[0].first^p[0].second,k=0;
    while(!(D>>k&1)) k++;
    for(auto &[x,y]:p){
        if(x>>k&1) swap(x,y);
        if(x>>k&1) rt.push_back({x,y});
        else if(!(y>>k&1)) lt.push_back({x,y});
        else mt.push_back({x,y});
        //cout << x << ' ' << y << endl;
    }
    for(int i=0;i<(int)mt.size();i+=2) lt.push_back({mt[i].first,mt[i+1].first});
    vector<int> L=dnc(lt);
    for(int i=0;i<(int)mt.size();i++) fake[mt[i].first]=i+1;
    vector<int> path;
    for(int i=0;i<(int)L.size();i++) if(fake[L[i]]) path.push_back(i);
    //cout << "R " << (int)path.size() << '\n';
    for(int i=1;i<(int)path.size();i+=2){
        int j=(i+1)%(int)path.size();
        int x=fake[L[path[i]]]-1,y=fake[L[path[j]]]-1;
        //cout << "add_rt " << x << ' ' << y << '\n';
        rt.push_back({mt[x].second,mt[y].second});
    }
    for(int i=0;i<(int)mt.size();i++) fake[mt[i].first]=0;
    vector<int> R=dnc(rt);
    vector<int> res;

    for(int i=0;i<(int)mt.size();i++) fake[mt[i].first]=i+1;
    for(int i=1;i<(int)path.size();i+=2){
        int j=(i+1)%(int)path.size();
        int x=fake[L[path[i]]]-1,y=fake[L[path[j]]]-1;
        fake[mt[x].second]=fake[mt[y].second]=i;
    }
    for(int i=0;i<(int)R.size();i++){
        res.push_back(R[i]);
        if(fake[R[i]]){
            int x=R[i],y=R[i+1];i++;
            int l=fake[x],r=(l+1)%(int)path.size();
            l=path[l],r=path[r];
            bool rev=false;
            int id=fake[L[l]]-1;
            if(mt[id].second!=x) rev=true;

            vector<int> add;
            while(true){
                bool ok=(l==r);
                add.push_back(L[l]),l=(l+1)%(int)L.size();
                if(ok) break;
            }
            if(rev) reverse(add.begin(),add.end());
            res.insert(res.end(),add.begin(),add.end());
            res.push_back(y);
        }
    }
    for(int i=0;i<(int)mt.size();i++) fake[mt[i].first]=fake[mt[i].second]=0;
    //cout << "end" << endl;
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    vector<pair<int,int>> p(1<<(n-1));
    for(int i=0;i<(1<<(n-1));i++) cin >> p[i].first >> p[i].second;
    vector<int> res=dnc(p);
    for(int x:res) cout << x << ' ';
    cout << '\n';
}