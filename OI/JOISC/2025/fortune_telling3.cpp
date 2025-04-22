#include "Anna.h"
#include "Bruno.h"
#include<bits/stdc++.h>
using namespace std;
const int mxL = 14;
/*
int ptr=0;
vector<int> Card;
vector<int> D;

int DrawCard(int i){
    if(i!=-1){
        //cout << "add " << i << ' ' << D[ptr-1] << '\n';
        Card.insert(Card.begin()+i,D[ptr-1]);
    }
    return D[ptr++];
}
*/

vector<int> base={1,31,165,463,2000};

int f(int n,int k){
    int res=1;
    for(int i=0;i<k;i++) res*=(n-i);
    for(int i=1;i<=k;i++) res/=i;
    return res;
}

void Anna(int N){
    int k=0;
    array<int,2> cnt={0,0};
    
    int X=DrawCard(-1);

    vector<int> card;
    auto init = [&](int sz){
        for(int i=0;i<sz;i++){
            if(X){
                cnt[X]++;
                if(cnt[X]==base[k]){
                    X=DrawCard((int)card.size());
                    card.push_back(1);
                    k++;
                }
                else X=DrawCard(-1);
            }
            else{
                if(cnt[X]<4){
                    cnt[X]++;
                    X=DrawCard(0);
                    card.insert(card.begin(),0);
                }
                else X=DrawCard(-1);
            }
        }
    };

    init(N-9);
    //cout << cnt[0] << ' ' << cnt[1] << ' ' << k << '\n';


    int K=9;
    if(cnt[0]<4){
        init(3);K=6;
        if(cnt[0]<4){
            for(int i=0;i<6;i++){
                if(X) X=DrawCard(0);
                else X=DrawCard(-1);
            }
            return;
        }
    }
    else if(cnt[1]==0){
        for(int i=1;i<=9;i++){
            if(!X) X=DrawCard(0);
            else X=DrawCard(-1);
        }
        return;
    }
    else{
        while(cnt[0]+k+K>mxL){
            if(X){
                cnt[X]++;
                if(cnt[X]==base[k]){
                    X=DrawCard((int)card.size());
                    card.push_back(1);
                    k++;
                }
                else X=DrawCard(-1);
            }
            else X=DrawCard(-1);
            K--;
        }
    }

    int val=cnt[1]-base[k-1];
    //cout << val << ' ' << K << ' ' << k << '\n';
    while(K){
        if(val>=f(K+k,k)) val-=f(K+k,k);
        else break;
        val+=X;K--;
        X=DrawCard(-1);
    }

    auto add = [&](int lst){
        if(X){
            if(!lst) return 0;
            for(int i=0;i<(int)card.size();i++){
                if(!card[i]){
                    lst--;
                    if(!lst) return i+1;
                }
            }
        }
        else{
            if(!lst) return (int)card.size();
            for(int i=(int)card.size()-1;i>=0;i--){
                if(card[i]){
                    lst--;
                    if(!lst) return i;
                }
            }
        }
        return -1;
    };
    int lst=0;
    while(K){
        //cout << val << ' ' << K << ' ' << k << ' ' << lst << '\n';
        assert(lst<=k);
        if(val>=f(K-1+k-lst,k-lst)) val-=f(K-1+k-lst,k-lst),lst++;
        else{
            int pos=add(lst);
            card.insert(card.begin()+pos,X);
            X=DrawCard(pos);
            K--;
        }
    }
}

int Bruno(int N, int L, std::vector<int> C){
    array<int,2> cnt={0,0};
    for(int i=0;i<L;i++) cnt[C[i]]++;

    if(cnt[1]==0) return 9-(cnt[0]-4);
    else if(cnt[0]<4) return (N-6)-cnt[0]+cnt[1]-4;

    int k=0,cur=0;
    for(int i=0;i<L;i++){
        cur+=!C[i];
        if(cur>=4) k+=C[i];
    }
    k=min(k,4);
    int res=base[k-1];
    vector<int> val(k+1);

    cur=4;
    vector<bool> wall(L);
    for(int i=0;i<L;i++) if(!C[i] && cur) wall[i]=true,cur--;

    cur=k;
    for(int i=L-1;i>=0;i--) if(C[i] && cur) wall[i]=true,cur--;

    //cout << k << '\n';

    int sz=L-4-k;

    cur=0;
    for(int i=0;i<L;i++){
        if(wall[i]){
            cur++;
            continue;
        }
        if(C[i]) val[cur]++;
    }

    cur=0;
    for(int i=L-1;i>=0;i--){
        if(wall[i]){
            cur++;
            continue;
        }
        if(!C[i]) val[cur]++;
    }   

    int lim=mxL-4-k;
    for(int i=sz+1;i<=lim;i++) res+=f(i+k,k);

    for(int i=0;i<=k;i++){
        sz-=val[i];
        if(sz) res+=f(sz-1+k-i,k-i);
    }
    return res+cnt[1]-k;
}

/*
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(1);
int rand(int l,int r){
    return l+rng()%(r-l+1);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    int N=900;
    while(true){

        int S=rand(0,N);
        D.assign(N,0);
        for(int i=0;i<S;i++) D[i]=1;
        shuffle(D.begin(),D.end(),rng);
        for(int i=N-9;i<N;i++) cout << D[i];
        cout << '\n';
        Card.clear();
        
        ptr=0;
        Anna(N);
        int L=(int)Card.size();

        for(int i=0;i<L;i++) cout << Card[i];
        cout << '\n';

        int res=Bruno(N,L,Card);
        
        cout << S << ' ' << res << endl;
        if(S!=res) break;
        
    }
}
*/