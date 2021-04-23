#include<iostream>
#include<sstream>
#include<string>
#include"illegalParameterValue.h"
using namespace std;

//2020-10-13 matrix��ĳ˷������������⣨�߼����⣩����δ���

//�ı����鳤��
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //�����ֱ�����ָ�룬ĩָ�룬Ŀ��λ��ָ��
	delete[]arr;
	arr = temp;
}

template<class T>
class matrix//��ͨ����
{
	public:
		//���캯������������
		matrix(int theRows = 0, int theColumns = 0);
		matrix(const matrix<T>&);//���ƹ��캯��
		~matrix() {};//����delete[]element��Ӱ�����,��ʱ�޷�debug
		//����
		int get_rows() const { return theRows; }
		int get_columns() const { return theColumns; }
		matrix<T> tranpose();//ת��
		//�Բ�����������
		T& operator() (int i, int j) const;//��( )������(�ȿ���ȡֵ�ֿ��Ը�ֵ)
		matrix<T>& operator= (const matrix<T>&);//��=������
		matrix<T> operator+(const matrix<T>&) const;//��+������
		matrix<T> operator-(const matrix<T>&) const;//��-������
		matrix<T> operator*(const matrix<T>&) const;//��*������
		//��������
		void createMatrix(int i = 3, int j = 3);//����һ������
		void output();//���
	private:
		int theRows, theColumns;//����������
		T* element;//��ž���Ԫ�ص�����
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	if (theRows < 0 || theColumns < 0)
		throw illegalParameterValue("rows and columns must be >0");
	//�޷�����0��1�к�1��0�еľ���
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw illegalParameterValue("either both or neither rows and columns should be 0");
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows * theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	//��������
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];
	//����m��ÿһ��Ԫ��
	copy(m.element, m.element + theRows * theColumns, element);
}

template<class T>
void matrix<T>::createMatrix(int i, int j)
{
	if (theRows != i || theColumns != j)
	{
		delete[]element;
		theRows = i;
		theColumns = j;
		element = new T[theRows * theColumns];
	}
	for (int i = 0; i < theRows * theColumns; i++)
		cin >> element[i];
}

template<class T>
void matrix<T>::output()
{
	// �����������
	cout << "rows = " << theRows << " columns = " << theColumns << endl;
	//�������
	for (int i = 0; i < theRows * theColumns; i++)
	{
		cout << element[i] << ' ';
		if ((i + 1) % theColumns == 0)
			cout << endl;
	}
}

template<class T>
T& matrix<T>::operator()(int i, int j) const
{
	if (i<1 || i>theRows || j<1 || j>theColumns)
		throw illegalParameterValue("matrix index out of bounds");
	return element[(i - 1) * theColumns + j - 1];
	//��������Ϊ(i,j)��Ԫ�ص�����(��ַ)
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (this != &m)//�����Լ���ֵ�Լ�
	{
		delete[]element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		
		copy(m.element, m.element + theRows * theColumns, element);
	}
	return *this;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	//������������ͬ�������
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw illegalParameterValue("matrix size must be the same");

	matrix<T> sumMatrix(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		sumMatrix.element[i] = element[i] + m.element[i];

	return sumMatrix;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
	//������������ͬ�������
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw illegalParameterValue("the size of matrix must be the same");

	matrix<T> minusMatrix(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		minusMatrix.element[i] = element[i] + m.element[i];

	return minusMatrix;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
	if (theColumns != m.theRows)
		throw illegalParameterValue("the size of matrix mismatch");
	
	matrix<T> multipleMatrix(theRows, m.theColumns);
	
	int index_this = 0, index_m = 0, index_multiple = 0;//�������������
	
	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColumns; j++)
		{
			//�ۼӵ�һ��
			T sum = element[index_this] * m.element[index_m];
			//�ۼ�������
			for (int k = 2; k <= theColumns; k++)
			{
				index_this++;//this�е�i�е���һ��
				index_m += m.theColumns;//m�е�j�е���һ��
				sum += element[index_this] * m.element[index_m];
			}
			//����ڽ������ģ�i,j����
			multipleMatrix.element[index_multiple++] = sum;
		}
		//��������һ�����������
		//���´�this��һ�к�m�ĵ�һ�п�ʼ����
		index_this += theColumns;
		index_m = 0;
	}
	return multipleMatrix;
}

template<class T>
matrix<T> matrix<T>::tranpose()
{
	matrix<T> tranposeMatrix(theColumns, theRows);

	int index = 0;
	for (int i = 0; i < theColumns; i++)
		for (int j = 0; j < theRows; j++)
			tranposeMatrix.element[index++] = element[j * theColumns + i];
	
	return tranposeMatrix;
}

template<class T>
class diagonalMatrix//�ԽǾ���
{
	public:
		//���캯������������
		diagonalMatrix(int theN = 3);
		~diagonalMatrix() {};//����delete[]element��Ӱ�����,��ʱ�޷�debug
		//����
		void createDiagonalMatrix(int theN = 3);//�����ԽǾ���
		void output();//���
		void tranpose() { cout << "the matrix has been tranposed" << endl; }//ת��
		//�Բ�����������
		T& operator() (int i, int j) const;//��( )������(�ȿ���ȡֵ�ֿ��Ը�ֵ)
		diagonalMatrix<T>& operator= (const diagonalMatrix<T>&);//��=������
		diagonalMatrix<T> operator+(const diagonalMatrix<T>&) const;//��+������
		diagonalMatrix<T> operator-(const diagonalMatrix<T>&) const;//��-������
		diagonalMatrix<T> operator*(const diagonalMatrix<T>&) const;//��*������
	private:
		int n;//����ά��
		T* element;//�洢�ԽǾ��������
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
	if (theN < 0)
		throw illegalParameterValue("rows and columns must be >= 0");
	n = theN;
	element = new T[n];//ֻ��ŶԽ��ߵ�Ԫ��
}

template<class T>
void diagonalMatrix<T>::createDiagonalMatrix(int theN)
{
	if (n != theN)
	{
		delete[]element;
		n = theN;
		element = new T[n];
	}
	cout << "enter the diagonal elements in order: ";
	for (int i = 0; i < n; i++)
		cin >> element[i];
}

template<class T>
void diagonalMatrix<T>::output()
{
	// �����������
	cout << "the dimension of diagonal matrix is " << n << endl;
	//�������
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				cout << element[i] << ' ';
			else
				cout << 0 << ' ';
		}
		cout << endl;
	}
}

template<class T>
T& diagonalMatrix<T>::operator()(int i, int j) const
{
	if (i<1 || i>n || j<1 || j>n)
		throw illegalParameterValue("matrix index out of bounds");
	if (i == j)
		return element[i - 1];
	else
		return 0;
	//��������Ϊ(i,j)��Ԫ�ص�����(��ַ)
}

template<class T>
diagonalMatrix<T>& diagonalMatrix<T>::operator=(const diagonalMatrix<T>& m)
{
	if (this != &m)//�����Լ���ֵ�Լ�
	{
		delete[]element;
		n = m.n;
		element = new T[n];

		copy(m.element, m.element + n, element);
	}
	return *this;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator+(const diagonalMatrix<T>& m) const
{
	//������������ͬ�������
	if (n != m.n)
		throw illegalParameterValue("matrix size must be the same");

	diagonalMatrix<T> sumMatrix(n);
	for (int i = 0; i < n; i++)
		sumMatrix.element[i] = element[i] + m.element[i];

	return sumMatrix;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator-(const diagonalMatrix<T>& m) const
{
	//������������ͬ�������
	if (n != m.n)
		throw illegalParameterValue("the size of matrix must be the same");

	diagonalMatrix<T> minusMatrix(n);
	for (int i = 0; i < n; i++)
		minusMatrix.element[i] = element[i] + m.element[i];

	return minusMatrix;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator*(const diagonalMatrix<T>& m) const
{
	if (n != m.n)
		throw illegalParameterValue("the size of matrix must be the same");

	diagonalMatrix<T> multipleMatrix(n);
	for (int i = 0; i < n; i++)
		multipleMatrix.element[i] = element[i] * m.element[i];

	return multipleMatrix;
}

//ϡ�����
template<class T>
struct matrixTerm
{
	//��Ա
	int row;
	int column;
	T value;
	//����=
	matrixTerm& operator=(const matrixTerm& x)
	{
		row = x.row;
		column = x.column;
		value = x.value;
		return *this;
	}
};

template<class T>
class sparseMatrix
{
	public:
		//���캯������������
		sparseMatrix(int theRows = 3, int theColumns = 3);
		~sparseMatrix() { delete[]Tarray; }
		//����
		T get(int theRow, int theColumn) const;
		void set(int theRow, int theColumn, const T& value);
		void add(sparseMatrix<T>&);//����ӷ�
		void multiply(sparseMatrix<T>&);//����˷�
		void tranpose();//����ת��
		//��������
		void copyMatrix(sparseMatrix<T>&);//���ƾ���
		void createSparseMatrix(int theRows = 3, int theColumns = 3);//����or����ϡ�����
		void output();//�������
	private:
		int rows;
		int columns;
		int term;//����Ԫ�ظ���
		matrixTerm<T>* Tarray;//��ŷ���Ԫ��
};

template<class T>
sparseMatrix<T>::sparseMatrix(int theRows, int theColumns)
{
	rows = theRows;
	columns = theColumns;
	term = 0;
	Tarray = new matrixTerm<T>[rows * columns];
}

template<class T>
void sparseMatrix<T>::copyMatrix(sparseMatrix<T>& x)
{
	rows = x.rows;
	columns = x.columns; 
	term = x.term;
	for (int i = 0; i < term; i++)
		Tarray[i] = x.Tarray[i];
}

template<class T>
void sparseMatrix<T>::createSparseMatrix(int theRows, int theColumns)
{
	term = 0;
	if (rows != theRows || columns != theColumns)
	{
		delete[]Tarray;
		rows = theRows;
		columns = theColumns;
		Tarray = new matrixTerm<T>[rows * columns];
	}
	T element;
	for (int i = 0; i < rows * columns; i++)
	{
		cin >> element;
		if (element != 0)
		{
			Tarray[term].value = element;
			Tarray[term].row = i / columns + 1;
			Tarray[term].column = i - (i / columns) * columns + 1;
			term++;
		}
	}
}

template<class T>
void sparseMatrix<T>::output()
{
	cout << rows << ' ' << columns << endl;//�������������
	for (int i = 0; i < rows; i++)//����
	{
		for (int j = 0; j < columns; j++)//����
		{
			int index = 0;//term������
			for (; index < term; index++)//��������Ԫ��
				if (Tarray[index].row == i + 1 && Tarray[index].column == j + 1)
				{
					cout << Tarray[index].value << ' ';
					break;//�ҵ��ˣ���������ٱ���
				}
			//û�ҵ������0
			if (index == term)
				cout << 0 << ' ';
		}
		cout << endl;
	}
}

template<class T>
T sparseMatrix<T>::get(int theRow, int theColumn) const
{
	if (theRow<1 || theColumn<1 || theRow>rows || theColumn>columns)
		throw illegalParameterValue("matrix index is out of bounds");
	
	for (int i = 0; i < term; i++)
	{
		if (Tarray[i].row == theRow || Tarray[i].column == theColumn)
			return Tarray[i].value;
		else
			return 0;
	}
}

template<class T>
void sparseMatrix<T>::set(int theRow, int theColumn, const T& value)
{
	if (theRow<1 || theColumn<1 || theRow>rows || theColumn>columns)
		throw illegalParameterValue("matrix index is out of bounds");

	int i = 0;
	for (; i < term; i++)
		if (Tarray[i].row == theRow || Tarray[i].column == theColumn)
		{
			Tarray[i].value = value;
			break;
		}

	if (i >= term)
	{
		changeLength(Tarray, rows * columns, rows * columns + 1);
		term++;
		Tarray[term].row = theRow;
		Tarray[term].column = theColumn;
		Tarray[term].value = value;
	}
}

template<class T>
void sparseMatrix<T>::add(sparseMatrix<T>& x)
{
	if (rows != x.rows || columns != x.columns)
		throw illegalParameterValue("the size of matrix is not matched");
	
	int term_this = term;//this�ķ���Ԫ�ػ�ı䣬�����ȱ�������ֵ
	bool exist = 0;//���x�еķ���Ԫ���Ƿ���this�д���
	for (int i = 0; i < x.term; i++)//����x�ķ���Ԫ��
	{
		exist = 0;//Ĭ�ϲ�����
		for(int j = 0;j<term_this;j++)//����x�ķ���Ԫ��
			if (Tarray[j].row == x.Tarray[i].row && Tarray[j].column == x.Tarray[i].column)
			{
				//���ڣ�ֱ�Ӽ�
				Tarray[j].value += x.Tarray[i].value;
				exist = 1;
				break;//���ü�������x��
			}
		if (!exist)//������
		{
			Tarray[term] = x.Tarray[i];
			term++;
		}
	}
}

template<class T>
void sparseMatrix<T>::multiply(sparseMatrix<T>& x)
{
	if (rows != x.columns)
		throw illegalParameterValue("the size of matrix is out of match");

	sparseMatrix resultMatrix(rows, x.columns);//��Ž��

	matrixTerm<T>* temp = new matrixTerm<T>[term + x.term];//�����˵ķ���˻����Ҳ�ȥ��
	int index_temp = 0;
	for (int i = 0; i < term; i++)//����this�ķ���Ԫ��
		for (int j = 0; j < x.term; j++)//����x�ķ���Ԫ��
			if (Tarray[i].row == x.Tarray[j].column)
			{
				//����temp���飬��ʶΪ���У��У�
				temp[index_temp].value = Tarray[i].value * x.Tarray[j].value;
				temp[index_temp].row = Tarray[i].row;
				temp[index_temp].column = x.Tarray[j].column;
				index_temp++;
				continue;
			}

	int index_result = 0;//��result�������е�����
	for (int i = 0; i < index_temp; i++)//����temp����
	{
		//Ѱ��result��������û����temp[i]��ͬ������Ԫ��
		for (int j = 0; j < resultMatrix.term; j++)//����result����
			if (temp[i].row == resultMatrix.Tarray[j].row && temp[i].column == resultMatrix.Tarray[j].column)
				index_result = j;//����У���λ
			else
				index_result = 0;//�Ҳ���������

		if (index_result > 0)//�ҵ���,ֱ�Ӽ�
			resultMatrix.Tarray[index_result].value += temp[i].value;
		else//�Ҳ���
		{
			resultMatrix.Tarray[resultMatrix.term] = temp[i];
			resultMatrix.term++;
		}
	}
	copyMatrix(resultMatrix);
	delete[]temp;//�ͷſռ�
}

template<class T>
void sparseMatrix<T>::tranpose()
{
	//�����к��е�ֵ��Ϊת��
	int temp;
	temp = rows;
	rows = columns;
	columns = temp;
	for (int i = 0; i < term; i++)
	{
		temp = Tarray[i].row;
		Tarray[i].row = Tarray[i].column;
		Tarray[i].column = temp;
	}
}

//����Ϊ��֤��
int main()
{
	sparseMatrix<int> a, b;
	a.createSparseMatrix(2,3);
	//b.createSparseMatrix(2,3);//ok
	//a.add(b);//ok
	//cout << a.get(1, 1) << endl;//ok
	//a.set(1, 1, 4);//ok
	//a.tranpose();//ok
	a.output();
}