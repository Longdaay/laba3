// ������������ ������ � 3  - ������ � ��������� � ������������ ����� � ������������ �������
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

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
unsigned int checkdigit()
{
	unsigned int digit;
	while (true)
	{
		// ������ �����, ������� ����� ����������� � �������� �����
			cin >> digit; // ����� �����

		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			cout << "������������ �������� �����. ������� ����� ���������" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
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
// ��������� ������� ��� i-� ������ � j-�� �������
void GetMatr(vector<vector<int> >& mat, vector<vector<int> > &alt_m, int i, int j, int m) {
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
			alt_m[ki][kj] = mat[ki + di][kj + dj];
		}
	}
}
// ����������� ���������� ������������
int Determinant(vector<vector<int> > mat, int m) {
	int i, j, d, k, n;
	vector<vector<int> > alt_m(m);
	for (i = 0; i < m; i++)
		alt_m[i].resize(m);
	j = 0; d = 0;
	k = 1; //(-1) � ������� i
	n = m - 1;
	if (m < 1) cout << "������������ ��������� ����������!";
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

	while (q <= l_min(i, j)) // ��������: ������� ������� ������ ��� ����� ������������ �� �������� �������?
	{ // ���� ��
		vector<vector<int> > mat_b(q); // ������� ����� ������� ������� q
		for (int w = 0; w < q; w++)
		{
			mat_b[w].resize(q);
		}
		for (int a = 0; a < (i - (q - 1)); a++) // ��� ���������� ������� ������ q-�� �������
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

				if (!(Determinant(mat_b, q) == 0)) // ���� ������������ ������� ������� �� ����
				{ // ��
					r = q; // ����������� ����� �������� q
				}
			}
		}
		q++; // ���������� 1
	}

	return r;

}
void fill_random_mat(vector<vector<int> >& tab_2, unsigned int mat_n)
{
	for (int i = 0; i < mat_n; i++)
	{
		tab_2[i].resize(mat_n); // ��������� ��������� ������ ��� ���������� ��������
		for (int j = 0; j < mat_n; j++)
		{
			tab_2[i][j] = rand() % 20; // �������� �������� ������� 20
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
		//���� �������� ����� ������ �������

		//������� ��������� ������� ����� � �����
		int count = 0;// ����� ����� � �����
		int temp;//��������� ����������

		while (!in.eof())// ��������� ���� �� �������� ����� ����� eof
		{
			in >> temp;//� ������� ��������� �� ����� �����
			count++;// ����������� ������� ����� �����
		}

		//����� ����� ���������, ������ ��� ����� ������ �������
		//����� � ����� ������
		//��� ����� ��������� ����� �������� �� ����� �������� �� ����� ������ 

		//������� ��������� ������� � ������ � ������ �����
		in.seekg(0, ios::beg);
		in.clear();

		//����� �������� � ������ ������� ������� ����� 0
		int count_space = 0;
		char symbol;
		while (!in.eof())//�� ������ ������ ���� ������������ ������ �����
		{
			//������ ��� ����� ��������� �� �����, � ����������� ��������� ������
			in.get(symbol);//������� ������� ������
			if (symbol == ' ') count_space++;//���� ��� ������, �� ����� �������� �����������
			if (symbol == '\n') break;//���� ����� �� ����� ������, �� ������� �� �����
		}
		//cout << count_space << endl;

		//����� ��������� � ������ � ������ �����
		in.seekg(0, ios::beg);
		in.clear();

		//������ �� ����� ������� ����� � ����� � ������� �������� � ������ ������.
		//������ ����� ������� �������.

		int n = count / (count_space + 1);//����� �����
		int m = count_space + 1;//����� �������� �� ������� ������ ����� ��������

		tab_2.resize(m);
		for (int i = 0; i < n; i++) tab_2[i].resize(m);

		//������� ������� �� �����
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> tab_2[i][j];

		//������� �������
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << tab_2[i][j] << "\t";
			cout << "\n";
		}

		in.close();//��� ����� ������� �����
		return m;
	}
	else
	{
		//���� �������� ����� ������ �� �������
		cout << "���� �� ������.";
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
			cout << "������� ����������� ���������� �������: ";
			mat_n = checkdigit();
			fill_random_mat(tab_2, mat_n);
			return mat_n;
			break;

		case '2':
			cout << "������� ����������� ���������� �������: ";
			mat_n = checkdigit();
			fill_mat(tab_2, mat_n);
			return mat_n;
			break;
		case '3':
			m = fill_mat_via_file(tab_2);
			return m;
			break;
		default:
			cout << "����� ������� �������. ������� ������" << endl;
			choosefill(tab_2);
		}
	}
	else
	{
		cout << "���������� ������ ���� ������. ���������� ������ ������" << endl;
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
			cout << "--------------�������--------------" << endl;
			print_Matrix(mat, mat_n, mat_n);
			return mat_n;
			break;
		case '2':
			cout << "������� ����������� ���������� �������: ";
			m = checkdigit();
			fill_random_mat(tab_2, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------�������--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '3':
			cout << "������� ����������� ���������� �������: ";
			m = checkdigit();
			fill_mat(tab_2, m);
			transp_mat(mat, tab_2, m);
			cout << "--------------�������--------------" << endl;
			print_Matrix(mat, m, m);
			return m;
			break;
		case '4':
			m = fill_mat_via_file(tab_2);
			transp_mat(mat, tab_2, m);
			return m;
		default:
			cout << "����� ������� �������. ������� ������" << endl;
			chooseMatrix(mat, tab_2, mat_n);
			break;
		}
	}
	else
	{
		cout << "���������� ������ ���� ������. ���������� ������ ������" << endl;
		chooseMatrix(mat, tab_2, mat_n);
	}
}
int main()
{
	setlocale(0, ""); // �����������
	unsigned int row; // ���������� ��� ���������� �����
	unsigned int col; // ���������� ��� ���������� ��������
	unsigned int mat_n; // N-�� ������� �������
	unsigned int m; //N-� ������� ������� ����� ������ ������ �� ���������
	int det; // ���������� ��� ������������
	int rang; // ���������� ��� �����

	cout << "������������ ������ � 3 - ������ � ���������" << endl << endl;
	cout << "�������� �������" << endl;
	cout << endl << "������� ���������� ����� � ������� (�������): ";
	row = checkdigit();
	cout << "������� ���������� �������� � �������: ";
	col = checkdigit();
	cout << "\n";

	vector<vector<int> > tab_1(row); // ������� ��������� ������
	

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
	cout << "---------������� 1 - ���������� ����� �� �������� ��������� ������� ������� - ������ �� ���� �������---------" << endl;

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
	cout << endl << "---------������� 2 - ����������, �������� �� ������� ���������� ��������� ( ����� �������� ��������� �� ������ ������ = ����� �������� ��������� �� ������� ������� = ����� �������� ��������� �� ���������)---------" << endl;

	vector<vector<int> > tab_2; // ������� ��������� ������ N-�� �������
	cout << "��� �� ������ ��������� ������ ���������� �������:" << endl;
	cout << "1 - �������� ��������� ����� ������ �������� (������ 20)" << endl;
	cout << "2 - �������������� ��������� �������� ��������� �������" << endl;
	cout << "3 - ��������� ������� � ������� ���������� �����" << endl;

	mat_n = choosefill(tab_2);
	cout << "��������� ���������� �������" << endl << endl;

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
		cout << "�������� ������� �� �������� ���������� ���������" << endl << endl;
	else
		cout << "�������� ������� �������� ���������� ���������! ����������" << endl << endl;

	// ������������ �������
	cout << "---------������� 2 - ����� ������������ ������� ---------" << endl;
	cout << "����� ������� �� ������ ������������:" << endl;
	cout << "1 - ��������� ������� � ������� 2" << endl;
	cout << "2 - ����� ��������� ������� (�������� ����� ������� �������� (������ 20))" << endl;
	cout << "3 - ������ �������� ������� ��������������" << endl;
	cout << "4 - ��������� ������� � ������� ���������� �����" << endl;
	vector<vector<int> > mat;
	m = chooseMatrix(mat, tab_2, mat_n);
	

	det = Determinant(mat, m);
	cout << "������������ ������� ����� " << det;
	cin.get(); cin.get();

	rang = rang_mat(mat, m, m);
	cout << endl << "���� ������� ����� " << rang;
	cin.get(); cin.get();

	return 0;
}