#include<bits/stdc++.h>
#include "perm.cpp"

int main(){
    return 0;
}

unsigned long long Alice(const std::vector<int> p);
std::vector<int> Bob(const unsigned long long x);

class Grader{
	int n;
	std::vector<int> a;
    void error(const std::string &info){
        std::cout << info << std::endl;
        exit(0);
    }
public:
    Grader(){
    	std::cin >> n;
    	a.resize(n);
		for(int i = 0;i < n;++i){
    		std::cin >> a[i];
		}
		fclose(stdin);
		unsigned long long msg = Alice(a);
		std::vector<int> ans = Bob(msg);
		if(ans.size() != n){
			error("Incorrect answer.");
		}
		for(int i = 0;i < n;++i){
			if(ans[i] != a[i]){
				error("Incorrect answer.");
			}
		}
		std::cout << "Correct." << std::endl;
		exit(0);
    }
}grader;
