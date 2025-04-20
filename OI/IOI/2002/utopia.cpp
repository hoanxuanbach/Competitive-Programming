#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N;cin >> N;
    auto cal = [&](vector<int> x,vector<int> a){
        sort(x.begin(),x.end());
        for(int i=N-2;i>=0;i-=2) x[i]=-x[i];
        if(!a[N-1]) for(int &c:x) c=-c;
        int l=0,r=N-1;
        vector<int> d(N);
        for(int i=N-1;i>=0;i--){
            if(i && a[i-1]==(x[r]>0)) d[i]=x[l++];
            else d[i]=x[r--];
        }
        return d;
    };
    vector<int> x(N),y(N),a(N),b(N);
    for(int i=0;i<N;i++) cin >> x[i] >> y[i];
    for(int i=0;i<N;i++){
        int d;cin >> d;
        a[i]=(d==1 || d==4);
        b[i]=(d==1 || d==2);
    }
    x=cal(x,a),y=cal(y,b);
    for(int i=0;i<N;i++){
        if(x[i]>0) cout << '+';
        cout << x[i] << ' ';
        if(y[i]>0) cout << '+';
        cout << y[i] << '\n';
    }
}
