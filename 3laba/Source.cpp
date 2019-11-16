// Лабораторная работа № 3  - Работа с матрицами и определением ранга и детерминанта матрицы
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void print_Matrix(vector<vector<int> > matrix, unsigned int row, unsigned int col) // функция вывода массива - принимает на вход матрицу, количество строк, количество столбцов
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}
unsigned int checkdigit()
{
	unsigned int digit;
	while (true)
	{
		// вводим число, которое хотим представить в двоичной форме
			cin >> digit; // число целое

		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			cout << "Недопустимое заданное число. Введите число правильно" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
			return digit;
		}
	}
}
void change_rows(vector<vector<int> >& tab_1, unsigned int first_row, unsigned int second_row, unsigned int col)
{
	int temp;
	for (int i = 0; i < col; i++)
	{
		temp = tab_1[first_row][i];
		tab_1[first_row][i] = tab_1[second_row][i];
		tab_1[second_row][i] = temp;
	}
}
int magic_matrix(vector<vector<int> >& tab_2, unsigned int mat_n)
{
	int summ_temp = 0;
	int summ = 0;
	int summ_row;
	int summ_col;
	int summ_d_main = 0;
	int summ_d_sub = 0;

	for (int i = 0; i < mat_n; i++) // цикл для проверки строк
	{
		summ = 0;
		for (int j = 0; j < mat_n; j++)
		{
			summ += tab_2[i][j];
		}
		if (i == 0)
			summ_temp = summ;
		else
		{
			if (summ_temp != summ)
			{
				return - 1;
			}
		}
	}
	summ_row = summ;
	for (int i = 0; i < mat_n; i++) // цикл для проверки столбцов
	{
		summ = 0;
		for (int j = 0; j < mat_n; j++)
		{
			summ += tab_2[j][i];
		}
		if (i == 0)
			summ_temp = summ;
		else
		{
			if (summ_temp != summ)
			{
				return - 1;
			}
		}
	}
	summ_col = summ;
	if (summ_row != summ_col)
	{
		return -1;
	}

	for (int i = 0; i < mat_n; i++)
	{
		summ_d_main += tab_2[i][i];
		summ_d_sub += tab_2[mat_n - i - 1][mat_n - i - 1];
	}
	if (summ_d_main != summ_d_sub)
	{
		return -1;
	}
	if (summ_row != summ_d_main)
	{
		return -1;
	}
}
// Получение матрицы без i-й строки и j-го столбца
void GetMatr(vector<vector<int> >& mat, vector<vector<int> > &alt_m, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
			if (kj == j)
			{
				dj = 1;
			}
			alt_m[ki][kj] = mat[ki + di][kj + dj];
		}
	}
}
// Рекурсивное вычисление определителя
int Determinant(vector<vector<int> > mat, int m) {
	int i, j, d, k, n;
	vector<vector<int> > alt_m(m);
	for (i = 0; i < m; i++)
		alt_m[i].resize(m);
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = m - 1;
	if (m < 1) cout << "Определитель вычислить невозможно!";
	if (m == 1) {
		d = mat[0][0];
		return(d);
	}
	if (m == 2) {
		d = mat[0][0] * mat[1][1] -(mat[1][0] * mat[0][1]);
		return(d);
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			GetMatr(mat, alt_m, i, 0, m);
			cout << mat[i][j] << endl;
			print_Matrix(alt_m , n, n);
			d = d + k * mat[i][0] * Determinant(alt_m, n);
			k = -k;
		}
	}
	return(d);
}
int l_min(int a, int b)
{
	if (a >= b)return b; else return a;
}

int rang_mat(vector<vector<int> > mat, int i, int j)

{
	int r = 0;
	int q = 1;

	while (q <= l_min(i, j)) // проверка: порядок матрицы меньше или равен минимальному из размеров матрицы?
	{ // если да
		vector<vector<int> > mat_b(q); // создаем новую матрицу размера q
		for (int w = 0; w < q; w++)
		{
			mat_b[w].resize(q);
		}
		for (int a = 0; a < (i - (q - 1)); a++) // тут начинается перебор матриц q-го порядка
		{
			for (int b = 0; b < (j - (q - 1)); b++)
			{
				for (int c = 0; c < q; c++)
				{
					for (int d = 0; d < q; d++)
					{
						mat_b[c][d] = mat[a + c][b + d];
					}
				}

				if (!(Determinant(mat_b, q) == 0)) // если определитель матрицы отличен от нуля
				{ // то
					r = q; // присваиваем рангу значение q
				}
			}
		}
		q++; // прибавляем 1
	}

	return r;

}
void fill_random_mat(vector<vector<int> >& tab_2, unsigned int mat_n)
{
	for (int i = 0; i < mat_n; i++)
	{
		tab_2[i].resize(mat_n); // расширяем двумерный массив под количество столбцов
		for (int j = 0; j < mat_n; j++)
		{
			tab_2[i][j] = rand() % 20; // рандомим значения кратные 20
		}
	}
}
void fill_mat(vector<vector<int> >& tab_2, unsigned int mat_n)
{
	for (int i = 0; i < mat_n; i++) {
		tab_2[i].resize(mat_n);
		for (int j = 0; j < mat_n; j++) {
			cout << "mas[" << i << "][" << j << "]= ";
			tab_2[i][j] = checkdigit();
		}
	}
}
int fill_mat_via_file(vector<vector<int> >& tab_2)
{
	ifstream in("input.txt");

	if (in.is_open())
	{
		//Если открытие файла прошло успешно

		//Вначале посчитаем сколько чисел в файле
		int count = 0;// число чисел в файле
		int temp;//Временная переменная

		while (!in.eof())// пробегаем пока не встретим конец файла eof
		{
			in >> temp;//в пустоту считываем из файла числа
			count++;// увеличиваем счетчик числа чисел
		}

		//Число чисел посчитано, теперь нам нужно понять сколько
		//чисел в одной строке
		//Для этого посчитаем число пробелов до знака перевода на новую строку 

		//Вначале переведем каретку в потоке в начало файла
		in.seekg(0, ios::beg);
		in.clear();

		//Число пробелов в первой строчке вначале равно 0
		int count_space = 0;
		char symbol;
		while (!in.eof())//на всякий случай цикл ограничиваем концом файла
		{
			//теперь нам нужно считывать не числа, а посимвольно считывать данные
			in.get(symbol);//считали текущий символ
			if (symbol == ' ') count_space++;//Если это пробел, то число пробелов увеличиваем
			if (symbol == '\n') break;//Если дошли до конца строки, то выходим из цикла
		}
		//cout << count_space << endl;

		//Опять переходим в потоке в начало файла
		in.seekg(0, ios::beg);
		in.clear();

		//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
		//Теперь можем считать матрицу.

		int n = count / (count_space + 1);//число строк
		int m = count_space + 1;//число столбцов на единицу больше числа пробелов

		tab_2.resize(m);
		for (int i = 0; i < n; i++) tab_2[i].resize(m);

		//Считаем матрицу из файла
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> tab_2[i][j];

		//Выведем матрицу
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << tab_2[i][j] << "\t";
			cout << "\n";
		}

		in.close();//под конец закроем файла
		return m;
	}
	else
	{
		//Если открытие файла прошло не успешно
		cout << "Файл не найден.";
	}
	
}
int choosefill(vector<vector<int> >& tab_2)
{
	int m;
	unsigned int mat_n;
	char value[256];
	cin >> value;
	if (strlen(value) == 1)
	{
		switch (value[0])
		{
		case '1':
			cout << "Введите размерность квадратной матрицы: ";
			mat_n = checkdigit();
			fill_random_mat(tab_2, mat_n);
			return mat_n;
			break;

		case '2':
			cout << "Введите размерность квадратной матрицы: ";
			mat_n = checkdigit();
			fill_mat(tab_2, mat_n);
			return mat_n;
			break;
		case '3':
			m = fill_mat_via_file(tab_2);
			return m;
			break;
		default:
			cout << "Число введено неверно. Введите заново" << endl;
			choosefill(tab_2);
		}
	}
	else
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		choosefill(tab_2);
	}
}
void transp_mat(vector<vector<int> >& mat, vector<vector<int> >& tab_2, unsigned int mat_n)
{
	mat.resize(mat_n);
	for (int i = 0; i < mat_n; i++)
	{
		mat[i].resize(mat_n);
	}
	for (int i = 0; i < mat_n; i++)
	{
		for (int j = 0; j < mat_n; j++)
		{
			mat[i][j] = tab_2[i][j];
		}
	}
}
int chooseMatrix(vector<vector<int> >& mat, vector<vector<int> >& tab_2, unsigned int mat_n)
{
	unsigned int m;
	char value[256];
	cin >> value;
	if (strlen(value) == 1)
	{
		switch (value[0])
		{
		case '1':
			transp_mat(mat, tab_2, mat_n);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, mat_n, mat_n);
			return mat_n;
			break;
		case '2':
			cout << "Введите размерность квадратной матрицы: ";
			m = checkdigit();
			fill_random_mat(tab_2, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '3':
			cout << "Введите размерность квадратной матрицы: ";
			m = checkdigit();
			fill_mat(tab_2, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '4':
			m = fill_mat_via_file(tab_2);
			transp_mat(mat, tab_2, m);
			return m;
		default:
			cout << "Число введено неверно. Введите заново" << endl;
			chooseMatrix(mat, tab_2, mat_n);
			break;
		}
	}
	else
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		chooseMatrix(mat, tab_2, mat_n);
	}
}
int main()
{
	setlocale(0, ""); // локализация
	unsigned int row; // переменная для количества строк
	unsigned int col; // переменная для количества столбцов
	unsigned int mat_n; // N-ый порядок матрицы
	unsigned int m; //N-й порядок матрицы после выбора одного из вариантов
	int det; // переменная для определителя
	int rang; // переменная для ранга

	cout << "ЛАБОРАТОРНАЯ РАБОТА № 3 - РАБОТА С МАТРИЦАМИ" << endl << endl;
	cout << "Создание матрицы" << endl;
	cout << endl << "Введите количество строк в матрице (арабски): ";
	row = checkdigit();
	cout << "Введите количество столбцов в матрице: ";
	col = checkdigit();
	cout << "\n";

	vector<vector<int> > tab_1(row); // создаем двумерный массив
	

	srand(time(0));
	/// создание первоначальной матрицы - MxN на рандоме
	for (int i = 0; i < row; i++)
	{
		tab_1[i].resize(col); // расширяем двумерный массив под количество столбцов
		for (int j = 0; j < col; j++)
		{
			tab_1[i][j] = rand() % 20; // рандомим значения кратные 20
		}
	}
	print_Matrix(tab_1, row, col);// выводим матрицу
	system("pause");

	// 1 задание - сортировка строк по убыванию элементов первого столбца - вместе со всей строкой
	cout << "---------Задание 1 - сортировка строк по убыванию элементов первого столбца - вместе со всей строкой---------" << endl;

	for (int i = 0; i < row ; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (tab_1[i][0] > tab_1[j][0])
			{
				change_rows(tab_1, i, j, col);
			}
		}
	}
	print_Matrix(tab_1, row, col);
	system("pause");
	
	// 2 задание - определить, является ли матрица магическим квадратом ( сумма значений элементов по каждой строке = сумма значений элементов по каждому столбцу = сумма значений элементов по диагналям)
	// создадим квадратную матрицу
	cout << endl << "---------Задание 2 - определить, является ли матрица магическим квадратом ( сумма значений элементов по каждой строке = сумма значений элементов по каждому столбцу = сумма значений элементов по диагналям)---------" << endl;

	vector<vector<int> > tab_2; // создаем двумерный массив N-го порядка
	cout << "Как вы хотите заполнить данную квадратную матрицу:" << endl;
	cout << "1 - Значения элементов будут заданы рандомно (кратны 20)" << endl;
	cout << "2 - Самостоятельно заполнить значения элементов матрицы" << endl;
	cout << "3 - Загрузить матрицу с помощью текстового файла" << endl;

	mat_n = choosefill(tab_2);
	cout << "Созданная квадратная матрица" << endl << endl;

	// магический квадрат для проверки значений
	/*tab_2[0].resize(mat_n);
	tab_2[0][0] = 2;
	tab_2[0][1] = 7;
	tab_2[0][2] = 6;

	tab_2[1].resize(mat_n);
	tab_2[1][0] = 9;
	tab_2[1][1] = 5;
	tab_2[1][2] = 1;

	tab_2[2].resize(mat_n);
	tab_2[2][0] = 4;
	tab_2[2][1] = 3;
	tab_2[2][2] = 8;*/

	print_Matrix(tab_2, mat_n, mat_n);
	if ((magic_matrix(tab_2, mat_n) == -1))
		cout << "Заданная матрица не является магическим квадратом" << endl << endl;
	else
		cout << "Заданная матрица является магическим квадратом! Поздравляю" << endl << endl;

	// Определитель матрицы
	cout << "---------Задание 2 - Найти определитель матрицы ---------" << endl;
	cout << "Какую матрицу Вы хотите использовать:" << endl;
	cout << "1 - Созданную матрицу в задании 2" << endl;
	cout << "2 - Новую созданную матрицу (элементы будут созданы рандомно (кратны 20))" << endl;
	cout << "3 - Ввести элементы матрицы самостоятельно" << endl;
	cout << "4 - Загрузить матрицу с помощью текстового файла" << endl;
	vector<vector<int> > mat;
	m = chooseMatrix(mat, tab_2, mat_n);
	

	det = Determinant(mat, m);
	cout << "Определитель матрицы равен " << det;
	cin.get(); cin.get();

	rang = rang_mat(mat, m, m);
	cout << endl << "Ранг матрицы равен " << rang;
	cin.get(); cin.get();

	return 0;
}