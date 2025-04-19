#include<bits/stdc++.h>
using namespace std;

signed main(){
    //freopen("output_3.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    int lg=0;
    while((1<<lg) < n) lg++;

    auto dist = [&](int x,int y){
        return (x>=y?x-y:x-y+n);
    };
    auto sub = [&](int x,int d){
        return (x-d<1?x-d+n:x-d);
    };

    cout << min(9,2*(lg-1)) << '\n';
    for(int p=1;p<=n;p++){
        cout << p << '\n';
        for(int x=1;x<=n;x++){
            int d=dist(x,p);
            for(int i=0;i<lg-1;i++) cout << (d<(1<<i)?'T':'F') << ' ' << sub(x,1<<i) << ' ';

            int k=0,cur=0;
            while((1<<k)<=d) k++;
            if(d>=32) d-=32,cur+=32;
            for(int i=lg-1-(n==48);i>=1;i--){
                if(d>>i&1) cur+=(1<<i);
                cout << (i==k?'T':'F') << ' ' << sub(x,cur) << ' ';
            }
            cout << '\n';
        }
    }
}