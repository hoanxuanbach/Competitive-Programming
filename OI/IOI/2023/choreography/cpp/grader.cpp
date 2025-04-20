#include "choreography.h"

#include <cassert>
#include <cstdio>
#include <vector>

int main() {
	int N, M, Q;
	assert(3 == scanf("%d %d %d", &N, &M, &Q));
	
	std::vector<int> P(N);
	for(int i = 0; i < N; i++){
		assert(1 == scanf("%d", &P[i]));
	}

	std::vector<std::pair<int, int>> operations(M + Q);

	for(int l = 0; l < M + Q; l++){
		assert(1 == scanf("%d", &operations[l].first));

		if(operations[l].first < 3 || operations[l].first == 5){
			assert(1 == scanf("%d", &operations[l].second));
		}
	}

	fclose(stdin);

	std::vector<int> res;

	init(N, P);
	for(int l = 0; l < M + Q; l++){
		switch (operations[l].first)
		{
		case 1:
			move_right(operations[l].second);
			break;
		case 2:
			move_left(operations[l].second);
			break;
		case 3:
			swap_places();
			break;
		case 4:
			move_around();
			break;
		case 5:
			res.push_back(get_position(operations[l].second));
			break;
		default:
			break;
		}
	}

	assert((int)res.size() == Q);

	for(int q = 0; q < Q; q++){
		printf("%d\n", res[q]);
	}

	fclose(stdout);
	return 0;
}
