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
	double cX, cY, cZ;
	
	int count = 0;
	while (getline(inputf, line)) {
		count++;
	}
	double* x = new double[count], * y = new double[count], *z = new double[count];
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

#pragma omp parallel for
	for (int i = 0; i < count; i++) {
		sumX += x[i];
		sumY += y[i];
		sumZ += z[i];
	}
	cX = sumX / count;
	cY = sumY / count;
	cZ = sumZ / count;
	cout << "Паралел цикл Геометрический центр: x = " << cX << " y = " << cY << " z = " << cZ << '\n';

	sumX = 0, sumY = 0, sumZ = 0;

#pragma omp parallel sections 
{
	#pragma omp section 
	{
		for (int i = 0; i < count; i++) {
			sumX += x[i];
		}
		cX = sumX / count;
	}
	#pragma omp section 
	{
		for (int i = 0; i < count; i++) {
			sumY += y[i];
		}
		cY = sumY / count;
	}
	#pragma omp section 
	{
		for (int i = 0; i < count; i++) {
			sumZ += z[i];
		}
		cZ = sumZ / count;
	}
}

	cout << "Декомпозиция Геометрический центр: x = " << cX << " y = " << cY << " z = " << cZ;

}