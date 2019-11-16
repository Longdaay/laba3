// Лабораторная работа № 3  - Работа с матрицами и определением ранга и детерминанта матрицы
#include <iostream> // для фунций ввода/вывода
#include <vector> // для создания вектора
#include <ctime> // для рандома
#include <fstream> // для потока
#include <chrono> // для расчета времени
#include <Windows.h> // для вывода цветом в консоли 

using namespace std;

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
void print_Matrix(vector<vector<int> > matrix, unsigned int row, unsigned int col) // функция вывода массива - принимает на вход матрицу, количество строк, количество столбцов
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << "\t"; // выводим табуляцией
		}
		cout << "\n";
	}
	cout << "\n";
}
void print_Matrix_first(vector<vector<int> > matrix, unsigned int row, unsigned int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 0)
			{
				SetColor(5, 0);
				cout << matrix[i][j] << "\t"; // выводим табуляцией
				SetColor(7, 0);
			}
			else
				cout << matrix[i][j] << "\t"; // выводим табуляцией
		}
		cout << "\n";
	}
	cout << "\n";
}
int checkdigit()
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
void change_rows(vector<vector<int> >& tab_1, unsigned int first_row, unsigned int second_row, unsigned int col) // функция для смены строк в матрице
{
	int temp;
	for (int i = 0; i < col; i++)
	{
		temp = tab_1[first_row][i];
		tab_1[first_row][i] = tab_1[second_row][i];
		tab_1[second_row][i] = temp;
	}
}
int magic_matrix(vector<vector<int> >& tab_2, unsigned int mat_n) // проверка матрицы на магический квадрат
{
	int summ_temp = 0; // сумма временная
	int summ = 0; // сумма для просчета
	int summ_row; // сумма по строке
	int summ_col; // сумма по столбцу
	int summ_d_main = 0; // сумма по главной диагонали
	int summ_d_sub = 0; // сумма по побочной диагонали

	for (int i = 0; i < mat_n; i++) // цикл для проверки строк
	{
		summ = 0;
		for (int j = 0; j < mat_n; j++)
		{
			summ += tab_2[i][j]; // суммируем все значения в строке
		}
		if (i == 0) // при прохождении первой строки присваеваем сумме сумму по первой строке
			summ_temp = summ;
		else
		{
			if (summ_temp != summ) // сравнимаем суммы - если не равны - выходим из функции с кодом -1
			{
				return - 1;
			}
		}
	}
	summ_row = summ; // если суммы сошлись в прошлом цикле - приравнием главной сумме по строке значение суммы
	for (int i = 0; i < mat_n; i++) // цикл для проверки столбцов
	{
		summ = 0;
		for (int j = 0; j < mat_n; j++) // суммируем все значения в столбце
		{
			summ += tab_2[j][i];
		}
		if (i == 0) // при прохождении первого столбца присваеваем сумме сумму по первому столбцу
			summ_temp = summ;
		else
		{
			if (summ_temp != summ) // сравнимаем суммы - если не равны - выходим из функции с кодом -1
			{
				return - 1;
			}
		}
	}
	summ_col = summ; // если суммы сошлись в прошлом цикле - приравнием главной сумме по столбцу значение суммы
	if (summ_row != summ_col) // сравниваем суммы по строкам и столбцам - если не сошлись - выходим из функции с кодом - 1
	{
		return -1;
	}

	for (int i = 0; i < mat_n; i++) // прогоняем суммы по диагоналям
	{
		summ_d_main += tab_2[i][i]; // суммируем элементы главной диагонали
		summ_d_sub += tab_2[mat_n - i - 1][mat_n - i - 1]; // суммируем элементы побочной диагонали
	}
	if (summ_d_main != summ_d_sub) // сравниваем суммы по диагоналям - если не сошлись - выходим из функции с кодом - 1
	{
		return -1;
	}
	if (summ_row != summ_d_main) // сравниваем суммы по диагналям и по строкам/столбцам - если не сошлись - выходим из функции с кодом - 1
	{
		return -1;
	}
}
// Получение матрицы без i-й строки и j-го столбца
void GetMatr(vector<vector<int> >& mat, vector<vector<int> > &alt_m, int i, int j, int m) // функция для получения временной матрицы без i-ой строки и j-ого столбца - получение минора
{
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
int Determinant(vector<vector<int> > mat, int m, int par) 
{
	int i, j, d, k, n;
	vector<vector<int> > alt_m(m); // создаем временную матрицу
	for (i = 0; i < m; i++)
		alt_m[i].resize(m); // подгоняем ее под необходимую размерность
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = m - 1;
	if (m < 1) cout << "Определитель вычислить невозможно!"; // если размерность < 1 
	if (m == 1) 
	{ // если размерность = 1
		d = mat[0][0];
		return d;
	}
	if (m == 2) 
	{ // если размерность = 2
		d = mat[0][0] * mat[1][1] -(mat[1][0] * mat[0][1]);
		return d;
	}
	if (m > 2) 
	{ // если размерность 2 и более
		for (i = 0; i < m; i++) {
			GetMatr(mat, alt_m, i, 0, m); // функция для получения минора
			if (par == 1) // проверяем, необходимо ли выводить расчет определителя
			{
				cout << "MAT["<< i << "]" <<"[" << j << "] = " << mat[i][j] << endl;
				cout << "Минор MAT[" << i << "]" << "[" << j << "] " << endl;
				print_Matrix(alt_m, n, n);
			}
			d = d + k * mat[i][0] * Determinant(alt_m, n, par); // расчитываем определитель
			k = -k; // меняем знак
		}
	}
	return d;
}
int l_min(int a, int b) // функция для проверки минимального индекса
{
	if (a >= b)return b; else return a;
}

int rang_mat(vector<vector<int> > mat, int i, int j, int par) // функция для просчета ранга

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

				if (!(Determinant(mat_b, q, par) == 0)) // если определитель матрицы отличен от нуля
				{ // то
					r = q; // присваиваем рангу значение q
				}
			}
		}
		q++; // прибавляем 1
	}

	return r;

}
void fill_random_mat(vector<vector<int> >& tab_2, unsigned int row, unsigned int col) // функция для рандомного заполнения матрицы в зависимости от его размерности
{
	tab_2.resize(row); // расширяем матрицу под количество строк
	for (int i = 0; i < row; i++)
	{
		tab_2[i].resize(col); // расширяем матрицу под количество столбцов
		for (int j = 0; j < col; j++)
		{
			tab_2[i][j] = rand() % 20; // рандомим значения кратные 20
		}
	}
}
void fill_mat(vector<vector<int> >& tab_2, unsigned int mat_n) // функция для ручного заполнения матрицы в зависимости от размерности
{
	tab_2.resize(mat_n); // расширяем матрицу под количество строк
	for (int i = 0; i < mat_n; i++) {
		tab_2[i].resize(mat_n); // расширяем матрицу под количество столбцов
		for (int j = 0; j < mat_n; j++) {
			cout << "mas[" << i << "][" << j << "]= ";
			tab_2[i][j] = checkdigit();
		}
		cout << endl;
	}
}
int fill_mat_via_file(vector<vector<int> >& tab_2)
{
	ifstream in("input.txt"); // объявляем потоковую переменную и задаем название текстового файла. Он должен находится в каталоге исходного кода

	if (in.is_open()) //Если открытие файла прошло успешно
	{
		//Вначале посчитаем сколько чисел в файле
		int count = 0; // число чисел в файле
		int temp; //Временная переменная

		while (!in.eof())// пробегаем пока не встретим конец файла eof
		{
			in >> temp; //в пустоту считываем из файла числа
			count++; // увеличиваем счетчик числа чисел
		}

		//Число чисел посчитано, теперь нам нужно понять сколько чисел в одной строке
		//Для этого посчитаем число пробелов до знака перевода на новую строку 

		//Вначале переведем каретку в потоке в начало файла
		in.seekg(0, ios::beg);
		in.clear();

		//Число пробелов в первой строчке вначале равно 0
		int count_space = 0;
		char symbol;
		while (!in.eof()) //на всякий случай цикл ограничиваем концом файла
		{
			//теперь нам нужно считывать не числа, а посимвольно считывать данные
			in.get(symbol); //считали текущий символ
			if (symbol == ' ') count_space++; //Если это пробел, то число пробелов увеличиваем
			if (symbol == '\n') break; //Если дошли до конца строки, то выходим из цикла
		}
		//cout << count_space << endl;

		//Опять переходим в потоке в начало файла
		in.seekg(0, ios::beg);
		in.clear();

		//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.

		//Теперь можем считать матрицу.

		int n = count / (count_space + 1); //число строк
		int m = count_space + 1; //число столбцов на единицу больше числа пробелов

		tab_2.resize(m);
		for (int i = 0; i < n; i++) tab_2[i].resize(m);

		//Считаем матрицу из файла
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> tab_2[i][j];

		in.close(); //под конец закроем файла
		return m;
	}
	else
	{
		//Если открытие файла прошло не успешно
		cout << "Файл не найден." << endl;
		cout << "Файл читается из каталога исходного кода. Закиньте файл туда и следуйте дальнейшим указаниям " << endl;
		system("pause");
		fill_mat_via_file(tab_2);
	}
	
}
int choosefill(vector<vector<int> >& tab_2) // функция выбора заполнения массива
{
	int m;
	unsigned int mat_n;
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // считываем выбранное значение
	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case '1': // рандомное заполнение
			cout << "Введите размерность квадратной матрицы: ";
			mat_n = checkdigit();
			fill_random_mat(tab_2, mat_n, mat_n);
			return mat_n;
			break;

		case '2': // ручное заполнение
			cout << "Введите размерность квадратной матрицы: ";
			mat_n = checkdigit();
			fill_mat(tab_2, mat_n);
			return mat_n;
			break;
		case '3': // заполнение через текстовый файл
			m = fill_mat_via_file(tab_2);
			return m;
			break;
		default: // если число не подходит ни к одному из
			cout << "Число введено неверно. Введите заново" << endl;
			choosefill(tab_2);
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		choosefill(tab_2);
	}
}
void transp_mat(vector<vector<int> >& mat, vector<vector<int> >& tab_2, unsigned int mat_n) // фунция копирования значений из одной матрицы в другую
{
	mat.resize(mat_n); // подгоняем размерность под исходную матрицу
	for (int i = 0; i < mat_n; i++)
	{
		mat[i].resize(mat_n); // расширяем размерность под количество столбцов
	}
	for (int i = 0; i < mat_n; i++)
	{
		for (int j = 0; j < mat_n; j++)
		{
			mat[i][j] = tab_2[i][j];
		}
	}
}
int chooseMatrix(vector<vector<int> >& mat, vector<vector<int> >& tab_2, unsigned int mat_n) // функция выбора заполнения массива
{
	unsigned int m; // переменная для размерности матрицы
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // вводим выбранное значение 
	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case '1': // использовать матрицу из задания №2
			transp_mat(mat, tab_2, mat_n);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, mat_n, mat_n);
			return mat_n;
			break;
		case '2': // рандомное заполнение матрицы
			cout << "Введите размерность квадратной матрицы: ";
			m = checkdigit();
			fill_random_mat(tab_2, m, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '3': // ручное заполнение матрицы
			cout << "Введите размерность квадратной матрицы: ";
			m = checkdigit();
			fill_mat(tab_2, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------Матрица--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '4': // заполнение матрицы из текстового файла
			m = fill_mat_via_file(tab_2);
			transp_mat(mat, tab_2, m);
			return m;
		default: // если число не подходит ни к одному из
			cout << "Число введено неверно. Введите заново" << endl;
			chooseMatrix(mat, tab_2, mat_n);
			break;
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		chooseMatrix(mat, tab_2, mat_n);
	}
}
int checkparam() // функция проверки выбранного действия
{
	int par;
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // вводим выбранное значение 
	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case 'y': // если соглашаемся
			par = 1;
			return par;
			break;
		case 'n': // если отказываемся
			par = 0;
			return par;
			break;
		default: // если число не подходит ни к одному из
			cout << "Значение введено неверно. Введите заново" << endl;
			checkparam();
			break;
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		checkparam();
	}
}
void random_fill(vector<vector<int> >& tab_1, unsigned int row, unsigned int col) // рандомное заполнение матрицы для первого задания
{
	for (int i = 0; i < row; i++)
	{
		tab_1[i].resize(col); // расширяем двумерный массив под количество столбцов
		for (int j = 0; j < col; j++)
		{
			tab_1[i][j] = rand() % 20; // рандомим значения кратные 20
		}
	}
}
void bubble_sort_mat(vector<vector<int> >& tab_1, unsigned int row, unsigned int col) // сортировка матрицы для первого задания
{
	for (int i = 0; i < row; i++) // сортировка пузырьком
	{
		for (int j = 0; j < row; j++)
		{
			if (tab_1[i][0] > tab_1[j][0])
			{
				change_rows(tab_1, i, j, col); // функция для смены строк в матрице
			}
		}
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
	int par = 1; // параметр для проверки необходимости вывода расчета определителя и матрицы
	chrono::steady_clock sc;   // create an object of `steady_clock` class
	double seconds; // переменная, которая хранит в себе время исполнения события
	
	vector<vector<int> > tab_1; // создаем двумерный массив
	vector<vector<int> > tab_2; // создаем двумерный массив N-го порядка
	vector<vector<int> > mat; // создаем массив для расчета определителя и ранга

	while (par == 1)
	{
		system("cls");
		cout << "ЛАБОРАТОРНАЯ РАБОТА № 3 - РАБОТА С МАТРИЦАМИ" << endl << endl;
		cout << "Создание матрицы (значения будут созданы случайным образом (значения кратные 20)" << endl;
		cout << "Введите количество строк в матрице (арабскими цифрами - например 4, 10, 40): ";
		row = checkdigit();
		cout << "Введите количество столбцов в матрице (арабскими цифрами - например 4, 10, 40): ";
		col = checkdigit();
		cout << "\n";

		tab_1.resize(row); // изменяем размерность массива на row
		srand(time(0));

		random_fill(tab_1, row, col); /// создание первоначальной матрицы - MxN на рандоме
		print_Matrix(tab_1, row, col);// выводим матрицу
		system("pause");

		// 1 задание - сортировка строк по убыванию элементов первого столбца - вместе со всей строкой
		cout << endl << "---------Задание 1 - сортировка строк по убыванию элементов первого столбца - вместе со всей строкой---------" << endl << endl;

		bubble_sort_mat(tab_1, row, col);
		print_Matrix_first(tab_1, row, col); // выводим полученную матрицу
		system("pause");

		// 2 задание - определить, является ли матрица магическим квадратом ( сумма значений элементов по каждой строке = сумма значений элементов по каждому столбцу = сумма значений элементов по диагналям)
		// создадим квадратную матрицу
		cout << endl << "---------Задание 2 - определить, является ли матрица магическим квадратом ( сумма значений элементов по каждой строке = сумма значений элементов по каждому столбцу = сумма значений элементов по диагналям)---------" << endl << endl;

		cout << "Как вы хотите заполнить данную квадратную матрицу:" << endl;
		cout << "1 - Значения элементов будут заданы рандомно (кратны 20)" << endl;
		cout << "2 - Самостоятельно заполнить значения элементов матрицы" << endl;
		cout << "3 - Загрузить матрицу с помощью текстового файла" << endl << endl;
		cout << "Введите номер одного из вариантов: ";

		mat_n = choosefill(tab_2); // функция для выбора варианта заполнения матрицы - возвращает ее размерность 
		cout << endl << "Созданная квадратная матрица" << endl << endl;

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

		print_Matrix(tab_2, mat_n, mat_n); // выводим матрицу
		if ((magic_matrix(tab_2, mat_n) == -1)) // функция проверка матрицы на магическую принадлежность - возвращает -1 (не является) или 0 (является) 
			cout << "Заданная матрица не является магическим квадратом" << endl << endl;
		else
			cout << "Заданная матрица является магическим квадратом! Поздравляю" << endl << endl;

		// Определитель и ранг матрицы
		cout << "---------Задание 2 - Найти определитель матрицы ---------" << endl;
		cout << "Какую матрицу Вы хотите использовать:" << endl;
		cout << "1 - Созданную матрицу в задании 2" << endl;
		cout << "2 - Новую созданную матрицу (элементы будут созданы рандомно (кратны 20))" << endl;
		cout << "3 - Ввести элементы матрицы самостоятельно" << endl;
		cout << "4 - Загрузить матрицу с помощью текстового файла" << endl;
		m = chooseMatrix(mat, tab_2, mat_n);

		cout << "Необходимо ли Вам показывать расчет определителя и ранга?(y/n) ";
		par = checkparam();

		auto start_d = sc.now();     // устанавливаем начало отсчета времени события
		det = Determinant(mat, m, par);
		cout << "Определитель матрицы равен " << det << endl;
		auto end_d = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span_d = static_cast<chrono::duration<double>>(end_d - start_d);   // высчитываем время, затраченное на событие
		cout << "Время, затраченное на поиск определителя: " << time_span_d.count() << " секунд" << endl << endl;
		cin.get(); cin.get();

		if (par == 1 and m != 1)
			cout << "Расчет ранга" << endl << endl;
		auto start_r = sc.now();     // устанавливаем начало отсчета времени события
		rang = rang_mat(mat, m, m, par);
		cout << "Ранг матрицы равен " << rang << endl;
		auto end_r = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span_r = static_cast<chrono::duration<double>>(end_r - start_r);   // высчитываем время, затраченное на событие
		cout << "Время, затраченное на поиск ранга: " << time_span_r.count() << " секунд" << endl << endl;
		cin.get(); cin.get();

		cout << "Хотите попробовать еще раз? (y/n) ";
		par = checkparam();
	}
	return 0;
}