#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int ask(int x,int y){
    cout << "? " << x << ' ' << y << endl;
    int d;cin >> d;return d;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    vector<int> p(n),a(n+1);
    iota(p.begin(),p.end(),1);
    shuffle(p.begin(),p.end(),rng);
    int x=0,y=0,w=0;
    for(int i:p){
        if(!x) x=i;
        else if(!y) y=i,w=ask(x,y);
        else{
            int d=ask(x,i);
            if(d<w) a[i]=d;
            else if(w<d) a[y]=w,y=i,w=d;
            else{
                a[x]=w;
                x=i,w=ask(x,y);
            }
        }
    }
    a[x]=a[y]=w;
    cout << "! ";
    for(int i=1;i<=n;i++) cout << a[i] << ' ';
    cout << endl;
}
