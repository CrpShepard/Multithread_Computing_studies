#include <iostream>
#include <omp.h>
#define THREAD_NUM 8
using namespace std;

int main() {
	omp_set_num_threads(THREAD_NUM);
	const int n = 16000;
	int arr[n], thread[n];
	float b[n];
	
	#pragma omp parallel for
		for (int i = 0; i < n; i++) {
			int myid = omp_get_thread_num();
			thread[i] = myid;
			arr[i] = i;
		}

	#pragma omp parallel for
		for (int i = 1; i < n - 1; i++) {
			b[i] = (arr[i - 1] + arr[i] + arr[i + 1]) / 3.0;
		}

	for (int i = 0; i < n; i++) {
		//cout << "THREAD: " << thread[i] << "  arr[" << i << "]:" << arr[i] << endl;
		cout << b[i] << endl;
	}
}