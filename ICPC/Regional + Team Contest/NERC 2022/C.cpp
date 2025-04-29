#include<bits/stdc++.h>
using namespace std;
pair<int,int> x[5];
signed main(){
    for(int i=1;i<=3;i++) cin >> x[i].first >> x[i].second;
    sort(x+1,x+4);
    cout << 3 << '\n';
    int a=min(x[1].second,min(x[2].second,x[3].second)),b=max(x[1].second,max(x[2].second,x[3].second));
    cout << x[2].first << " " << a << " " << x[2].first << " "  << b << '\n';
    cout << x[1].first << " " << x[1].second << " " << x[2].first << " " << x[1].second << '\n';
    cout << x[3].first << " " << x[3].second << " " << x[2].first << " " << x[3].second << '\n';
}
