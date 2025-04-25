#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,a[maxn],b[maxn];
vector<int> p[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){int x;cin >> x;p[x].push_back(i);}
    set<int> ss;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        if(p[x].empty()){
            cout << -1 << '\n';
            return 0;
        }
        int k=p[x].back();p[x].pop_back();
        auto it=ss.lower_bound(k);
        if(it==ss.end()) a[k]=(int)ss.size()+1;
        else{
            a[k]=a[*it];
            ss.erase(it);
        }
        ss.insert(k);
        b[i]=a[k];
    }
    cout << (int)ss.size() << '\n';
    for(int i=1;i<=n;i++) cout << a[i] << " \n"[i==n];
    for(int i=1;i<=n;i++) cout << b[i] << " \n"[i==n];
}
/*
7
1 2 3 2 2 1 3
2 3 1 2 3 2 1
*/
