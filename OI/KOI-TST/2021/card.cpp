#include<bits/stdc++.h>
using namespace std;

bool reversal(int N, int M, std::vector<std::string> P)
{
    for(int i=0;i<M;i++) for(int j=0;j<M;j++){
        vector<vector<int>> board;
        for(int x=0;x+i<N;x+=M){
            vector<int> row;
            for(int y=0;y+j<N;y+=M) row.push_back(P[x+i][y+j]=='O');
            board.push_back(row);
        }
        vector<int> row((int)board.size()),col((int)board[0].size());
        for(int x=0;x<(int)board[0].size();x++) col[x]=row[0]^board[0][x];
        for(int x=0;x<(int)board.size();x++) row[x]=col[0]^board[x][0];
        for(int x=0;x<(int)board.size();x++){
            for(int y=0;y<(int)board[0].size();y++){
                if(row[x]^col[y]^board[x][y]) return false;
            }
        }
    }
    return true;
}