#include <cstdlib>
#include <ctime>
#include <stdio.h>




int main(){
	
	std::srand(std::time(0));
	
	int r = std::rand() % 4 + 1;
	
	printf("random: %d\n", r);
	
	return 0;
}