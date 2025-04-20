#include "longesttrip.h"
#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
const int maxn=305;
vector<int> cc[maxn];

vector<int> longest_trip(int N, int D)
{
    rng.seed(998244353);
    for(int i=0;i<N;i++) cc[i].clear();
    vector<int> res={0};
    vector<int> s;
    for(int i=1;i<N;i++){
        cc[i].push_back(i);
        s.push_back(i);
    }
    while(!s.empty()){
        int st=-1,cnt=0;
        bool check=false;
        shuffle(s.begin(),s.end(),rng);
        for(int x:s){
            cnt++;
            if(!are_connected({res.back()},cc[x])){
                if(st==-1) st=x;
                else for(int u:cc[x]) cc[st].push_back(u);
            }
            else{
                check=true;
                int l=1,r=(int)cc[x].size();
                while(l<r){
                    int mid=(l+r)>>1;
                    vector<int> v(cc[x].begin(),cc[x].begin()+mid);
                    if(are_connected({res.back()},v)) r=mid;
                    else l=mid+1;
                }
                r--;
                res.push_back(cc[x][r]);
                for(int u:cc[x]) if(u!=cc[x][r]) res.push_back(u);
                break;
            }
        }
        s.erase(s.begin(),s.begin()+cnt);
        if(!check){
            int l=1,r=(int)cc[st].size(),p=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                vector<int> v(cc[st].begin(),cc[st].begin()+mid);
                if(are_connected(res,v)) p=cc[st][mid-1],r=mid-1;
                else l=mid+1;
            }
            if(p==-1){
                if((int)cc[st].size()>(int)res.size()) swap(res,cc[st]);
            }
            else{
                reverse(res.begin(),res.end());
                if(!are_connected({res.back()},{p})){
                    l=1,r=(int)res.size();
                    while(l<r){
                        int mid=(l+r)>>1;
                        vector<int> v(res.begin(),res.begin()+mid);
                        if(are_connected({p},v)) r=mid;
                        else l=mid+1;
                    }
                    res.insert(res.end(),res.begin(),res.begin()+r);
                    res.erase(res.begin(),res.begin()+r);

                }
                res.push_back(p);
                for(int u:cc[st]) if(u!=p) res.push_back(u);
            }
        }
        else if(st!=-1) s.push_back(st);
    }
    return res;
}
