#include <iostream>
#include <omp.h>
#define THREAD_NUM 8
using namespace std;

int main() {
	omp_set_num_threads(THREAD_NUM);
	
	int myid, a;
	a = 10;
	#pragma omp parallel firstprivate(a)
	{
		myid = omp_get_thread_num();
		printf("Thread%d", myid);
	}
}