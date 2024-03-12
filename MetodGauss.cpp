#include <stdio.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif


int KeepQuantityChangesSystemEquations()
{
	int quantity;
	printf("Введите число переменных и уравнений ");
	std::cin >> quantity;
	return quantity;
}


void ScanMatrix(double** matrix, int quantity)
{
	for (int j = 0; j < quantity; j++)
	{
		printf("Введите значения коэфициентов при %d переменной для всех уравнений\n", j+1);
			for (int i = 0; i < quantity; i++)
			{
				std::cin >> matrix[i][j];
			}
	}
	int j = quantity;
	printf("Введите значение для правой части всех уравнений\n");
	for (int i = 0; i < quantity; i++)
	{
		std::cin >> matrix[i][j];
	}
}


void TriangularMatrix(double** matrix, int quantity)
{
	for (int j = 0; j < quantity - 1; j++)
	{
		if (matrix[j][j] == 0)
		{
			int f = j + 1;
			while (matrix[f][j] == 0)
			{
				f = f + 1;
			}
			double c = 0;
			for (int q = j; q < quantity + 1; q++)
			{
				c = matrix[f][q];
				matrix[f][q] = matrix[j][q];
				matrix[j][q] = c;
			}
		}
		for (int i = j + 1; i < quantity; i++)
		{
			double k = -matrix[i][j] / matrix[j][j];
			for (int n = j + 1; n < quantity + 1; n++)
			{
				matrix[i][n] = matrix[i][n] + matrix[j][n] * k;
			}
			matrix[i][j] = 0;
		}
	}
}



void FindVariables(double** matrix, int quantity)
{
	for (int i = quantity - 1; i >= 0; i--)
	{
		double summa = 0;
		int j = quantity - 1;
		while (j > i)
		{
			summa = summa + matrix[i][j];
			j = j - 1;
		}
		matrix[i][quantity] = matrix[i][quantity] - summa;
		double k = matrix[i][quantity] / matrix[i][i];
		int f = i - 1;
		while (f >= 0)
		{
			matrix[f][i] = matrix[f][i] * k;
			f = f - 1;
		}
		printf("%d переменная = %lf\n", i + 1, k);
	}
}


void Gauss(double** matrix, int quantity)
{
	TriangularMatrix(matrix, quantity);
//	FindVariables(matrix, quantity);
}
/*
void Print(double** matrix, int quantity)
{
	for (int i = 0; i <= quantity; ++i)
	{
		for (int k = 0; k <= quantity; ++k)
		{
			std::cout << matrix[i][k] << ' ';
		}
		std::cout << '\n';
	}
}
*/
int main()
{
#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif
	int quantity = KeepQuantityChangesSystemEquations();
	double** matrix;
	matrix = new double* [quantity];
	for (int i = 0; i < quantity; i++)
	{
		matrix[i] = new double[quantity + 1];
	}
	ScanMatrix(matrix, quantity);
	Gauss(matrix, quantity);
	//Print(matrix, quantity);
	for (int i = 0; i < quantity; i++)
	{
		delete matrix[i];
	}
	delete[]matrix;
	return 0;}