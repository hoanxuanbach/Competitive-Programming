#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;
struct node{
    int d,id;
    bool operator<(const node &a)const{
        return d>a.d;
    }
}a[maxn];

vector<pair<int,int>> ans;
void add(int i,int j){
    a[i].d--;a[j].d--;
    ans.push_back({a[i].id,a[j].id});
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i].d,a[i].id=i;
    while(true){
        sort(a+1,a+n+1);
        while(n && !a[n].d) n--;
        if(!n) break;
        if(a[n].d==1){
            int p=1;
            for(int i=1;i<=n;i++) if((a[i].d&1) && a[i].d>1){p=i;break;}
            if(a[p].d==1 && n>2){
                cout << -1 << '\n';
                return 0;
            }
            add(p,n);
        }
        else if(a[n].d==2){
            if(n<3){
                cout << -1 << '\n';
                return 0;
            }
            if(a[1].d==2){
                for(int i=1;i<=n;i++) add(i,i%n+1);
            }
            else{
                if(a[n-1].d!=2){
                    cout << -1 << '\n';
                    return 0;
                }
                add(n-1,n),add(1,n),add(1,n-1);
            }
        }
        else{
            cout << -1 << '\n';
            return 0;
        }
    }
    cout << (int)ans.size() << '\n';
    for(auto [u,v]:ans) cout << 2 << ' ' << u << ' ' << v << '\n';
}
