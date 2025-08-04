#include "bitstrings.h"
#include<bits/stdc++.h>
using namespace std;

int count_duplicated(std::string S) {
    set<string> ss;
    int N=(int)S.size();
    for(int i=1;i<N;i++){
        for(int j=1;j<=min(i,N-i);j++){
            string A=S.substr(i,j),B=S.substr(i-j,j);
            if(A==B) ss.insert(A);
        }
    }
    return (int)ss.size();
}

std::string find_weakest() {
  return "0001011000111001011000101110001100101100010111001011000111001011100010110001110010110001011100011001";
}

std::string find_strongest() {
  return "1100000000100000000100000001000000001000000010000001000000010000001000001000000100000100001000100100";
}
