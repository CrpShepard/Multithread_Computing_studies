#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <omp.h>
#define THREAD_NUM 8
using namespace std;

int main() {
	omp_set_num_threads(THREAD_NUM);
	system("chcp 1251");
	system("cls");
	string line;
	ifstream inputf("input.txt");

	double sumX = 0, sumY = 0, sumZ = 0;

	int count = 0;
	while (getline(inputf, line)) {
		count++;
	}
	double* x = new double[count], * y = new double[count], * z = new double[count];
	ifstream inputf2("input.txt");
	int i = 0;
	while (getline(inputf2, line)) {

		istringstream is(line);
		double n;
		int pos = 0;
		while (is >> n) {
			if (pos % 3 == 0) x[i] = n;
			if (pos % 3 == 1) y[i] = n;
			if (pos % 3 == 2) z[i] = n;
			pos++;
		}
		i++;
	}

	int k = 0;
#pragma omp parallel for shared(x,y,z) private(k) reduction(+:sumX, sumY, sumZ)
	for (k = 0; k < count; k++) {
		sumX += x[k];
		sumY += y[k];
		sumZ += z[k];
	}
	
	double answer = (sumX + sumY + sumZ) / 3 * count;
	cout << "Глоб сумма Значение: " << answer << '\n';

	sumX = 0, sumY = 0, sumZ = 0;

#pragma omp parallel
	{
#pragma omp critical (first)
		{
			for (int i = 0; i < count; i++) {
				sumX += x[i];
				cout << "first" << '\n';
			}
		}
#pragma omp critical (second) 
		{
			for (int i = 0; i < count; i++) {
				sumY += y[i];
				cout << "second" << '\n';
			}
		}
#pragma omp critical (third) 
		{
			for (int i = 0; i < count; i++) {
				sumZ += z[i];
				cout << "third" << '\n';
			}
		}
	}
	cout << sumX << " " << sumY << " " << sumZ << '\n';
	answer = (sumX + sumY + sumZ) / 3 * count;
	cout << "Крит секции Значение: " << answer << '\n';

}