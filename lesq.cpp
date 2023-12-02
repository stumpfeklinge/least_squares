#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <math.h>
#include <complex>
#include <locale>
#include "GnuP.h"
using namespace std;
float summ(float* t, int y,int nt)
{
float sum = 0;
1
for (int i = 0; i < nt; i++)
{
sum += pow(t[i], y);
}
return sum;
}
float suma(float* z, float* t, int y,int nt)
{
float sum = 0;
for (int i = 0; i < nt; i++)
{
sum += z[i] * pow(t[i], y);
}
return sum;
}
int main()
{
setlocale(LC_ALL, "rus");
float rar = 0;
float rar1 = 0;
float rar2 = 0;
float rar3 = 0;
int n = 5;
int i, j, k, r;
float* B;
float** A;
FILE* fz;
int iz, nz; float* Z;
fz = fopen("Z.dat", "rb");
fread(&nz, sizeof(int), 1, fz);
Z = new float[nz];
fread(Z, sizeof(float), nz, fz);
fclose(fz);
FILE* f;
2
int it, nt; float* T;
f = fopen("T.dat", "rb");
fread(&nt, sizeof(int), 1, f);
cout << "Кол-во эксперементальных значений = " << nt << "\n";
T = new float[nt];
fread(T, sizeof(float), nt, f);
fclose(f);
cout << "Массив значений Z: ";
for (i = 0; i < nt; i++)
{
cout << Z[i] << " ";
}
cout << "" << endl;
cout << "Массив значений t: ";
for (i = 0; i < nt; i++)
{
cout << T[i] << " ";
}
cout << "" << endl;
B = new float[n];
A = new float* [n];
for (i = 0; i < n; i++)
A[i] = new float[n];
for (i = 0; i < n; i++)
{
for (j = 0; j < n; j++)
{
if (i == 0 and j == 0)
A[i][j] = nt;
else
A[i][j] = summ(T, (i + j),nt);
}
}
for (i = 0; i < n; i++)
3
{
for (j = 0; j < n; j++)
{
if (j == 2)
A[i][j] = 0;
}
}
cout << "Для определения параметров функциональной зависимости нужно";
cout << "решеить матричное ур-ие A*B=0" << endl;
cout << "Матрица А:" << endl;
for (i = 0; i < n; cout << "" << endl, i++)
{
for (j = 0; j < n; j++)
{
cout << A[i][j] << " ";
}
}
for (i = 0; i < n; i++)
{
if (i == 0)
B[i] = summ(Z, 1,nt);
else
B[i] = suma(Z, T, i,nt);
}
cout << "Матрица B:" << endl;
for (i = 0; i < n; i++)
{
cout << B[i] << endl;
}
float* x;
x = new float[n];
float c, M, s;
float max;
float** a, * b;
a = new float* [n];
4
for (i = 0; i < n; i++)
a[i] = new float[n];
b = new float[n];
for (i = 0; i < n; i++)
for (j = 0; j < n; j++)
a[i][j] = A[i][j];
for (i = 0; i < n; i++)
b[i] = B[i];
for (k = 0; k < n; k++)
{
if (k != 2)
{
max = fabs(a[k][k]);
r = k;
for (i = k + 1; i < n; i++)
if (abs(a[i][k]) > max)
{
max = fabs(a[i][k]);
r = i;
}
for (j = 0; j < n; j++)
{
c = a[k][j];
a[k][j] = a[r][j];
a[r][j] = c;
}
c = b[k];
b[k] = b[r];
b[r] = c;
for (i = k + 1; i < n; i++)
{
for (M = a[i][k] / a[k][k], j = k; j < n; j++)
a[i][j] -= M * a[k][j];
b[i] -= M * b[k];
}
}
}
5
for (i = n - 1; i >= 0; i--)
{
if (i != 2)
{
for (s = 0, j = i + 1; j < n; j++)
s += a[i][j] * x[j];
x[i] = (b[i] - s) / a[i][i];
}
else
x[i] = 0;
}
float mx = summ(T, 1,nt) / nt;
float my = summ(Z, 1,nt) / nt;
for (i = 0; i < nt; i++)
{
rar1 += (T[i] - mx) * (Z[i] - my);
rar2 += pow((T[i] - mx), 2);
rar3 += pow((Z[i] - my), 2);
}
rar = rar1 / (sqrt(rar2 * rar3));
cout << "Функциональная зависимость: ";
cout << "Z = " << x[4] << "*t^4 + " << x[3] << "*t^3 + ";
cout << x[2] << "*t^2 + " << x[1] << "*t + " << x[0] << endl;
float a1, a0;
a1 = (nt * suma(Z, T, 1,nt) - summ(T, 1,nt) * summ(Z, 1,nt)) / (nt * summ(T, 2,nt)a0 = summ(Z, 1,nt) / nt - a1 * summ(T, 1,nt) / nt;
cout << "Линия регрессии: " << "Z= " << a0 << " + " << a1 << "*t" << endl;
float suml = 0;
float srl = 0;
for (i = 0; i < nt; i++)
{
suml += (Z[i] - a0 - a1 * T[i]) * (Z[i] - a0 - a1 * T[i]);
}
srl = suml / nt;
float sumf = 0;
6
float srf = 0;
for (i = 0; i < nt; i++)
{
sumf += (Z[i] - x[4] * pow(T[i], 4) - x[3] * pow(T[i], 3) - x[2] * pow(T[i], 2) -}
srf = sumf / nt;
float otnk = 0;
for (i = 0; i < nt; i++)
{
otnk += Z[i];
}
otnk /= nt;
float chil = 0;
float znam = 0;
for (int i = 0; i < nt; i++)
{
chil += pow(Z[i] - x[4] * pow(T[i], 4) - x[3] * pow(T[i], 3) - x[2] * T[i] * T[i]znam += pow(Z[i] - my, 2);
}
float nel = sqrt(1 - chil / znam);
cout << "Суммарная квадратичная ошибка для линии регрессии = " << suml << endl;
cout << "Средняя квадратичная ошибка для линии регрессии = " << srl << endl;
cout << "Относительная ошибка для линии регрессии = " << srl / otnk * 100 << "%" <cout << "Коэффициент корреляции для линии регрессии = " << rar << endl;
cout << "Суммарная квадратичная ошибка для функциональной зависимости = " << sumfcout << "Средняя квадратичная ошибка для функциональной зависимости = " << srf <<cout << "Относительная ошибка для функицональной зависимости = " << srf / otnk * 1cout << "Индекс кореляции для функциональной зависимости = " << nel << endl;
GnuP p;
int a01 = a0;
int a02 = abs(a0 * 10000 - a01 * 10000);
int a11 = a1;
int a12 = abs(a1 * 10000 - a11 * 10000);
7
string lin = to_string(a01) + "." + to_string(a02) + "+" + to_string(a11) + "." +int x41 = x[4];
int x42 = abs(x[4] * 10000 - x41 * 10000);
int x31 = x[3];
int x32 = abs(x[3] * 10000 - x31 * 10000);
int x11 = x[1];
int x12 = abs(x[1] * 10000 - x11 * 10000);
int x01 = x[0];
int x02 = abs(x[0] * 10000 - x01 * 10000);
string funk = to_string(x41) + "." + to_string(x42) + "*x*x*x*x+" + to_string(x31)p.plotFuncPar(lin, 2, 3, 8, "Линейная зависимость");
p.plotFuncPar(funk, 2, 3, 6, "Функциональная зависимость");
p.plotArrayPar(9, T, Z, 1, 2, 11, "Эксперементальные точки");
p.plot();
}
