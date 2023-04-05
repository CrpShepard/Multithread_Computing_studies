# Openmp (лаба 1)
Поставить в свойствах проекта openmp_support: YES

#include <omp.h>  
#pragma omp parallel <опции>  
...
  
# MPI (лаба 2)  
## Установка  
Открыть командную консоль (cmd) с правами администратора  
1. Скачать vcpkg "git clone https://github.com/microsoft/vcpkg.git"  
2. Установить vcpkg ".\vcpkg\bootstrap-vcpkg.bat"  
3. (Необязательно) Для установки через Intellisence внутри Visual Studio: "vcpkg integrate install"
4. Установить сам модуль "vcpkg install msmpi:x64-windows"  
  
## Запуск программы  
#include <iostream>  
#include "mpi.h"  
int main(int argc, char** args) {  
	int rank, size;  
  
	MPI_Init(&argc, &args);  
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
	MPI_Comm_size(MPI_COMM_WORLD, &size);  
  
	cout << rank << " " << size;  
  
	MPI_Finalize();  
}  
WIP
