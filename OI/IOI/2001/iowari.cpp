#include<bits/stdc++.h>
using namespace std;
const int N = 7;

int act(vector<int> &state,int i){
    int d=0,cnt=state[i];
    state[i]=0;i=(i+1)%N;
    while(cnt){
        if(cnt==1){
            if(state[i]>=1 && state[i]<=4) d+=state[i]+1,state[i]=0;
            else d--;
            break;
        }
        else{
            if(state[i]==5) d++,state[i]--;
            else cnt--,state[i]++;
        }
        i=(i+1)%N;
    }
    return d;
}

map<vector<int>,pair<int,int>> mp;

int query(vector<int> state){
    if(mp.find(state)!=mp.end()) return mp[state].first;
    int pos=-1,mx=-100;
    for(int i=0;i<N;i++){
        if(!state[i]) continue;
        vector<int> nxt=state;
        int val=act(nxt,i);
        if(*max_element(nxt.begin(),nxt.end())!=0) val-=query(nxt);
        if(val>mx) mx=val,pos=i;
    }
    mp[state]={mx,pos};
    return mx;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    vector<int> state(N);
    for(int i=0;i<N;i++) cin >> state[i];
    int total=0;
    while(true){
        int val=query(state);
        int pos=mp[state].second;
        if(pos<0) break;
        cout << pos+1 << endl;
        total+=act(state,pos);

        //for(int i=0;i<N;i++) cout << state[i] << ' ';
        //cout << endl;

        if(*max_element(state.begin(),state.end())==0) break;

        cin >> pos;pos--;
        total-=act(state,pos);

        //for(int i=0;i<N;i++) cout << state[i] << ' ';
        //cout << endl;
    }
}
