// program.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <clocale>
#include <cmath>

using Matrix = double[50][50];
using namespace std;


// процедура вывода массива
void printMatrix(int n, Matrix a) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout  << a[i][j] << " ";
		}
		cout << '\n';
	}
}

// Процедура считывания массива из файла  
void setMatrix(int &n, Matrix &a) {
	ifstream fin("mas.txt");
	if (!fin.is_open()) {
		cout << "Файл не открыт! Неправильный путь или формат файла";
		exit;
	}
	else {
		fin >> n;
		cout << "Размера массива n = " << n << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fin >> a[i][j];
			}
		}
		printMatrix(n, a);
	}
	fin.close();
}

//Фиксация единичной диоганали L
// процедура нахождения L - нижней и U - верхней треугольной матрицы
void upDownMatrix1(int n, int id, Matrix a, Matrix &u, Matrix &l) {
	//инициализация матриц L и U
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//присвоение матрице L главной диагонали единичные значения
			if (i == j) l[j][i] = 1.0;
			else l[j][i] = 0.0;
			u[j][i] = 0.0;
		}
	}
	//непосредственно разложение
	for (int k = 0; k < n; k++)
	{
		//присвоение матрице U в главной диагонали значения главной диагонали из a
		u[k][k] = a[k][k];
		for (int i = k + 1; i < n; i++)
		{
			// преобразованная формула 1.3
			l[k][i] = a[k][i] / (u[k][k] == 0 ? 1 : u[k][k]);
			u[i][k] = a[i][k];
		}
		for (int i = k + 1; i < n; i++)
		{
			// преобразованная формула 1.2
			for (int j = k + 1; j < n; j++) { 
				a[j][i] = a[j][i] - l[k][i] * u[j][k]; 
			}
		}
	}
	cout << "Матрица L" << id << "\n";
	printMatrix(n, l);
	cout << "\n";
	cout << "Матрица U" << id << "\n";
	printMatrix(n, u);
	cout << "\n";
}

//Фиксация единичной диоганали U
// процедура нахождения L - нижней и U - верхней треугольной матрицы
void upDownMatrix2(int n, int id, Matrix a, Matrix&u, Matrix& l) {
		//инициализация матриц L и U
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j) l[i][j] = 1.0;
			else l[i][j] = 0.0;
			u[i][j] = 0.0;
		}
	}
	//непосредственно разложение
	for (int k = 0; k < n; k++)
	{
		u[k][k] = a[k][k];
		for (int i = k + 1; i < n; i++)
		{
			l[i][k] = a[i][k] / (u[k][k] == 0 ? 1 : u[k][k]);
			u[k][i] = a[k][i];
		}
		for (int i = k + 1; i < n; i++)
		{
			for (int j = k + 1; j < n; j++) {
				a[i][j] = a[i][j] - l[i][k] * u[k][j];
			}
		}
	}
	cout << "Матрица U" << id << "\n";
	printMatrix(n, u);
	cout << "\n";
		cout << "Матрица L" << id << "\n";
		printMatrix(n, l);
		cout << "\n";
		
	
}

// Присвоение значений элементов одного  массива к другому
void equalsMatrix(int n, Matrix a, Matrix &a1) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a1[i][j] = a[i][j];
		}
	}
}

// Процедура умножения двух матриц
void multiplicationMatrix(int n, int id, Matrix &a, Matrix u, Matrix l) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double sum = 0;
			for (int k = 0; k < n; k++) {
				sum += u[k][j] * l[i][k];
			}
			a[i][j] = sum;
		}
	}
	cout << "Матрица A" << id << "\n";
	printMatrix(n, a);
}

//Вывод лямда
void printLambda(int n, Matrix a) {
	for (int i = 0; i < n; i++) {
		cout << "Lambda" << i + 1 << " = " << a[i][i] << "   ";
	}
	cout << "\n";
}


//void vectorMatrix(int n, Matrix a, double lamda) {
	//Matrix l1, l2;
//	for (int i = 0; i < n; i++) {
//		a[i][i] -= lamda;
//	}
	//upDownMatrix2(n, 1, a, l1, l2);
	//cout << -pow(lamda, 3) + pow(lamda, 2) * 6 - 11 * lamda + 6;
	///double* x = new double[n];
	//for (int i = 0; i < n; i++) {
	//	x[i] = 1;
	//}

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		double sum = 0;
	//		for (int k = 0; k < n; k++) {
	//			sum += a[k][j] * x[j];
	//		}
	//		a[i][j] = sum;
	//	}
//	}
	//printMatrix(n, a);
//}

int main(){
	setlocale(LC_ALL, "ru");
	Matrix  a, a1, l, l1, u, u1;
	int n, k, m, exitProgramm = 0;

	// Цикл необходимый для выхоа из программы
	while (exitProgramm == 0) {
		//a1 = a;
		cout << "Фиксация единичной диоганали по L - Нажмите 1" << "\n";
		cout << "Фиксация единичной диоганали по U - Нажмите 2" << "\n";
		cin >> m;
		cout << "Введите значение k = ";
		cin >> k;
		cout << "\n";
		// Считываем матрицу
		setMatrix(n, a);
		//setMatrix(n, a2);
		//Если с клавиатуры было введено 1 то программа выполнится с фиксацией единичной диоганали по L 
		if (m == 1) {
			for (int i = 1; i <= k; i++) {
				cout << "k = " << i << "\n";
				//присвоем значения матрицы а к а1
				equalsMatrix(n, a, a1);
				//раскладываем матрицу а на L и U
				upDownMatrix1(n, i, a1, u, l);
				//присвоем значения матрицы u к u1 и l к l1
				equalsMatrix(n, u, u1);
				equalsMatrix(n, l, l1);
				//Умножение матрицы u1 и l1 
				multiplicationMatrix(n, i, a, u1, l1);
				cout << "\n";
				//Вывод лямда
				printLambda(n, a);
			}
		}
		//Если с клавиатуры было введено ц то программа выполнится с фиксацией единичной диоганали по U
		else if (m == 2) {
			for (int i = 1; i <= k; i++) {
				cout << "k = " << i << "\n";
				//присвоем значения матрицы а к а1
				equalsMatrix(n, a, a1);
				//раскладываем матрицу а на L и U
				upDownMatrix2(n, i, a1, u, l);
				//присвоем значения матрицы u к u1 и l к l1
				equalsMatrix(n, u, u1);
				equalsMatrix(n, l, l1);
				//Умножение матрицы u1 и l1 
				multiplicationMatrix(n, i, a, l1, u1);
				cout << "\n";
				//Вывод лямда
				printLambda(n, a);
			}
			//вернется к началу цикла
		}else {
			m = 0;
		}
		cout << "0 - начать заново" << "\n";
		cout << "Любая клавиша - выход" << "\n";
		cin >> exitProgramm;
	}
		return 0;
		exit;
	
}

