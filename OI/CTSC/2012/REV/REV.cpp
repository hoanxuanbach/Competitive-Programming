#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+5;

int n,m,q,S,qq[maxn];
bool sw=false;
int x1[maxn],x2[maxn],Y[maxn],y2[maxn];
long long res[maxn];

int bit[2][maxn];
void update(int t,int x,int val){
    for(int i=x;i<=S;i+=(i&(-i))) bit[t][i]+=val;
}
int query(int t,int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[t][i];
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=7;test<=7;test++){
        cout << test << endl;
        string in="rev"+to_string(test)+".in";
        ifstream cin(in);
        string out="rev"+to_string(test)+".out";
        ofstream cout(out);
        /*
        auto solve = [&]{
            cin >> n >> m >> q;
            if(n>m) sw=true,swap(n,m);
            vector<vector<int>> A(n+1,vector<int>(m+1,0));
            vector<int> com;
            if(!sw){
                for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin >> A[i][j];
            }
            else{
                for(int j=1;j<=m;j++) for(int i=1;i<=n;i++) cin >> A[i][j];
            }
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) com.push_back(A[i][j]);
            sort(com.begin(),com.end());
            com.erase(unique(com.begin(),com.end()),com.end());
            S=(int)com.size();
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) A[i][j]=lower_bound(com.begin(),com.end(),A[i][j])-com.begin()+1;

            for(int i=1;i<=q;i++){
                cin >> x1[i] >> Y[i] >> x2[i] >> y2[i];
                if(sw) swap(x1[i],Y[i]),swap(x2[i],y2[i]);
                qq[i]=i;res[i]=0;
            }
            int B=sqrt(q);
            sort(qq+1,qq+q+1,[B](int x,int y){
                int lx=Y[x],rx=y2[x];
                int ly=Y[y],ry=y2[y];
                if(lx/B!=ly/B) return lx/B<ly/B;
                else{
                    if((lx/B)&1) return rx>ry;
                    else return rx<ry;
                }
            });

            for(int a=1;a<=n;a++) for(int b=a;b<=n;b++){
                long long total=0;
                int l=1,r=0;
                for(int i=1;i<=q;i++){
                    int id=qq[i];
                    if(a<x1[id] || x2[id]<b) continue;
                    while(r<y2[id]){
                        r++;
                        update(0,A[a][r],1);
                        update(1,A[b][r],1);
                        total+=r-l+1-query(0,A[b][r]);
                    }
                    while(l>Y[id]){
                        l--;
                        update(0,A[a][l],1);
                        update(1,A[b][l],1);
                        total+=query(1,A[a][l]-1);
                    }
                    while(r>y2[id]){
                        total-=r-l+1-query(0,A[b][r]);
                        update(0,A[a][r],-1);
                        update(1,A[b][r],-1);
                        r--;
                    }
                    while(l<Y[id]){
                        total-=query(1,A[a][l]-1);
                        update(0,A[a][l],-1);
                        update(1,A[b][l],-1);
                        l++;
                    }
                    //cout << a << ' ' << b << ' ' << id << ' ' << total << '\n';
                    res[id]+=total;
                }
                for(int i=l;i<=r;i++){
                    update(0,A[a][i],-1);
                    update(1,A[b][i],-1);
                }
            }
            long long total=0;
            for(int i=1;i<=q;i++) total^=res[i];
            cout << total << '\n';
        };
        solve();
        */
        auto solve7 = [&](){
            int n,m,q;cin >> n >> m >> q;
            vector<vector<int>> A(n+1,vector<int>(m+1));
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
                cin >> A[i][j];
                //if((i+j)&1) A[i][j]=9;
                //else A[i][j]=5;
            }
            long long ans=0;
            auto g = [&](int x,int a,int b){
                if(x==0) return 0;
                if(a==b){
                    x=(x+a)/2;
                    return x*(x+1)/2;
                }
                else{
                    int k=(x+a)/2;
                    return ((x+a+1)/2)*k-k*(k+1)/2;
                }
            };
            auto f = [&](int l,int r){
                vector<vector<int>> c(2,vector<int>(2,0));
                for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
                    c[i][j]=g(r,i,j)-g(l-1,i,j);
                    //cout << l << ' ' << r << ' ' << i << ' ' << j << ' ' << c[i][j] << '\n';
                    c[i][j]-=((l-1+i)/2)*((r+j)/2-(l-1+j)/2);
                }
                return c;
            };
            for(int i=1;i<=q;i++){
                int X1,Y1,X2,Y2;
                cin >> X1 >> Y1 >> X2 >> Y2;
                vector<vector<int>> cx=f(X1,X2);
                vector<vector<int>> cy=f(Y1,Y2);
                long long total=0;
                for(int a=0;a<=1;a++) for(int b=0;b<=1;b++){
                    total+=1LL*cx[a][b]*cy[a^1][b];
                    //cout << cx[a][b] << ' ' << cy[a][b] << '\n';
                }
                ans^=total;
            }
            cout << ans << '\n';
        };
        solve7();
    }
}
