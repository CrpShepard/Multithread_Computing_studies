#include <iostream>
#include <omp.h>
#include <time.h>
#include <random>
#define THREAD_NUM 8
#define MATRIX_SIZE 1000
using namespace std;

int main() {
    omp_set_num_threads(THREAD_NUM);

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 100); // define the range

    int row1 = MATRIX_SIZE,
        row2 = MATRIX_SIZE,
        col1 = MATRIX_SIZE,
        col2 = MATRIX_SIZE;
    double** a, ** b, ** c;
    system("chcp 1251");
    system("cls");
    /*cout << "������� ���������� ����� ������ �������: ";
    cin >> row1;
    cout << "������� ���������� �������� ������ �������: ";
    cin >> col1;
    cout << "������� ���������� ����� ������ �������: ";
    cin >> row2;
    cout << "������� ���������� �������� ������ �������: ";
    cin >> col2;*/
    //#pragma omp parallel 
    //int myid = omp_get_thread_num();
    if (col1 != row2) {
        cout << "��������� ����������!";
        //cin.get(); cin.get();
        return 0;
    }
    // ���� ��������� ������ �������
    a = new double* [row1];
    //cout << "������� �������� ������ �������" << endl;
    for (int i = 0; i < row1; i++) {
        a[i] = new double[col1];
        for (int j = 0; j < col1; j++) {
            a[i][j] = distr(gen);
            //cout << "a[" << i << "][" << j << "]= ";
            //cin >> a[i][j];
        }
    }
    // ����� ��������� ������ �������
    //for (int i = 0; i < row1; i++) {
      //  for (int j = 0; j < col1; j++)
        //    cout << a[i][j] << " ";
        //cout << endl;
    //}
    // ���� ��������� ������ �������
    b = new double* [row2];
    //cout << "������� �������� ������ �������" << endl;
    for (int i = 0; i < row2; i++) {
        b[i] = new double[col2];
        for (int j = 0; j < col2; j++) {
            b[i][j] = distr(gen);
            //cout << "b[" << i << "][" << j << "]= ";
            //cin >> b[i][j];
        }
    }
    // ����� ��������� ������ �������
    //for (int i = 0; i < row2; i++) {
      //  for (int j = 0; j < col2; j++) {
        //    cout << b[i][j] << " ";
        //}
        //cout << endl;
    //}
    // ��������� ������
    clock_t start = clock();
    c = new double* [row1];
    #pragma omp parallel for
    for (int i = 0; i < row1; i++) {
        c[i] = new double[col2];
        for (int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    // ����� ������� ������������
    //cout << "������� ������������" << endl;
    //for (int i = 0; i < row1; i++) {
        //for (int j = 0; j < col2; j++)
            //cout << c[i][j] << " ";
        //cout << endl;
    //}
    //cin.get(); cin.get();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
    }
    
