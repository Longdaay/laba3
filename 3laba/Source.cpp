#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void print_Matrix(vector<vector<int> > matrix, unsigned int row, unsigned int col) // ������� ������ ������� - ��������� �� ���� �������, ���������� �����, ���������� ��������
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

	for (int i = 0; i < mat_n; i++) // ���� ��� �������� �����
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
	for (int i = 0; i < mat_n; i++) // ���� ��� �������� ��������
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
// ������� ������ �������
void PrintMatr(int** mas, int m) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}
// ��������� ������� ��� i-� ������ � j-�� �������
void GetMatr(int** mas, int** p, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) { // �������� ������� ������
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) { // �������� ������� �������
			if (kj == j)
			{
				dj = 1;
			}
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}
// ����������� ���������� ������������
int Determinant(int** mas, int m) {
	int i, j, d, k, n;
	int** p;
	p = new int* [m];
	for (i = 0; i < m; i++)
		p[i] = new int[m];
	j = 0; d = 0;
	k = 1; //(-1) � ������� i
	n = m - 1;
	if (m < 1) cout << "������������ ��������� ����������!";
	if (m == 1) {
		d = mas[0][0];
		return(d);
	}
	if (m == 2) {
		d = mas[0][0] * mas[1][1] -(mas[1][0] * mas[0][1]);
		return(d);
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			GetMatr(mas, p, i, 0, m);
			cout << mas[i][j] << endl;
			PrintMatr(p, n);
			d = d + k * mas[i][0] * Determinant(p, n);
			k = -k;
		}
	}
	return(d);
}
int main()
{
	setlocale(0, ""); // �����������
	unsigned int row = 4; // ���������� ��� ���������� �����
	unsigned int col = 4; // ���������� ��� ���������� ��������
	unsigned int mat_n = 3; // N-�� ������� �������
	int temp;

	/*
	cout << endl << "������� ���������� ����� � �������: ";
	cin >> row;
	cout << "������� ���������� �������� � �������: ";
	cin >> col;
	cout << "\n";
	*/
	vector<vector<int> > tab_1(row); // ������� ��������� ������
	vector<vector<int> > tab_2(mat_n); // ������� ��������� ������ N-�� �������

	srand(time(0));
	/// �������� �������������� ������� - MxN �� �������
	for (int i = 0; i < row; i++)
	{
		tab_1[i].resize(col); // ��������� ��������� ������ ��� ���������� ��������
		for (int j = 0; j < col; j++)
		{
			tab_1[i][j] = rand() % 20; // �������� �������� ������� 20
		}
	}
	print_Matrix(tab_1, row, col);// ������� �������
	system("pause");

	// 1 ������� - ���������� ����� �� �������� ��������� ������� ������� - ������ �� ���� �������
	cout << "������� 1 - ���������� ����� �� �������� ��������� ������� ������� - ������ �� ���� �������" << endl;

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
	
	// 2 ������� - ����������, �������� �� ������� ���������� ��������� ( ����� �������� ��������� �� ������ ������ = ����� �������� ��������� �� ������� ������� = ����� �������� ��������� �� ���������)
	// �������� ���������� �������
	for (int i = 0; i < mat_n; i++)
	{
		tab_2[i].resize(mat_n); // ��������� ��������� ������ ��� ���������� ��������
		for (int j = 0; j < mat_n; j++)
		{
			tab_2[i][j] = rand() % 20; // �������� �������� ������� 20
		}
	}
	// ���������� ������� ��� �������� ��������
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
		cout << "�������� ������� �� �������� ���������� ���������" << endl;
	else
		cout << "�������� ������� �������� ���������� ���������! ����������" << endl;

	int m, i, j, d;
	int** mas;
	system("chcp 1251");
	system("cls");
	cout << "������� ����������� ���������� �������: ";
	cin >> m;
	mas = new int* [m];
	for (i = 0; i < m; i++) {
		mas[i] = new int[m];
		for (j = 0; j < m; j++) {
			cout << "mas[" << i << "][" << j << "]= ";
			cin >> mas[i][j];
		}
	}
	PrintMatr(mas, m);
	d = Determinant(mas, m);
	cout << "������������ ������� ����� " << d;
	cin.get(); cin.get();

	return 0;
}