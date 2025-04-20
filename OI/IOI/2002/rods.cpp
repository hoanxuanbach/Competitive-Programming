#include<bits/stdc++.h>
using namespace std;
int N,p[1005][1005];

void init(){
    int x,u,y,v;cin >> x >> y >> u >> v;
    for(int i=x;i<=u;i++) for(int j=y;j<=v;j++) p[i][j]++;
    cin >> x >> y >> u >> v;
    for(int i=x;i<=u;i++) for(int j=y;j<=v;j++) p[i][j]++;
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) p[i][j]+=p[i-1][j]+p[i][j-1]-p[i-1][j-1];

}

int cnt=0;

int get(int x,int y,int u,int v){
    cnt++;
    assert(cnt<=100);
    cout << "? " << x << ' ' << u << ' ' << y << ' ' << v << endl;
    //return !!(p[u][v]-p[x-1][v]-p[u][y-1]+p[x-1][y-1]);
    int a;cin >> a;return a;
}

int get_lt(int x,int y,int u,int v){
    int l=y,r=N,res=N+1;
    while(l<=r){
        int m=(l+r)>>1;
        if(get(x,y,u,m)) res=m,r=m-1;
        else l=m+1;
    }
    return res;
}
int get_rt(int x,int y,int u,int v){
    int l=1,r=y,res=0;
    while(l<=r){
        int m=(l+r)>>1;
        if(get(x,m,u,v)) res=m,l=m+1;
        else r=m-1;
    }
    return res;
}
int get_dn(int x,int y,int u,int v){
    int l=1,r=x,res=0;
    while(l<=r){
        int m=(l+r)>>1;
        if(get(m,y,u,v)) res=m,l=m+1;
        else r=m-1;
    }
    return res;
}
int get_up(int x,int y,int u,int v){
    int l=x,r=N,res=N+1;
    while(l<=r){
        int m=(l+r)>>1;
        if(get(x,y,m,v)) res=m,r=m-1;
        else l=m+1;
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N;
    //init();
    int Y=get_lt(1,1,N,1),V=get_rt(1,N,N,N);
    int X=get_up(1,1,1,N),U=get_dn(N,1,N,N);
    int xy=get(X,Y,X,Y),xv=get(X,V,X,V),uy=get(U,Y,U,Y),uv=get(U,V,U,V);
    array<int,4> A,B;
    auto print = [&](){
        cout << "! " << B[0] << ' ' << B[1] << ' ' << B[2] << ' ' << B[3] << ' ' << A[0] << ' ' << A[1] << ' ' << A[2] << ' ' << A[3] << endl;
    };
    //cout << '*' << X << ' ' << Y << ' ' << U << ' ' << V << '\n';
    //cout << "First\n";
    if(!get(X,Y+1,U,Y+1)){
        if(!xy){
            A={get_up(X,Y,X,Y),Y,U,Y};
            B={X,get_lt(X,Y+1,X,Y+1),X,V};
        }
        else if(!uy){
            A={X,Y,get_dn(U,Y,U,Y),Y};
            B={U,get_lt(U,Y+1,U,Y+1),U,V};
        }
        else{
            A={X,Y,U,Y};
            B[1]=get_lt(X,Y+1,U,Y+1),B[3]=V;
            B[0]=B[2]=get_up(X,B[1],X,B[3]);
        }
        print();
        return 0;
    }
    if(!get(X,V-1,U,V-1)){
        if(!xv){
            A={get_up(X,V,X,V),V,U,V};
            B={X,Y,X,get_rt(X,V-1,X,V-1)};
        }
        else if(!uv){
            A={X,V,get_dn(U,V,U,V),V};
            B={U,Y,U,get_rt(U,V-1,U,V-1)};
        }
        else{
            A={X,V,U,V};
            B[1]=Y,B[3]=get_rt(X,V-1,U,V-1);
            B[0]=B[2]=get_up(X,B[1],X,B[3]);
        }
        print();
        return 0;
    }
    if(!get(X+1,Y,X+1,V)){
        if(!xy){
            B={X,get_lt(X,Y,X,Y),X,V};
            A={get_up(X+1,Y,X+1,Y),Y,U,Y};
        }
        else if(!xv){
            B={X,Y,X,get_rt(X,V,X,V)};
            A={get_up(X+1,V,X+1,V),V,U,V};
        }
        else{
            B={X,Y,X,V};
            A[0]=get_up(X+1,Y,X+1,V),A[2]=U;
            A[1]=A[3]=get_lt(A[0],Y,A[2],Y);
        }
        print();
        return 0;
    }
    if(!get(U-1,Y,U-1,V)){
        if(!uy){
            B={U,get_lt(U,Y,U,Y),U,V};
            A={X,Y,get_dn(U-1,Y,U-1,Y),Y};
        }
        else if(!uv){
            B={U,Y,U,get_rt(U,V,U,V)};
            A={X,V,get_dn(U-1,V,U-1,V),V};
        }
        else{
            B={U,Y,U,V};
            A[0]=X,A[2]=get_dn(U-1,Y,U-1,V);
            A[1]=A[3]=get_lt(A[0],Y,A[2],Y);
        }
        print();
        return 0;
    }
    //cout << "Second\n";
    int XY=get(X+1,Y+1,U,V),XV=get(X+1,Y,U,V-1),UY=get(X,Y+1,U-1,V),UV=get(X,Y,U-1,V-1);
    if(!XY){
        A={get_up(X,Y,X,Y),Y,U,Y};
        B={X,get_lt(X,Y,X,Y),X,V};
        print();
        return 0;
    }
    if(!XV){
        A={get_up(X,V,X,V),V,U,V};
        B={X,Y,X,get_rt(X,V,X,V)};
        print();
        return 0;
    }
    if(!UY){
        A={X,Y,get_dn(U,Y,U,Y),Y};
        B={U,get_lt(U,Y,U,Y),U,V};
        print();
        return 0;
    }
    if(!UV){
        A={X,V,get_dn(U,V,U,V),V};
        B={U,Y,U,get_rt(U,V,U,V)};
        print();
        return 0;
    }
    //cout << "Third\n";
    A[0]=X,A[2]=U;
    B[1]=Y,B[3]=V;
    if(!xy){
        A[1]=A[3]=get_lt(X,Y,X,Y);
        B[0]=B[2]=get_up(X,Y,X,Y);
    }
    else if(!uy){
        A[1]=A[3]=get_lt(U,Y,U,Y);
        B[0]=B[2]=get_dn(U,Y,U,Y);
    }
    else if(!uv){
        A[1]=A[3]=get_rt(U,V,U,V);
        B[0]=B[2]=get_dn(U,V,U,V);
    }
    else if(!xv){
        A[1]=A[3]=get_rt(X,V,X,V);
        B[0]=B[2]=get_up(X,V,X,V);
    }
    print();
    return 0;
}
