#include<bits/stdc++.h>
using namespace std;
const int maxn = 505;
int n,a[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    while(true){
        int k;cin >> k;
        if(k==-1) return 0;
        if(a[k]==1){
            cout << 1 << endl;
            a[k]=0;
        }
        else{
            bool remain=false;
            for(int i=1;i<=n;i++) if(i!=k && a[i]) remain=true;
            if(remain){
                cout << a[k]-1 << endl;
                a[k]=1;
            }
            else cout << a[k] << endl;
        }
        k=-1;
        for(int i=1;i<=n;i++) if(a[i]==1) k=i;
        cout << k << endl;
        if(k==-1) return 0;
        int x;cin >> x;
        a[k]-=x;
    }
}