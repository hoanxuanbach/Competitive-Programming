#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,R;cin >> n >> R;R=R%n+2*n;
    vector<int> b(2*n),a(2*n);
    vector<vector<int>> cnt(n,vector<int>(3,0));

    for(int i=0;i<2*n;i++) cin >> b[i];
    int s=b[0];
    auto g = [&](int x){
        return (x>s)+(x>=s);
    };

    auto f = [&](){
        if(s==1) return 0;
        cnt.assign(n,vector<int>(3,0));
        if(s>n+1){
            int pos=0;
            for(int i=0;i<n;i++){
                cnt[i][0]=(a[i]>s)+(a[n+i]>s);
                cnt[i][1]=(a[i]==s || a[n+i]==s);
            }
            int x=0,y=0,rt=0;
            for(int it=0;it<3;it++){
                int i=0;
                do{
                    auto &d=cnt[i];
                    x+=d[0];y+=d[1];
                    if(x+y>1){
                        if(i){
                            d[0]=1;
                            d[1]=0;
                            x--;
                        }
                        else{
                            if(y>0){
                                d[1]=1;
                                d[0]=0;
                                y--;
                            }
                            else{
                                d[1]=0;
                                d[0]=1;
                                x--;
                            }
                        }
                    }
                    else{
                        if(i){
                            d[0]=x,d[1]=y;
                            x=y=0;
                        }
                        else{
                            if(y>0) rt++;
                            d[0]=d[1]=0;
                        }
                    }
                    i=(i+n-1)%n;
                }while(i!=0);
            }
            for(int i=0;i<n;i++) if(cnt[i][1]) return i-rt*n;
        }
        else{
            for(int i=0;i<n;i++) cnt[i][g(a[i])]++,cnt[i][g(a[n+i])]++;
            int x=0,rt=0;
            while(!cnt[0][x]) x++;
            cnt[0][x]--;
            vector<int> num(3,0);
            for(int i=1;i<=3*n;i++){
                for(int j=0;j<3;j++) num[j]+=cnt[(i-1)%n][j],cnt[(i-1)%n][j]=0;
                int y=0;
                while(!num[y]) y++;
                num[y]--;
                if(x>y) swap(x,y);
                cnt[(i-1)%n][y]++;
                if(y==1){
                    rt++;
                    if(i>2*n){
                        if(R<i) rt--;
                        return (n-1-R+i)%n-rt*n;
                    }
                }
            }
        }
        assert(false);
        return -1;
    };
    auto get = [&](int x){
        vector<int> c=b;
        rotate(c.begin(),c.begin()+1,c.begin()+2*x+1);
        for(int i=0;i<n;i++) a[i]=c[i<<1],a[n+i]=c[i<<1|1];
        return f();
    };

    int cc=get(n-1),l=0,r=n-1;
    while(l<r){
        int m=(l+r)>>1;
        if(get(m)>=cc-(cc%n+n)%n) r=m;
        else l=m+1;
    }
    int val=get(l);
    l=0,r=n-1;
    while(l<r){
        int m=(l+r+1)>>1;
        if(get(m)<=val) l=m;
        else r=m-1;
    }
    cout << l+1 << '\n';
}
