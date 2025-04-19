#include<bits/stdc++.h>
using namespace std;

namespace A{
    int X,lst=-1,L=0;
    int cnt[4][4]={
        {-4,-4,-3,-3},
        {-2,0,0,-2},
        {-1,0,0,-1},
        {-4,-4,-3,-3}
    };
}

void InitA(int T, int x) {
    A::X=x;
    for(int i=0;i<30;i++) if(x>>i&1) A::lst=i;
    //cout << "SA " << A::lst << '\n';
    A::lst++;
}

int GameA(int I, int J) {
    I--;J--;
    if(A::cnt[I][J]!=0){
        return A::cnt[I][J];
    }
    else{
        int d=A::L;A::L++;
        if(d<30) d=(A::X>>d)&1;
        else{
            d-=30;d/=2;
            d=(A::lst>>(5-d))&1;
        }
        if(d){
            if(J==1) return -3;
            else return -4;
        }
        else{
            if(I==1) return -1;
            else return -2;
        }
    }
	return -4;
}
const int MaxL=42;

namespace B{
    string S;
    int cnt[4][4]={
        {-4,0,0,-3},
        {0,-4,-3,0},
        {0,-4,-3,0},
        {-4,0,0,-3}
    };
}

void InitB(int T) {

}

int GameB(int I, int J) {
    I--;J--;
	if(B::cnt[I][J]!=0){
        return B::cnt[I][J];
	}
	else{
        //cout << "SB " << (J==0 || J==3) << endl;
        B::S+=(char('0')+(J==0 || J==3));
        if((int)B::S.length()==MaxL){
            int lst=0;
            for(int i=0;i<6;i++){
                if(i) B::S.pop_back();
                lst+=(B::S.back()-'0')<<i;
                B::S.pop_back();
            }
            int p=0;lst--;
            //cout << "SB " << lst << '\n';
            for(int i=0;i<(int)B::S.length();i++) if(B::S[i]=='1') p=i;
            p=(p!=lst);
            int X=0;
            for(int i=p;i<(int)B::S.length();i++) X+=(B::S[i]-'0')<<(i-p);
            return X;
        }
        if(I==0) return -2;
        else if(I==3) return -1;
        else if(J==0) return -4;
        else return -3;
	}
}
