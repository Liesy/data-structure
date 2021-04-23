#include<iostream>
#include<sstream>
#include<string>
#include"illegalParameterValue.h"
using namespace std;

//2020-10-13 matrix类的乘法的重载有问题（逻辑问题），暂未解决

//改变数组长度
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //参数分别是首指针，末指针，目标位置指针
	delete[]arr;
	arr = temp;
}

template<class T>
class matrix//普通矩阵
{
	public:
		//构造函数、析构函数
		matrix(int theRows = 0, int theColumns = 0);
		matrix(const matrix<T>&);//复制构造函数
		~matrix() {};//加上delete[]element会影响输出,暂时无法debug
		//方法
		int get_rows() const { return theRows; }
		int get_columns() const { return theColumns; }
		matrix<T> tranpose();//转置
		//对操作符的重载
		T& operator() (int i, int j) const;//对( )的重载(既可以取值又可以赋值)
		matrix<T>& operator= (const matrix<T>&);//对=的重载
		matrix<T> operator+(const matrix<T>&) const;//对+的重载
		matrix<T> operator-(const matrix<T>&) const;//对-的重载
		matrix<T> operator*(const matrix<T>&) const;//对*的重载
		//辅助方法
		void createMatrix(int i = 3, int j = 3);//创建一个矩阵
		void output();//输出
	private:
		int theRows, theColumns;//行数、列数
		T* element;//存放矩阵元素的数组
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	if (theRows < 0 || theColumns < 0)
		throw illegalParameterValue("rows and columns must be >0");
	//无法生成0行1列和1行0列的矩阵
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw illegalParameterValue("either both or neither rows and columns should be 0");
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows * theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	//创建矩阵
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];
	//复制m的每一个元素
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
	// 输出矩阵特征
	cout << "rows = " << theRows << " columns = " << theColumns << endl;
	//输出矩阵
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
	//返回索引为(i,j)的元素的引用(地址)
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (this != &m)//不能自己赋值自己
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
	//行数、列数相同才能相加
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
	//行数、列数相同才能相减
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
	
	int index_this = 0, index_m = 0, index_multiple = 0;//三个矩阵的索引
	
	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColumns; j++)
		{
			//累加第一项
			T sum = element[index_this] * m.element[index_m];
			//累加其余项
			for (int k = 2; k <= theColumns; k++)
			{
				index_this++;//this中第i行的下一项
				index_m += m.theColumns;//m中第j列的下一项
				sum += element[index_this] * m.element[index_m];
			}
			//存放在结果矩阵的（i,j）中
			multipleMatrix.element[index_multiple++] = sum;
		}
		//结果矩阵的一行运算结束了
		//重新从this下一行和m的第一列开始运算
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
class diagonalMatrix//对角矩阵
{
	public:
		//构造函数、析构函数
		diagonalMatrix(int theN = 3);
		~diagonalMatrix() {};//加上delete[]element会影响输出,暂时无法debug
		//方法
		void createDiagonalMatrix(int theN = 3);//创建对角矩阵
		void output();//输出
		void tranpose() { cout << "the matrix has been tranposed" << endl; }//转置
		//对操作符的重载
		T& operator() (int i, int j) const;//对( )的重载(既可以取值又可以赋值)
		diagonalMatrix<T>& operator= (const diagonalMatrix<T>&);//对=的重载
		diagonalMatrix<T> operator+(const diagonalMatrix<T>&) const;//对+的重载
		diagonalMatrix<T> operator-(const diagonalMatrix<T>&) const;//对-的重载
		diagonalMatrix<T> operator*(const diagonalMatrix<T>&) const;//对*的重载
	private:
		int n;//数组维数
		T* element;//存储对角矩阵的数组
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
	if (theN < 0)
		throw illegalParameterValue("rows and columns must be >= 0");
	n = theN;
	element = new T[n];//只存放对角线的元素
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
	// 输出矩阵特征
	cout << "the dimension of diagonal matrix is " << n << endl;
	//输出矩阵
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
	//返回索引为(i,j)的元素的引用(地址)
}

template<class T>
diagonalMatrix<T>& diagonalMatrix<T>::operator=(const diagonalMatrix<T>& m)
{
	if (this != &m)//不能自己赋值自己
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
	//行数、列数相同才能相加
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
	//行数、列数相同才能相减
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

//稀疏矩阵
template<class T>
struct matrixTerm
{
	//成员
	int row;
	int column;
	T value;
	//重载=
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
		//构造函数、析构函数
		sparseMatrix(int theRows = 3, int theColumns = 3);
		~sparseMatrix() { delete[]Tarray; }
		//方法
		T get(int theRow, int theColumn) const;
		void set(int theRow, int theColumn, const T& value);
		void add(sparseMatrix<T>&);//矩阵加法
		void multiply(sparseMatrix<T>&);//矩阵乘法
		void tranpose();//矩阵转置
		//辅助方法
		void copyMatrix(sparseMatrix<T>&);//复制矩阵
		void createSparseMatrix(int theRows = 3, int theColumns = 3);//创建or重置稀疏矩阵
		void output();//输出矩阵
	private:
		int rows;
		int columns;
		int term;//非零元素个数
		matrixTerm<T>* Tarray;//存放非零元素
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
	cout << rows << ' ' << columns << endl;//输出行数和列数
	for (int i = 0; i < rows; i++)//行数
	{
		for (int j = 0; j < columns; j++)//列数
		{
			int index = 0;//term的索引
			for (; index < term; index++)//遍历非零元素
				if (Tarray[index].row == i + 1 && Tarray[index].column == j + 1)
				{
					cout << Tarray[index].value << ' ';
					break;//找到了，输出，不再遍历
				}
			//没找到，输出0
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
	
	int term_this = term;//this的非零元素会改变，所以先保存他的值
	bool exist = 0;//标记x中的非零元素是否在this中存在
	for (int i = 0; i < x.term; i++)//遍历x的非零元素
	{
		exist = 0;//默认不存在
		for(int j = 0;j<term_this;j++)//遍历x的非零元素
			if (Tarray[j].row == x.Tarray[i].row && Tarray[j].column == x.Tarray[i].column)
			{
				//存在，直接加
				Tarray[j].value += x.Tarray[i].value;
				exist = 1;
				break;//不用继续遍历x了
			}
		if (!exist)//不存在
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

	sparseMatrix resultMatrix(rows, x.columns);//存放结果

	matrixTerm<T>* temp = new matrixTerm<T>[term + x.term];//存放相乘的非零乘积，且不去重
	int index_temp = 0;
	for (int i = 0; i < term; i++)//遍历this的非零元素
		for (int j = 0; j < x.term; j++)//遍历x的非零元素
			if (Tarray[i].row == x.Tarray[j].column)
			{
				//放在temp数组，标识为（行，列）
				temp[index_temp].value = Tarray[i].value * x.Tarray[j].value;
				temp[index_temp].row = Tarray[i].row;
				temp[index_temp].column = x.Tarray[j].column;
				index_temp++;
				continue;
			}

	int index_result = 0;//在result的数组中的索引
	for (int i = 0; i < index_temp; i++)//遍历temp数组
	{
		//寻找result数组中有没有与temp[i]相同索引的元素
		for (int j = 0; j < resultMatrix.term; j++)//遍历result数组
			if (temp[i].row == resultMatrix.Tarray[j].row && temp[i].column == resultMatrix.Tarray[j].column)
				index_result = j;//如果有，定位
			else
				index_result = 0;//找不到，置零

		if (index_result > 0)//找到了,直接加
			resultMatrix.Tarray[index_result].value += temp[i].value;
		else//找不到
		{
			resultMatrix.Tarray[resultMatrix.term] = temp[i];
			resultMatrix.term++;
		}
	}
	copyMatrix(resultMatrix);
	delete[]temp;//释放空间
}

template<class T>
void sparseMatrix<T>::tranpose()
{
	//交换行和列的值即为转置
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

//以下为验证用
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