#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
bool ask(int x,int y){
    cout << "? " << x << ' ' << y << endl;
    char c;cin >> c;return (c=='<');
}

void solve3(){
    int a=2-ask(1,2),b=4-ask(3,4),c=6-ask(5,6);
    int na=3^a,nb=7^b,nc=3^c;
    int x=a+(b-a)*ask(a,b);
    x+=(c-x)*ask(x,c);
    vector<int> p;
    if(x!=a) p.push_back(na);
    if(x!=b) p.push_back(nb);
    if(x!=c) p.push_back(nc);
    p[0]+=(p[1]-p[0])*ask(p[1],p[0]);
    ask(x,p[0]);
    cout << "!" << endl;
}

void solve(){
    int n;cin >> n;
    if(n==3){
        solve3();
        return;
    }
    vector<int> a(2*n);
    iota(a.begin(),a.end(),1);
    function<int(int,int)> get = [&](int l,int r){
        if(l+1==r) return a[l];
        int mid=(l+r)>>1;
        int x=get(l,mid),y=get(mid,r);
        if(x==-1) return y;
        else if(y==-1) return x;
        else return y+ask(x,y)*(x-y);
    };
    for(int i=0;i<n;i++) a[get(0,2*n)-1]=-1;
    cout << "!" << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}
