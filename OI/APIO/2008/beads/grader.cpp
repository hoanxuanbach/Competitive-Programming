#include "beads.h"
#include "beads.cpp"
#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> P(M);
  for (int i = 0; i < M; i++) {
    assert(1 == scanf("%d", &P[i]));
  }

  init(N, M, P);

  int Q;
  assert(1 == scanf("%d", &Q));
  for (int i = 0; i < Q; ++i) {
    int K, J;
    assert(2 == scanf("%d %d", &K, &J));
    printf("%d\n", ask(K, J));
  }
  return 0;
}
