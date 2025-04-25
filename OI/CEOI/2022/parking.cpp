#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int n,m;
vector<array<int,2>> res;
array<int,2> a[maxn],f[maxn];   
queue<int> A,B,C,D,E;

int get(){
    if(E.empty()){
        cout << -1 << '\n';
        exit(0);
    }
    int x=E.front();E.pop();
    return x;
}

void move(int x,int i,int y,int j){
    res.push_back({x,y});
    swap(a[x][i],a[y][j]);
    int k=a[y][j];
    f[k][f[k][0]!=x]=y;
    if(a[x][0]) A.push(x);
    else E.push(x);
}

bool check(int k){
    int x=f[k][0],y=f[k][1];
    if(a[x][1]!=k || a[y][1]!=k) return true;
    int z=get();
    move(x,1,z,0);
    move(y,1,z,1);
    return false;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int x,y;cin >> x >> y;
        f[a[i][0]=x][!!f[x][0]]=i;
        f[a[i][1]=y][!!f[y][0]]=i;
        if(!x) E.push(i);
        A.push(i);
    }
    D=B=C=A;
    while(true){
        if(!A.empty()){
            //cout << "A" << endl;
            int p=A.front();A.pop();
            auto [x,y]=a[p];
            if(!x || y) continue;
            int q = f[x][f[x][0]==p];
            int i = !!a[q][1];
            if(a[q][i]!=x) B.push(p);
            else move(q,i,p,1);
        }
        else if(!B.empty()){
            //cout << "B" << endl;
            int p=B.front();B.pop();
            auto [x,y]=a[p];
            if(!x || y) continue;
            do{
                p=f[x][f[x][0]==p];
            }while(check(x=a[p][1]));   
        }
        else if(!C.empty()){
            //cout << "C" << endl;
            int p=C.front();C.pop();
            auto [x,y]=a[p];
            if(y && x!=y && check(y)) D.push(y);
        }
        else if(!D.empty()){
            //cout << "D" << endl;
            int p=D.front();D.pop();
            auto [x,y]=a[p];
            if(y && x!=y) move(p,1,get(),0);
        }
        else break;
    }   

    cout << (int)res.size() << '\n';
    for(auto [x,y]:res) cout << x << ' ' << y << '\n';
}