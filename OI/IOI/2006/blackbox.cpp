#include "blackbox.h"
#include<bits/stdc++.h>
using namespace std;

int N;
char init[32][32],cur[32][32];
void reset(){
    ResetBox();
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) cur[i][j]=init[i][j];
}
void toggle(){
    ToggleDeflectors();
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(cur[i][j]=='/' || cur[i][j]=='\\') cur[i][j]^='/'^'\\';
}

int T;
int h_out,s_out,c_out,cnt;

void right_send(int i,int j,int t){
    if(i<0 || j<0){
        if(t) c_out = throwBall((T?i+1:N-i),(T?4:2),h_out,s_out);
        else c_out = throwBall((T?j+1:N-j),(T?1:3),h_out,s_out);
        return;
    }
    int x=i,y=j;
    while(x>=0 && y>=0){
        x-=t;y-=!t;
        if(cur[x][y]^'.') break;
    }
    right_send(x,y,!t);
    cur[i][j]^='/'^'\\';
    cnt++;
}
void left_send(int i,int j,int t){
    if(i<0 || j>=N){
        if(t) h_out=(T?i+1:N-i),s_out=(T?2:4);
        else h_out=(T?j+1:N-j),s_out=(T?1:3);
        return;
    }
    int x=i,y=j;
    while(x>=0 && y<N){
        x-=t,y+=!t;
        if(cur[x][y]^'.') break;
    }
    cnt++;
    left_send(x,y,!t);
    cur[i][j]^='/'^'\\';
}

void left_fix(int x,int y);
void right_fix(int x,int y);
void fix_all(int x,int y);

void left_fix(int x,int y){
    if(cur[x][y]^'/') return;
    fix_all(x,y);
    int j=y;
    while(--j>=0) if(cur[x][j]^'.') break;
    right_send(x,j,1);
    left_send(x,y,1);
}
void right_fix(int x,int y){
    if(cur[x][y]^'\\') return;
    for(int j=y+1;j<N;j++) right_fix(x,j);
    for(int i=x-1;i>=0;i--){
        for(int j=y;j>=0;j--) left_fix(i,j);
        for(int j=y+1;j<N;j++) right_fix(i,j);
    }
    int i=x;
    while(--i>=0) if(cur[i][y]^'.') break;
    right_send(i,y,0);
    left_send(x,y,0);
}

void fix_all(int x,int y){
    for(int i=y-1;i>=0;i--) left_fix(x,i);
    for(int i=x-1;i>=0;i--){
        for(int j=y;j<N;j++) right_fix(i,j);
        for(int j=y-1;j>=0;j--) left_fix(i,j);
    }
}

void get(){
    memset(init,'?',sizeof(init));
    for(int i=0;i<(N+T)/2;i++){
        int pi=i,pj=-1;
        for(int j=0;j<N;j++){
            reset();
            fix_all(i,j);
            cnt=0;cur[i][j]='/';
            left_send(i,j,1);
            int cs=s_out,ch=h_out;
            right_send(pi,pj,1);

            if(cs==s_out && ch==h_out && cnt==c_out){
                init[i][j]='/';
                pi=i,pj=j;
                continue;
            }

            reset();
            toggle();
            fix_all(i,j);
            cnt=0;cur[i][j]='/';
            left_send(i,j,1);
            cs=s_out,ch=h_out;
            right_send(pi,pj,1);
            if(cs==s_out && ch==h_out && cnt==c_out){
                init[i][j]='\\';
                pi=i,pj=j;
                continue;
            }

            init[i][j]='.';
        }
    }
}

void solve(vector<string> &ans){
    N=(int)ans.size();
    T=1;get();
    for(int i=0;i<(N+1)/2;i++) for(int j=0;j<N;j++) ans[i][j]=init[i][j];
    T=0;get();
    for(int i=(N/2)-1;i>=0;i--) for(int j=N-1;j>=0;j--) ans[N-i-1][N-j-1]=init[i][j];
}
