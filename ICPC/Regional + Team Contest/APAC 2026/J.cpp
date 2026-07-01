#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve() {
    int n,d;cin >> n >> d;
    vector<int> a(n+1),fa(n+1);
    vector<int> b(n+1),fb(n+1),f(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],fa[a[i]]=i;
    for(int i=1;i<=n;i++) cin >> b[i],fb[b[i]]=i,f[i]=fa[b[i]];

    int cnt=0;
    for(int i=1;i<n;i++) cnt+=f[i]>f[i+1];

    auto change = [&](int x,int k){
        if(x>1) cnt-=(f[x-1]>f[x]);
        if(x<n) cnt-=(f[x]>f[x+1]);
        f[x]=k;
        if(x>1) cnt+=(f[x-1]>f[x]);
        if(x<n) cnt+=(f[x]>f[x+1]);
    };
    auto print = [&](){
        cout << n*(cnt-1)+f[n] << '\n';
    };
    print();
    for(int i=1;i<d;i++){
        int op,x,y;cin >> op >> x >> y;
        if(op == 1){
            int A=a[x],B=a[y];
            swap(a[x],a[y]);
            swap(fa[A],fa[B]);

            x=fb[A],y=fb[B];
            change(x,fa[A]);
            change(y,fa[B]);
        }
        else{
            int A=b[x],B=b[y];
            swap(b[x],b[y]);
            swap(fb[A],fb[B]);

            int k=f[x];
            change(x,f[y]);
            change(y,k);
        }
        print();
    }
    

}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    //cin >> num_test;
    while (num_test--) {
        solve();
    }
}