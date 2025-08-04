#include "aplusb.h"
#include<bits/stdc++.h>
using namespace std;

vector<int> A,B;
void initialize(std::vector<int> _A, std::vector<int> _B) {
  A=_A;B=_B;
  return;
}

int answer_question(int i, int j) {
  return A[i]+B[j];
}
