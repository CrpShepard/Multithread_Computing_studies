#include <iostream>
#include <omp.h>
#define THREAD_NUM 8
using namespace std;

int main() {
	omp_set_num_threads(THREAD_NUM);

	int myid;

#pragma omp parallel
	{
        myid = omp_get_num_threads();
        for (int i = myid - 1; i >= 0; i--)
        {
            #pragma omp barrier
            {
                if (i == omp_get_thread_num())
                {
                    #pragma omp critical
                    cout << "I am thread " << i << endl;
                }
            }
        }
	}
}