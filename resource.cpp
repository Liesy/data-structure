#include<iostream>
#include<cmath>
#include<string>
#include <iomanip>
#include"illegalParameterValue.h"
#include"change array length.h"
using namespace std;

//实验一

//题目一 全排列的异或和
/*
template<class T>
void change(T &a, T &b) //本质是地址的交换
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int value_num = 0; //用于标记这是集合价值数组的第几个元素
template<class T>
void perm(T arr[], T value[], int begin, int end)  // 计算每种排列的价值
{
	T per_value;
	
	if (begin == end)
	{
		per_value = 0;
		for (int i = 0; i < end; i++)
			per_value += (arr[i] ^ (i + 1));
		value[value_num] = per_value;
		value_num++;
	}
	
	else
		for (int i = begin; i < end; i++)
		{
			change(arr[begin], arr[i]);
			perm(arr, value, begin + 1, end);
			change(arr[i], arr[begin]);
		}
}

int main()
{
	int n;
	cin >> n;
	
	int permSum = 1;//排列组合的个数
	for (int i = 2; i <= n; i++)
		permSum *= i;

	int* arr = new int[n];
	int* value = new int[permSum];
	for (int i = 0; i < n; i++) // 初始化
	{
		cin >> arr[i];
		value[i] = 0;
	}
	perm(arr, value, 0, n);

	unsigned long OR = value[0] | value[1];
	for (int i = 2; i < permSum; i++)
		OR |= value[i];
	cout << OR;
}
*/

//题目二 子集的价值
/*
int sign_value_num = 0; //用于标识这是子集价值数组的第几个元素

void calculate(int arr_judge[], int arr_num[], int all_value[], int end)
{
	int sign_subset_num=0; // 用于标识这是子集中的第几个元素
	int subset_value=0; //用于记录该子集的价值

	for (int i = 0; i < end; i++) // 计算子集价值
	{
		if (arr_judge[i])
		{
			sign_subset_num++; //元素个数从1开始
			subset_value += sign_subset_num * arr_num[i];
		}
	}

	all_value[sign_value_num] = subset_value;
	sign_value_num++;
}

void subset(int arr_judge[], int arr_num[], int all_value[],int begin, int end)
{
	for (int i = 0; i <=1; i++)
	{
		arr_judge[begin] = i;
		
		if (begin == end - 1)
			calculate(arr_judge, arr_num, all_value, end);
		else
			subset(arr_judge, arr_num, all_value, begin + 1, end);
	}
}

int main()
{
	int n;
	cin >> n;
	int subsetNum = (int)pow(2, n); //子集个数为2^n个

	int* arr_num = new int[n];
	int* arr_judge = new int[n]; 
	for (int i = 0; i < n; i++)//初始化
	{
		cin >> arr_num[i];
		arr_judge[i] = 0;
	}
	
	int* all_value = new int[subsetNum]; //存放各个子集的价值

	subset(arr_judge, arr_num, all_value, 0, n);

	unsigned long xor_sum = all_value[0] ^ all_value[1]; //求异或和
	for (int i = 2; i < subsetNum; i++)
		xor_sum ^= all_value[i];

	cout << xor_sum;
}
*/


//实验二
//四种排序（名次排序，选择排序，冒泡排序，插入排序）
/*
template<class T>
class Sort
{
	public:
		Sort(){}
		~Sort(){}
		
		void rank(T arr[], int len);
		void selectSort(T arr[],int len);
		void bubbleSort(T arr[],int len);
		void insertSort(T arr[], int len);
};

template<class T>  //名次排序
void Sort<T>::rank(T arr[],int len)
{
	T* rank = new T[len];
	for (int i = 0; i < len; i++)
		rank[i] = 0;
	for (int i = 1; i < len; i++)
		for (int j = 0; j < i; j++)
		{
			if (arr[i] >= arr[j])
				rank[i] += 1;
			else
				rank[j] += 1;
		}
	//输出
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			if (rank[j] == i)
			{
				cout << arr[j] << ' ';
				break;
			}
	delete[]rank;
}

template<class T> //选择排序
void Sort<T>::selectSort(T arr[], int len)
{
	T temp;
	bool sorted = false; //用于判断前面的元素是否已经按顺序排好了
	for (int size = len; (size > 1) && !sorted; size--) //size为数组长度
	{
		int index_max = 0; //存放最大值的下标
		sorted = true;
		for (int j = 1; j < size ; j++)
		{
			if (arr[index_max] <= arr[j])
				index_max = j;
			else
				sorted = false; //
		}
		//将最大值放在相对的最后
		temp = arr[size-1];
		arr[size-1] = arr[index_max];
		arr[index_max] = temp;
	}
	//输出
	for (int i = 0; i < len - 1; i++)
		cout << arr[i] << ' ';
	cout << arr[len - 1] << endl;
}

template<class T> //冒泡排序
void Sort<T>::bubbleSort(T arr[], int len)
{
	T term;
	bool SWAP = true;
	for (int i = 0; i < len - 1 && SWAP; i++)
	{
		SWAP = false;
		for (int j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j + 1])
			{
				term = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = term;
				SWAP = true;
			}
	}
	//输出
	for (int i = 0; i < len - 1; i++)
		cout << arr[i] << ' ';
	cout << arr[len];
}

template<class T> //插入排序
void Sort<T>::insertSort(T arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		T temp = arr[i]; //从第二个元素开始取数
		int j;
		// 从后往前对[0:i]的数组进行比较，找到arr[i]位置，将比arr[i]大的数往后移一个位置
		for (j = i - 1; j >= 0 && arr[j] > temp; j--)
			arr[j + 1] = arr[j]; //此时arr[i]已经被顶替但是值存在temp中
		arr[j + 1] = temp; 
		//j-- 之后 j 的位置是一个比arr[i]小的数，故把temp给arr[j+1]
	}
	//输出
	for (int i = 0; i < len - 1; i++)
		cout << arr[i] << ' ';
	cout << arr[len-1];
}

int main()
{
	int n;
	cin >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	Sort<int>  object;
	object.insertSort(arr, n);
}
*/


//实验三
//线性表的数组描述
/*
struct student //学生类
{
	string name; // 姓名
	string phone; //电话
	int class_num; //班级
	int dorm; //宿舍
};

template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //参数分别是首指针，末指针，目标位置指针
	delete[]arr;
	arr = temp;
}

class linearlist
{
	public:
		//构造函数
		linearlist(int n = 10);
		//析构函数
		~linearlist() { delete []stu; };
		//四种操作
		void insert(string& name, string& phone, int& class_num, int& dorm);
		void erase(string &name);
		void edit_phone(string &name,string &new_info);
		void edit_class_dorm(string& name, int decision, int &new_info);
		bool serch(string &name);
		//计算宿舍号的异或值
		int calculate_xor(int &class_num); 
	private:
		struct student* stu;
		int len; //数组容量
		int size; //元素个数
};

linearlist::linearlist(int n)
{
	stu = new student[n];
	len = n;
	size = 0;
}

void linearlist::insert(string& name, string& phone, int& class_num, int& dorm)
{
	if (len == size)
	{
		changeLength(stu, len, len*2);
		len *= 2;
	}

	stu[size].name = name;
	stu[size].phone = phone;
	stu[size].class_num = class_num;
	stu[size].dorm = dorm;

	size++;
}

void linearlist::erase(string& name)
{
	int index = 0;//name对应的元素的索引
	while (stu[index].name != name && index < size)
		index++;

	copy(stu + index + 1, stu + size, stu + index);
	stu[--size].~student(); //调用析构函数
}

void linearlist::edit_phone(string& name, string& new_info)
{
	int index = 0;
	while (stu[index].name != name && index < size)
		index++;
	stu[index].phone = new_info;
}

void linearlist::edit_class_dorm(string& name, int decision, int &new_info)
{
	int index = 0;
	while (stu[index].name != name && index < size)
		index++;
	
	if (decision == 2)
		stu[index].class_num = new_info;
	else
		stu[index].dorm = new_info;
}

bool linearlist::serch(string& name)
{
	int index = 0; 
	while (stu[index].name != name && index < size)
		index++;

	if (index >= size)
		return 0;
	else
		return 1;
}

//在main函数中无法直接在循环判断中访问size，故写为一个内部方法
int linearlist::calculate_xor(int &class_num)
{
	int result_xor = 0;
	for (int i = 0; i < size; i++)
	{
		if (stu[i].class_num == class_num)
			result_xor ^= stu[i].dorm;
	}
	return result_xor;
}

int main()
{
	int  judge, n, index_result = 0, i = 0;
	string name, phone, new_phone;
	int decision, new_info, dorm, class_num;

	cin >> n;
	int* result = new int[n];
	linearlist s;

	for (i = 0; i < n; i++)
	{
		cin >> judge;
		switch (judge)
		{
			case 0:
				cin >> name >> phone >> class_num >> dorm;
				s.insert(name, phone, class_num, dorm);
				break;
			case 1:
				cin >> name;
				s.erase(name);
				break;
			case 2:
				cin >> name >> decision;
				if (decision == 1)
				{
					cin >> new_phone;
					s.edit_phone(name, new_phone);
				}
				else
				{
					cin >> new_info;
					s.edit_class_dorm(name, decision, new_info);
				}
				break;
			case 3:
				cin >> name;
				result[index_result] = s.serch(name);
				index_result++;
				break;
			case 4:
				cin >> class_num;
				result[index_result] = s.calculate_xor(class_num);
				index_result++;
				break;
			default:
				break;
		}
	}

	for (int j = 0; j < index_result; j++)
	{
		cout << result[j] << endl;
	}

	return 0;
}
*/

//实验四
//线性表的链式描述
/*
//题目一
template<class T>
struct chainNode  //定义节点
{
	//数据成员
	T element;
	chainNode<T>* next;

	//构造函数
	chainNode(const T& element) { this->element = element; }
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};

template<class T>
class chain
{
public:
	//构造函数
	chain(int n= 5);
	//析构函数
	~chain();

	//方法
	void insert(int theIndex,const T& theElement);
	void del(const T& theElement);
	int theIndexOf(int theElement);
	void reverse();
	unsigned long output_xor();
	void combine(chain<T>& a, chain<T>& b);

	//辅助方法
	void create(chainNode<T>* theFirstNode) { firstNode = theFirstNode; }
	int getListSize() { return size; } // 获得元素长度
	void setSize(int theSize) { size = theSize; } // 修改元素长度
	chainNode<T>* getFirstNode() { return firstNode; }//获取该链表的首指针
	void output();
	void insertSort();
protected:
	chainNode<T>* firstNode; //指向首元素的地址
	int size;
};

template<class T>
chain<T>::chain(int n) // 构造函数
{
	if (n <= 0)
	{
		firstNode = NULL;
		size = 0;
	}
	else
	{
		int* num = new int[n];
		for (int i = 0; i < n; i++)
			cin >> num[i];

		chainNode<int>* nextNode;
		chainNode<int>* headNode = new chainNode<int>(num[n - 1], NULL);
		for (int i = n - 2; i >= 0; i--)
		{
			chainNode<int>* newNode = new chainNode<int>(num[i], NULL);
			nextNode = headNode;
			headNode = newNode;
			headNode->next = nextNode;
		}
		firstNode = headNode;
		size = n;
	}
}

template<class T>
chain<T>::~chain() //析构函数
{
	//将下一个节点变为第一个节点，将第一个节点删除
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next; //element的值此时已经无所谓了
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
void chain<T>::output()
{
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL)
	{
		cout << currentNode->element << ' ';
		currentNode = currentNode->next;
	}
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	chainNode<T>* searchNode = firstNode;
	
	if (theIndex == 0)
	{
		newNode->next = firstNode;
		this->create(newNode);
	}
	else
	{
		for (int i = 0; i < theIndex - 1; i++)//找到索引指向的元素的前驱
			searchNode = searchNode->next;
		
		newNode->next = searchNode->next;
		searchNode->next = newNode;
	}
	size++;
}

template<class T>
void chain<T>::del(const T& theElement)
{
	chainNode<T>* searchNode = firstNode;
	
	if (firstNode->element == theElement)
		this->create(firstNode->next);
	else
	{
		//找到要删除元素的前驱
		while (searchNode->next->element != theElement)
			searchNode = searchNode->next;
		searchNode->next = searchNode->next->next;
	}
	size--;
}

template<class T>
int chain<T>::theIndexOf(int theElement)
{
	int last_index = -1; //默认没找到
	chainNode<T>* searchNode = firstNode;
	for (int i = 0; searchNode != NULL; i++)
	{
		if (searchNode->element == theElement)
		{
			last_index = i;
			break;
		}
		else
			searchNode = searchNode->next;
	}
	return last_index;
}

template<class T>
void chain<T>::reverse()
{
	chainNode<T>* dummy = new chainNode<T>(-1, NULL);
	dummy->next = firstNode;//用于固定连接
	chainNode<T>* headNode = firstNode;//第一个元素的节点
	chainNode<T>* reverseNode = headNode->next;//待反转元素的节点
	while (reverseNode != NULL)
	{
		//保存反转元素的下一个节点防止丢失
		headNode->next = reverseNode->next;
		//将待反转元素放在第一个元素的位置
		reverseNode->next = dummy->next;
		dummy->next = reverseNode;
		//反转下一个元素
		reverseNode = headNode->next;
	}
	firstNode = dummy->next;
	delete dummy;
}

template<class T>
unsigned long chain<T>::output_xor()
{
	unsigned long sum_xor = 0;
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < size; i++)
	{
		sum_xor += (i ^ currentNode->element);
		currentNode = currentNode->next;
	}
	return sum_xor;
}
/*
template<class T>
chainNode<T>* creatLinklist(int n=0)
{
	if (n <= 0)
		return NULL;
	else
	{
		int* num = new int[n];
		for (int i = 0; i < n; i++)
			cin >> num[i];

		chainNode<int>* nextNode;
		chainNode<int>* headNode = new chainNode<int>(num[n - 1], NULL);
		for (int i = n - 2; i >= 0; i--)
		{
			chainNode<int>* newNode = new chainNode<int>(num[i], NULL);
			nextNode = headNode;
			headNode = newNode;
			headNode->next = nextNode;
		}
		return headNode;
	}
}
*/
/*
int main()
{
	int n, q;
	cin >> n >> q;
	//创建链表
	chainNode<int>* firstNode = NULL;
	chain<int> element;
	element.setSize(n);
	element.create(firstNode->creatLinklist(n));
	
	int result_index = 0;
	long* result = new long[q];
	int idx, val;
	for (int i = 0; i < q; i++)
	{
		int decision;
		cin >> decision;
		switch (decision)
		{
			case(1):
				cin >> idx >> val;
				element.insert(idx, val);
				break;
			case(2):
				cin >> val;
				element.del(val);
				break;
			case(3):
				element.reverse();
				break;
			case(4):
				cin >> val;
				result[result_index] = element.theIndexOf(val);
				result_index++;
				break;
			case(5):
				result[result_index] = element.output_xor();
				result_index++;
			default:
				break;
		}
	}

	for (int i = 0; i < result_index - 1; i++)
		cout << result[i] << endl;
	cout << result[result_index - 1];
}
*/
//题目二
/*
template<class T>
void chain<T>:: combine(chain<T>& a, chain<T>& b)
{
	firstNode = a.firstNode;
	size = a.size + b.size;
	chainNode<T>* currentNode = firstNode;
	if (currentNode == NULL)
		firstNode = b.firstNode;
	else
	{
		while (currentNode->next != NULL)
			currentNode = currentNode->next;
		currentNode->next = b.firstNode;
	}
}

template<class T>
void chain<T>::insertSort()
{
	if (firstNode != NULL)
	{
		chainNode<T>* unsortedNode_head = firstNode->next;
		firstNode->next = NULL;
		chainNode<T>* un_head_next;
		chainNode<T>* searchNode;//寻找最后一个比它小的元素
		while (unsortedNode_head != NULL)
		{
			un_head_next = unsortedNode_head->next;
			searchNode = firstNode;
			while (searchNode->next != NULL && searchNode->next->element <= unsortedNode_head->element)
				searchNode = searchNode->next;

			if (searchNode == firstNode && searchNode->element > unsortedNode_head->element)
			{
				unsortedNode_head->next = searchNode;
				this->create(unsortedNode_head);//重置firstNode
				unsortedNode_head = un_head_next;
			}
			else
			{
				unsortedNode_head->next = searchNode->next;
				searchNode->next = unsortedNode_head;
				unsortedNode_head = un_head_next;
			}
		}
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	//创建链表
	
	chain<int> element1(n);
	chain<int> element2(m);
	chain<int>element3(0);
	element1.insertSort();
	element2.insertSort();
	element3.combine(element1, element2);
	element3.insertSort();

	cout << element1.output_xor() << endl << element2.output_xor() << endl << element3.output_xor();
}
*/

//实验五
//稀疏矩阵

/*
template<class T>
struct matrixTerm  //创建节点，里面包含矩阵中一个元素的  行，列，数值
{
	int r;
	int c;
	T v;
};

template<class T>
class sparseMatrix
{
private:
	int rows;
	int cols;
	int listsize;

	matrixTerm<T>* element;

public:
	sparseMatrix() { listsize = 0; rows = 0; cols = 0; }
	void set(int m, int n, int t);
	void setTerm(int m, int n, int t);
	void getValue();
	int getListsize() { return listsize; }
	int getRow() { return rows; }
	int getCols() { return cols; }
	matrixTerm<T>& returnElement(int index) { return element[index]; }
	matrixTerm<T>*& getAddress() { return element; }
	int multiply(sparseMatrix<T>& q);
	int add(sparseMatrix<T>& q);
	void transpose();
};

template<class T>
void sparseMatrix<T>::set(int m, int n, int t) //m,n分别是行数和列数
{
	rows = m;
	cols = n;
	T value;
	listsize = 0;
	if (t != 0) delete[] element;
	element = new matrixTerm<T>[m * n + 1];

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> value;
			if (value != 0)
			{
				listsize++;
				element[listsize].r = i;
				element[listsize].c = j;
				element[listsize].v = value;
			}
		}
	}
}

template<class T>
void sparseMatrix<T>::setTerm(int m, int n, int t)
{
	rows = m;
	cols = n;
	listsize = t;
	element = new matrixTerm<T>[t + 1];

	for (int i = 1; i <= listsize; i++)
		cin >> element[i].r >> element[i].c >> element[i].v;
}

template<class T>
void sparseMatrix<T>::getValue()
{
	int step = 1;
	cout << rows << ' ' << cols << endl;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
		{
			if (step <= listsize && element[step].r == i && element[step].c == j)
			{
				cout << element[step].v << ' '; step++;
			}
			else cout << 0 << ' ';
		}
		cout << endl;
	}
}

template<class T>
int sparseMatrix<T>::multiply(sparseMatrix<T>& q)   //乘法
{//矩阵q的相关信息
	int qrows = q.getRow();
	int qcols = q.getCols();
	int qlistsize = q.getListsize();
	// 如果两个矩阵不匹配
	if (cols != qrows)
	{
		delete[] element;
		element = q.getAddress(); //将 element 指向 q 中的 element 
		listsize = qlistsize;
		rows = qrows;
		cols = qcols;
		return -1;
	}

	else
	{
		matrixTerm<T>* result = new matrixTerm<T>[rows * qcols + 1];//储存结果
		int number = 0;//目前没有结果
		//统计this------------------------------------------------------------------------------------
		int* irowsize = new int[rows + 1];//统计每一行有几个非0元素
		int* irowtop = new int[rows + 1];//统计每一行的非0元素在element数组中的索引

		for (int i = 1; i <= rows; i++)
			irowsize[i] = 0;//初始化为0

		for (int i = 1; i <= listsize; i++)
			irowsize[element[i].r]++;

		irowtop[1] = 1;
		for (int i = 2; i <= rows; i++)
			irowtop[i] = irowtop[i - 1] + irowsize[i - 1];
		//统计矩阵q--------------------------------------------------------------------------------------
		q.transpose();//转置矩阵q
		//转置后的矩阵q的相关信息
		qrows = q.getRow();
		qcols = q.getCols();

		int* qrowsize = new int[qrows + 1];//统计每一行有几个非0元素
		int* qrowtop = new int[qrows + 1];//统计每一行的非0元素在element数组中的索引

		for (int i = 1; i <= qrows; i++)
			qrowsize[i] = 0;//初始化为0

		for (int i = 1; i <= qlistsize; i++)
			qrowsize[q.returnElement(i).r]++;

		qrowtop[1] = 1;
		for (int i = 2; i <= qrows; i++)
			qrowtop[i] = qrowtop[i - 1] + qrowsize[i - 1];
		//乘法算法-----------------------------------------------------------------------------------------
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= qrows; j++)
			{
				int temp = 0;//储存结果矩阵某（i，j）的数值
				int flagi = irowtop[i];   int flagq = qrowtop[j];
				while (flagi < irowtop[i] + irowsize[i] && flagq < qrowtop[j] + qrowsize[j])
				{
					if (element[flagi].c == q.returnElement(flagq).c)
					{
						temp += element[flagi].v * q.returnElement(flagq).v;
						flagi++;
						flagq++;
					}

					else if (element[flagi].c < q.returnElement(flagq).c)
						flagi++;

					else flagq++;
				}

				if (temp != 0)
				{
					number++;
					result[number].r = i;
					result[number].c = j;
					result[number].v = temp;
				}
			}
		}
		delete[] element;
		element = result;
		listsize = number;
		cols = qrows;

		return 0;
	}
}

template<class T>
int sparseMatrix<T>::add(sparseMatrix<T>& q)
{
	int qr = q.getRow();
	int qc = q.getCols();
	int qlistsize = q.getListsize();

	if (rows != qr || cols != qc)
	{
		delete[] element;
		element = q.getAddress();
		listsize = qlistsize;
		rows = qr;
		cols = qc;
		return -1;
	}

	else
	{
		matrixTerm<T>* data = new matrixTerm<T>[listsize + qlistsize + 1];
		int i = 1, j = 1; int t = 0;
		while (i != (listsize + 1) && j != (qlistsize + 1))
		{
			int aindex = (element[i].r - 1) * cols + element[i].c - 1;
			int qindex = (q.returnElement(j).r - 1) * cols + q.returnElement(j).c - 1;

			if (aindex < qindex)
			{
				t++;
				data[t].r = element[i].r;
				data[t].c = element[i].c;
				data[t].v = element[i].v;
				i++;
			}

			else if (aindex == qindex)
			{
				if (element[i].v + q.returnElement(j).v != 0)
				{
					t++;
					data[t].r = element[i].r;
					data[t].c = element[i].c;
					data[t].v = element[i].v + q.returnElement(j).v;
				}

				i++;
				j++;
			}

			else if (aindex > qindex)
			{
				t++;
				data[t].r = q.returnElement(j).r;
				data[t].c = q.returnElement(j).c;
				data[t].v = q.returnElement(j).v;
				j++;
			}
		}

		for (; i <= listsize; i++)
		{
			t++;
			data[t].r = element[i].r;
			data[t].c = element[i].c;
			data[t].v = element[i].v;
		}

		for (; j <= qlistsize; j++)
		{
			t++;
			data[t].r = q.returnElement(j).r;
			data[t].c = q.returnElement(j).c;
			data[t].v = q.returnElement(j).v;
		}

		delete[] element;
		element = data;
		listsize = t;
	}
	return 0;

}

template<class T>
void sparseMatrix<T>::transpose()
{
	matrixTerm<T>* b = new matrixTerm<T>[listsize + 1];
	int* colsize = new int[cols + 1];//记录矩阵每一列的非0元素个数
	int* rowNext = new int[cols + 1];
	for (int i = 1; i <= cols; i++)
		colsize[i] = 0;

	for (int i = 1; i <= listsize; i++)
		colsize[element[i].c]++;

	rowNext[1] = 1;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colsize[i - 1];


	for (int i = 1; i <= listsize; i++)
	{
		int j = rowNext[element[i].c]++;
		b[j].r = element[i].c;
		b[j].c = element[i].r;
		b[j].v = element[i].v;
	}

	delete[] element;
	delete[] colsize;
	delete[] rowNext;
	element = b;
	int t = cols;
	cols = rows;
	rows = t;
}

int main()
{
	int w; //w 为执行操作数
	cin >> w;
	int step = 0;
	int size;
	int theRow, theCol;
	sparseMatrix<int> mode1;

	for (int i = 1; i <= w; i++)
	{
		int m;
		cin >> m;

		switch (m)
		{
		case 1:
		{cin >> theRow >> theCol;
		mode1.set(theRow, theCol, step);
		step++;
		break; }

		case 2:
		{cin >> theRow >> theCol;
		cin >> size;
		sparseMatrix<int> mode2;
		mode2.setTerm(theRow, theCol, size);
		int t = mode1.multiply(mode2);

		if (t == -1) { cout << t << endl; }
		break; }

		case 3:
		{cin >> theRow >> theCol;
		cin >> size;
		sparseMatrix<int> mode2;
		mode2.setTerm(theRow, theCol, size);
		int t = mode1.add(mode2);

		if (t == -1)cout << t << endl;
		break; }

		case 4:
		{mode1.getValue(); break; }

		case 5:
		{mode1.transpose(); break; }
		}
	}
}
*/

//实验六   栈
/*
//#include<iostream>
//#include<string>
//#include <iomanip>
//using namespace std;
//使用iosmanip的setprecision(n)函数将浮点数小数部分设置为n位

//栈-----------------------------------------------------------------------------
template<class T>
class arrayStack
{
public:
	//构造函数、析构函数
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[]stack; }
	//方法
	bool empty() const { return stackTop == -1; }//判断是否为空
	bool full() const { return stackTop == arrayLength - 1; }//判断栈是否已满
	int size() const { return stackTop + 1; }//返回元素个数
	T& top()//返回栈顶元素
	{
		if (stackTop == -1)//栈空
			throw illegalParameterValue("stack is empty");
		return stack[stackTop];
	}
	void pop()//删除栈顶元素
	{
		if (stackTop == -1)
			throw illegalParameterValue("stack is empty");
		stack[stackTop--].~T();//调用T的析构函数
	}
	void push(const T&);//将元素压入栈顶
protected:
	int stackTop;//栈顶索引
	int arrayLength;//栈容量
	T* stack;//元素数组
};
//构造函数-------------------------------------------------------------
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be >0");
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;//栈空
}
//入栈------------------------------------------------------------------
template<class T>
void arrayStack<T>::push(const T& element)
{
	if (stackTop == arrayLength - 1)//栈满
	{
		changeLength(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = element;
}
//计算-----------------------------------------------------------------
void calculate(arrayStack<double>& num, arrayStack<char>& sym)
{
	//符号栈顶为左括号，不继续向下运算
	if (sym.top() == '(')
		return;
	//移出第一个操作数
	double num1 = num.top();
	num.pop();
	//移出第二个操作数
	double num2 = num.top();
	num.pop();
	//根据符号栈的栈顶元素不同进行不同运算
	//注意减和除运算的数字顺序
	switch (sym.top())
	{
	case '+':
		num.push(num1 + num2);
		break;
	case '-':
		num.push(num2 - num1);
		break;
	case '*':
		num.push(num1 * num2);
		break;
	case '/':
		num.push(num2 / num1);
		break;
	default:
		break;
	}
	sym.pop();//弹出已运算完的符号
}
//对一串字符的处理--------------------------------
void process(string str, int str_len)
{
	bool minus = false;//负号标识
	arrayStack<double> num(str_len);//数字栈
	arrayStack<char> symbol(str_len);//运算符栈
	//遍历字符串
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] == ' ')//跳过空格
			continue;
		if (str[i] >= '0' && str[i] <= '9')//数字
		{
			int temp = str[i] - '0';
			while (str[i + 1] >= '0' && str[i + 1] <= '9')//下一个也是数字，说明这是个多位数
			{
				temp = 10 * temp + (str[i + 1] - '0');
				i++;
			}
			if (minus)//若为负
			{
				temp = -temp;
				minus = false;
			}
			num.push(temp);//入栈
		}
		else//不是数字
		{
			if ((i == 0 || str[i - 1] == '(') && str[i] == '-')//负号（排除减号干扰）
			{
				minus = true;
				continue;
			}
			switch (str[i])
			{
				//加减优先级相同
			case'+':
			case'-':
				if (symbol.empty() || symbol.top() == '(')
					symbol.push(str[i]);
				else
				{
					calculate(num, symbol);
					//括号嵌套
					if (!symbol.empty() && symbol.top() != '(')
						calculate(num, symbol);
					symbol.push(str[i]);
				}
				break;
				//乘除优先级相同
			case'*':
			case'/':
				if (symbol.empty() || symbol.top() == '(')
					symbol.push(str[i]);
				else if (symbol.top() == '+' || symbol.top() == '-')
					symbol.push(str[i]);
				else if (symbol.top() == '*' || symbol.top() == '/')
				{
					calculate(num, symbol);
					symbol.push(str[i]);
				}
				break;
			case'('://左括号直接入栈
				symbol.push(str[i]);
				break;
			case')'://遇到右括号运算至左括号
				while (symbol.top() != '(')
					calculate(num, symbol);
				symbol.pop();//左括号弹出
				break;
			default:
				break;
			}
		}
	}
	//运算最终结果
	while (!symbol.empty())
		calculate(num, symbol);
	//修改精度
	cout << setprecision(2) << fixed << num.top() << endl;
}
//主函数--------------------------------------------------------
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string str;
		int length;
		cin >> str;
		length = str.length();
		process(str, length);
	}
	return 0;
}
*/

//实验七   队列
//队列的数组定义
/*
template<class T>
class arrayQueue
{
public:
	//构造函数析构函数
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[]queue; }
	//方法
	bool empty() const { return queueFront == queueBack; }//判空
	bool full() const { return queueFront == (queueBack + 1) % arrayLength; }//判满
	int size() const { return (queueBack - queueFront + arrayLength) % arrayLength; }//返回元素个数
	T& theFront()//返回队首元素
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		return queue[(queueFront + 1) % arrayLength];
	}
	T& theBack()//返回队尾元素
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		return queue[queueBack];
	}
	void pop()//弹出队首元素
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		queueFront = (queueFront + 1) % arrayLength;
		queue[queueFront].~T();
	}
	void adjustLength();//队列满时数组长度加倍
	void push(const T& theElement);//压入队列
protected:
	int queueFront;//指向队首元素的前一个位置
	int queueBack;//队尾元素位置
	int arrayLength;//数组大小
	T* queue;//元素数组
};
//构造函数---------------------------------------------------------
template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("array length must be >0");
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	queueFront = 0;
	queueBack = 0;
}
//队列数组长度加倍---------------------------------------------------------------
template<class T>
void arrayQueue<T>::adjustLength()
{
	if (!full())//数组不满不加倍
		return;
	T* newQueue = new T[arrayLength * 2];
	int start = (queueFront + 1) % arrayLength;//队首元素位置
	if (start <= 1)//没有形成环
		//复制
		copy(queue + start, queue + start + arrayLength - 1, newQueue);
	else//形成环
	{
		copy(queue + start, queue + start + arrayLength - 1, newQueue);
		copy(queue, queue + queueBack + 1, newQueue + arrayLength - start);
	}
	//重置
	queueFront = 2 * arrayLength - 1;
	queueBack = arrayLength - 2;
	arrayLength *= 2;
	delete[]queue;
	queue = newQueue;
}
//压入队列----------------------------------------------
template<class T>
void arrayQueue<T>::push(const T& theElement)
{
	adjustLength();
	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
}
//操作-------------------------------------------------
int operate(arrayQueue<int>& card)
{
	int numOfCard = card.size();
	while (numOfCard >= 2)
	{
		card.pop();//扔掉第一张
		numOfCard--;
		card.push(card.theFront());//将新的第一张放入最后
		card.pop();
	}
	
	return card.theFront();
}

int main()
{
	int n;
	cin >> n;
	arrayQueue<int> card(n);
	for (int i = 1; i <= n; i++)
		card.push(i);
	cout << operate(card);
}
*/

//实验八   散列表
//题目一
/*
//#include<iostream>
//using namespace std;
//节点---------------------------------------------------------------------
template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;
	chainNode(){}
	chainNode(const T& theElement) { this->element = theElement; }
	chainNode(const T& theElement, chainNode<T>* theNext)
	{
		this->element = theElement;
		this->next = theNext;
	}
};
//有序链表描述------------------------------------------------------
template<class T>
class sortedChain
{
public:
	//构造函数析构函数
	sortedChain(int initialDivisor = 10) { firstNode = NULL; dSize = 0; }
	~sortedChain();
	//方法
	bool empty() { return dSize == 0; }
	int size() { return dSize; }
	void insert(const T&);
	void search(const T&);
	void erase(const T&);
protected:
	int dSize;//元素个数
	chainNode<T>* firstNode;//首指针
};
//析构函数----------------------------------------------
template<class T>
sortedChain<T>::~sortedChain()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
//插入--------------------------------------------------------------------------
template<class T>
void sortedChain<T>::insert(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;//指向要插入位置
	chainNode<T>* lastNode = NULL;//指向要插入位置的前一个元素
	while (currentNode != NULL && currentNode->element < theKey)
	{//找位置
		lastNode = currentNode;//寻找合适的位置(最后一个小于key)
		currentNode = currentNode->next;//此时要么=key要么>key
	}
	if (currentNode != NULL && currentNode->element == theKey)
	{
		//找到了相同的元素
		cout << "Exist" << endl;
		return;
	}
	//没找到
	chainNode<T>* newNode = new chainNode<T>(theKey, currentNode);
	if (lastNode == NULL)//插在表头
		firstNode = newNode;
	else//插在其他位置
		lastNode->next = newNode;
	dSize++;
	return;
}
//查找------------------------------------------------------------------------
template<class T>
void sortedChain<T>::search(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element != theKey)
		currentNode = currentNode->next;
	if (currentNode != NULL && currentNode->element == theKey)
		//找到了
		cout << size() << endl;
	else
		cout << "Not Found" << endl;
}
//删除-----------------------------------------------------------------------
template<class T>
void sortedChain<T>::erase(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;//指向要删除的元素
	chainNode<T>* lastNode = NULL;//指向前一个元素
	while (currentNode != NULL && currentNode->element < theKey)
	{
		//找位置
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode != NULL && currentNode->element == theKey)
	{
		//找到了
		if (lastNode == NULL)//删表头
			firstNode = currentNode->next;
		else
			lastNode->next = currentNode->next;
		dSize--;
		cout << dSize << endl;
	}
	else//没找到
		cout << "Delete Failed" << endl;
}
//散列表的数组定义------------------------------------------------------
template<class T>
class hashTable
{
public:
	//构造函数、析构函数
	hashTable(int initialDivisor = 11)
	{
		divisor = initialDivisor;
		dSize = 0;
		table = new sortedChain<T>[divisor];
	}
	~hashTable() { delete[]table; }
	//方法
	bool empty() { return dSize == 0; }
	int size() { return dSize; }
	void find(const T& theKey) const
	{
		table[theKey % divisor].search(theKey);
	}
	void insert(const T& theKey)
	{
		int homeBucket = theKey % divisor;//起始桶
		int homeSize = table[homeBucket].size();//起始桶的元素数量
		table[homeBucket].insert(theKey);//插入
		if (table[homeBucket].size() == homeSize)//成功插入
			dSize++;
	}
	void del(const T& theKey)
	{
		table[theKey % divisor].erase(theKey);
	}
protected:
	int divisor;//容量
	int dSize;//元素个数
	sortedChain<T>* table;//表
};
//主函数----------------------------------------------
int main()
{
	int D, m, opt, x;
	cin >> D >> m;
	hashTable<int> hashing(D);
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		switch (opt)
		{
		case(0):
			cin >> x;
			hashing.insert(x);
			break;
		case(1):
			cin >> x;
			hashing.find(x);
			break;
		case(2):
			cin >> x;
			hashing.del(x);
			break;
		default:
			break;
		}
	}
	return 0;
}
*/

//题目二
/*
//#include<iostream>
//using namespace std;
//自定义的异常类
//class illegalParameterValue
//{
//public:
	//illegalParameterValue(string s = "value is illegal") :message(s) {};
	//void output() { cout << message; }
//private:
	//string message;
//};
//散列的数组定义----------------------------------------
template<class T>
class hashTable
{
public:
	//构造函数、析构函数
	hashTable(int theDivisor = 11);
	~hashTable() { delete[] table; }
	//方法
	bool empty() const { return dSize == 0; }//判空
	int size() const { return dSize; }//返回元素个数
	void find(const T&) const;//查询
	void insert(const T&);//计算出f (k)，把元素放在f (k)位置
	void del(T&);//删除
protected:
	int search(const T&) const;//计算出f (k)，然后看表中f (k)处是否有元素(返回索引)
	T* table;//存放指针的散列表
	int dSize;//表中的元素个数
	int divisor;//表容量
};
//构造函数-----------------------------------------
template<class T>
hashTable<T>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	table = new T[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = -1;
}
//查找是否含有theKey的元素在表中--------------------------
template<class T>
void hashTable<T>::find(const T& theKey) const
{
	int homeBucket = theKey % divisor;//理论上要装填的桶的位置
	int currentBucket = homeBucket;//此时正在哪一个桶
	do
	{
		if (table[currentBucket] == theKey)
		{
			cout << currentBucket << endl;
			return;
		}
		currentBucket = (currentBucket + 1) % divisor;//指向下一个桶
	} while (currentBucket != homeBucket);
	//又回到最初的homeBucket
	cout << -1 << endl;
	return;
}
//插入（K,E），若已经存在----------------------------
template<class T>
void hashTable<T>::insert(const T& theKey)
{
	int index = search(theKey);
	if (table[index] == -1)//没找到，并且表没满
	{
		table[index] = theKey;
		dSize++;
		cout << index << endl;
	}
	else
		if (table[index] == theKey)//找到了,改相应的值
			cout << "Existed" << endl;
		else//表满了
			throw illegalParameterValue("table full");
}
//遍历整个表，若找到该元素或空置单元，则返回位置下标------------------------
template<class T>
int hashTable<T>::search(const T& theKey) const
{
	int homeBucket = theKey % divisor;//理论上要装填的桶的位置
	int currentBucket = homeBucket;//此时正在哪一个桶
	do
	{
		if (table[currentBucket] == -1 || table[currentBucket] == theKey)
			return currentBucket;
		currentBucket = (currentBucket + 1) % divisor;//指向下一个桶
	} while (currentBucket != homeBucket);
	//又回到最初的homeBucket
	return currentBucket;//此时表全满
}
//删除---------------------------------------------------------------------
template<class T>
void hashTable<T>::del(T& theKey)
{
	int delBucket = search(theKey);
	if (table[delBucket] == -50000 || table[delBucket] != theKey)//没找到
	{
		cout << "Not Found" << endl;
		return;
	}
	//找到了
	int currentBucket = delBucket;
	int correctBucket;//正确的桶
	int sum = 0;//移动桶的个数
	table[delBucket] = -50000;//标记为空
	do
	{
		currentBucket = (currentBucket + 1) % divisor;//操作下一个桶
		if (table[currentBucket] == -50000)//当前为空，不操作
			break;
		correctBucket = table[currentBucket] % divisor;
		if ((correctBucket <= delBucket && currentBucket > delBucket) || (currentBucket < correctBucket && correctBucket <= delBucket) || (delBucket < currentBucket && currentBucket < correctBucket))
		{
			table[delBucket] = table[currentBucket];
			table[currentBucket] = -50000;
			delBucket = currentBucket;
			sum++;
		}

	} while (table[(currentBucket + 1) % divisor] != -50000);
	cout << sum << endl;
	return;
}

int main()
{
	int D, m, opt, x;
	cin >> D >> m;
	hashTable<int> hashing(D);
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		switch (opt)
		{
		case(0):
			cin >> x;
			hashing.insert(x);
			break;
		case(1):
			cin >> x;
			hashing.find(x);
			break;
		case(2):
			cin >> x;
			hashing.del(x);
			break;
		default:
			break;
		}
	}
	return 0;
}
*/

//实验九   二叉树
//题目一
/*
#include<iostream>
using namespace std;

//异常类--------------------------------------------------
class queueEmpty
{
public:
	queueEmpty() : message("The queue is empty") {}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};
//节点---------------------------------------------------------------
template<class T>
struct chainNode
{
	chainNode<T>* next;
	T element;
	chainNode() {};
	chainNode(const T& theElement, chainNode<T>* theNext)
	{
		this->next = theNext;
		this->element = theElement;
	}
};
//队列的链式描述--------------------------------------------------
template<class T>
class linkedQueue
{
public:
	//构造函数析构函数
	linkedQueue() { theFront = 0; theBack = 0; queueSize = 0; }
	~linkedQueue();
	//方法
	bool empty() const { return queueSize == 0; }//判空
	int size() const { return queueSize; }//返回队列中元素的个数
	T& front()//返回头元素的引用
	{
		if (queueSize == 0)
			throw queueEmpty();
		return theFront->element;
	}
	T& back()//返回尾元素的引用
	{
		if (queueSize == 0)
			throw queueEmpty();
		return theBack->element;
	}
	chainNode<T>*& getFront() { return theFront; }//返回队首元素全部信息
	void pop();//弹出首元素
	void push(const T& theElement);//把元素theElement压入队列
private:
	chainNode<T>* theFront;//首元素
	chainNode<T>* theBack;//尾元素
	int queueSize;//元素个数
};
//一个简单的析构函数--------------
template<class T>
linkedQueue<T>::~linkedQueue()
{
	while (theFront != NULL)
		pop();
}
//从队列中弹出元素------------------------------
template<class T>
void linkedQueue<T> ::pop()
{
	if (theFront == NULL)
		throw queueEmpty();
	chainNode<T>* nextNode = theFront->next;
	delete theFront;
	theFront = nextNode;
	queueSize--;
}
//压入队列------------------------------------------------
template<class T>
void linkedQueue<T> ::push(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);

	if (queueSize == 0)
		theFront = newNode;
	else
		theBack->next = newNode;

	theBack = newNode;
	queueSize++;
}
//二叉树节点-------------------------------------------------------
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
	//三个构造函数
	binaryTreeNode() { leftChild = NULL; rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeft, binaryTreeNode<T>* theRight)
	{
		element = theElement;
		leftChild = theLeft;
		rightChild = theRight;
	}
};
//遍历删除二叉树----------------------------
template<class T>
void erase(binaryTreeNode<T>*& theRoot)
{
	if (theRoot != NULL)
	{
		erase(theRoot->leftChild);
		erase(theRoot->rightChild);
		delete theRoot;
		theRoot = NULL;
	}
}
//二叉树----------------------------------------------------------------------
template<class T>
class binaryTree
{
public:
	//构造函数析构函数
	binaryTree();
	~binaryTree() { erase(root); }
	//方法
	void create();//创建树
	int heightOf(binaryTreeNode<T>* t);//以 t 为根节点的树的高度
	int count(binaryTreeNode<T>* t);//以 t 为根节点的树的节点个数
	binaryTreeNode<T>*& theRoot() { return root; }//根节点的指针
	binaryTreeNode<T>*& elementOf(int i) { return num[i]; }//第i个节点的指针
	//四种遍历方式
	void preOrder(binaryTreeNode<T>* t);//前序
	void midOrder(binaryTreeNode<T>* t);//中序
	void postOrder(binaryTreeNode<T>* t);//后序
	void levelOrder(binaryTreeNode<T>* t);//层次
	//输出
	void outputHeight()//顺序输出树高度
	{
		for (int i = 1; i <= treeSize; i++)
		cout << heightOf(num[i]) << " ";
	}
	void outputCounts()//顺序输出节点个数
	{
		for (int i = 1; i <= treeSize; i++)
			cout << count(num[i]) << " ";
	}
private:
	binaryTreeNode<T>* root;//根节点指针
	int treeSize;//二叉树中元素的个数
	binaryTreeNode<T>** num;//用来建立初始化数组
};
//构造函数-------------------------------------------------
template<class T>
binaryTree<T>::binaryTree()
{
	int n;
	cin >> n;
	treeSize = n;
	num = new binaryTreeNode<T>*[n + 1];//0号位不用
	//给每个指针初始化
	for (int i = 1; i <= treeSize; i++)
		num[i] = new binaryTreeNode<T>(-1);
	//按题目要求赋值
	for (int i = 1; i <= treeSize; i++)
		num[i]->element = i;
	root = num[1];//把number[1]的值给root，直接对number操作就是改变二叉树结构
}
//建树----------------------------------
template<class T>
void binaryTree<T>::create()
{
	int a, b;//两个孩子的节点编号
	for (int i = 1; i <= treeSize; i++)
	{
		cin >> a >> b;//编号为i的节点的左右孩子为a，b
		if (a != -1)
			num[i]->leftChild = num[a];//如果a不是-1，则将他作为第i个节点的左孩子
		if (b != -1)
			num[i]->rightChild = num[b];//如果b不是-1，则将他作为第i个节点的又孩子
	}
}
//前序遍历-----------------------------------------------------
template<class T>
void binaryTree<T>::preOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		cout << t->element << " ";
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}
//中序遍历---------------------------------------------------
template<class T>
void binaryTree<T>::midOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		midOrder(t->leftChild);
		cout << t->element << " ";
		midOrder(t->rightChild);
	}
}
//后序遍历------------------------------------------------------
template<class T>
void binaryTree<T>::postOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		cout << t->element << " ";
	}
}
//层次遍历--------------------------------------------------------
template<class T>
void binaryTree<T>::levelOrder(binaryTreeNode<T>* t)
{
	linkedQueue<binaryTreeNode<T>*>q;
	while (t != NULL)
	{
		cout << t->element << " ";
		if (t->leftChild) q.push(t->leftChild);
		if (t->rightChild) q.push(t->rightChild);
		try { t = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}
//计算树高----------------------------------------------
template<class T>
int binaryTree<T>::heightOf(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return 0;
	int hl = heightOf(t->leftChild);//左子树的高度
	int hr = heightOf(t->rightChild);//右子树的高度
	if (hl >= hr)
		return ++hl;
	else
		return ++hr;
}
//计算节点个数---------------------------------------
template<class T>
int binaryTree<T>::count(binaryTreeNode<T>* t)
{
	int sum = 0;
	if (t != NULL)
		sum = count(t->leftChild) + count(t->rightChild) + 1;
	return sum;
}
//以下主函数用于测试-------------------
int main()
{
	binaryTree<int> tree_1;
	tree_1.create();
	tree_1.levelOrder(tree_1.theRoot());
	cout << endl;
	tree_1.outputCounts();
	cout << endl;
	tree_1.outputHeight();
}
*/

//题目二
/*
#include<iostream>
using namespace std;

//二叉树节点-------------------------------------------------------
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
	//三个构造函数
	binaryTreeNode() { leftChild = NULL; rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeft, binaryTreeNode<T>* theRight)
	{
		element = theElement;
		leftChild = theLeft;
		rightChild = theRight;
	}
};
//遍历删除二叉树----------------------------
template<class T>
void erase(binaryTreeNode<T>*& theRoot)
{
	if (theRoot != NULL)
	{
		erase(theRoot->leftChild);
		erase(theRoot->rightChild);
		delete theRoot;
		theRoot = NULL;
	}
}
//二叉树----------------------------------------------------------------------
template<class T>
class binaryTree
{
public:
	//构造函数析构函数
	binaryTree();
	~binaryTree() { erase(root); }
	//方法
	void postOrder(binaryTreeNode<T>* t);//后序
	void operate();//还原
	binaryTreeNode<T>*& theRoot() { return root; }//根节点的指针
	binaryTreeNode<T>*& elementOf(int i) { return num[i]; }//第i个节点的指针
	int index_inArr(T theElement);//返回第i个节点在中序数组中的索引
private:
	binaryTreeNode<T>* root;//根节点指针
	int treeSize;//二叉树中元素的个数
	binaryTreeNode<T>** num;//用来建立初始化数组
	T* preArr;//前序数组
	T* inArr;//后序数组
};
//构造函数-------------------------------------------------
template<class T>
binaryTree<T>::binaryTree()
{
	int n;
	cin >> n;
	treeSize = n;
	num = new binaryTreeNode<T>*[n + 1];//0号位不用
	preArr = new T[n + 1];
	inArr = new T[n + 1];
	//给每个指针初始化
	for (int i = 1; i <= treeSize; i++)
		num[i] = new binaryTreeNode<T>(i);
	//输入前序、中序数组
	for (int i = 1; i <= treeSize; i++)
		cin >> preArr[i];
	for (int i = 1; i <= treeSize; i++)
		cin >> inArr[i];
	root = num[preArr[1]];//根节点
}
//后序遍历------------------------------------------------------
template<class T>
void binaryTree<T>::postOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		cout << t->element << " ";
	}
}
//返回在中序数组中的索引-----------------------------
template<class T>
int binaryTree<T>::index_inArr(T theElement)
{
	for (int i = 1; i <= treeSize; i++)
		if (inArr[i] == theElement)
			return i;
	return 0;//没找到
}
//操作两种遍历生成树--------------------------------
template<class T>
void binaryTree<T>::operate()
{
	T current;//要插入的节点的值
	int index_c;//在中序遍历中的索引
	binaryTreeNode<T>* node;
	int index_n;
	for (int i = 2; i <= treeSize; i++)
	{
		current = preArr[i];//从前序数组中第二个开始依次取数
		index_c = index_inArr(current);
		node = root;//从根节点开始比较
		index_n = index_inArr(node->element);
		while ((index_c < index_n && node->leftChild != NULL) || (index_c > index_n && node->rightChild != NULL))
		{
			if (index_c < index_n)
			{
				node = node->leftChild;
				index_n = index_inArr(node->element);
			}
			else
			{
				node = node->rightChild;
				index_n = index_inArr(node->element);
			}
		}
		if (index_c < index_n)
			node->leftChild = num[current];
		else
			node->rightChild = num[current];
	}
}
//以下主函数用于测试-------------------
int main()
{
	binaryTree<int> tree_1;
	tree_1.operate();
	tree_1.postOrder(tree_1.theRoot());
}
*/

//实验十
//题目一
/*
#include<iostream>
#include<iterator>
using namespace std;

//数组长度加倍-----------------------------------------------
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp);
	//参数分别是首指针，末指针，目标位置指针
	delete[]arr;
	arr = temp;
}
//小根堆的数组描述------------------------------------------------------
template<class T>
class minHeap
{
public:
	//构造函数&析构函数
	minHeap(int initialCapacity = 10);
	~minHeap() { delete[]heap; }
	//方法
	void create(T*, int);//创建小根堆
	void clear() { heap = NULL; arrayLength = heapSize = 0; }//清空堆
	bool empty() { return heapSize == 0; }//判空
	int size() { return heapSize; }//返回元素个数
	const T& top()//返回堆顶元素
	{
		if (heapSize == 0)//堆空
			exit(1);
		return heap[1];//0号位不用
	}
	void pop();//从堆顶弹出元素
	void push(const T&);//压入堆
private:
	T* heap;//堆数组
	int arrayLength;//堆容量
	int heapSize;//元素个数
};
//构造函数------------------------------------
template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	if (initialCapacity < 1)
		exit(1);
	arrayLength = initialCapacity + 1;//0不用
	heap = new T[arrayLength];
	heapSize = 0;
}
//按题目要求创建小根堆----------------------------
template<class T>
void minHeap<T>::create(T* theHeap, int theSize)
{
	delete[]heap;
	heap = theHeap;
	heapSize = theSize;
	//堆化
	for (int root = heapSize / 2; root >= 1; root--)//从最后一个有孩子的结点开始
	{//root表示正在处理的结点
		T rootElement = heap[root];//保存父节点的值
		//为rootElement寻找合适的位置
		int child = 2 * root;//锁定左孩子
		while (child <= heapSize)
		{
			//child<heapSize保证child+1存在
			//比较左右孩子，让heap[child]锁定在兄弟中的较小者
			if (child < heapSize && heap[child] > heap[child + 1])
				child++;
			//判断是否可以将rootElement放在heap[child/2]
			if (rootElement <= heap[child])
				break;//可以
			//不可以
			heap[child / 2] = heap[child];//把孩子上移
			child *= 2;//指针下移一层，去操作子树
		}
		//如果不交换，则child/2就是root
		//如果交换，child/2是child(因为child*2/2=child)
		heap[child / 2] = rootElement;
	}
}
//从堆顶删除元素------------------------------------
template<class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
		exit(1);
	heap[1].~T();
	//保存最后一个元素值
	//heapSize--表示删除了最后一个
	T lastElement = heap[heapSize--];
	//从根开始为最后一个元素寻找合适的位置
	int current = 1, child = 2;
	while (child <= heapSize)
	{
		if (child<heapSize && heap[child]>heap[child + 1])
			child++;//锁定孩子的较小者
		if (lastElement <= heap[child])
			break;//可以把lastElemeny放在current的位置
		//不可以
		heap[current] = heap[child];
		current = child;//去操作子树
		child *= 2;
	}
	heap[current] = lastElement;
}
//将元素加入堆-----------------------------------
template<class T>
void minHeap<T>::push(const T& theElement)
{
	//堆满，加倍
	if (heapSize == arrayLength - 1)
	{
		changeLength(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	//寻找位置
	int current = ++heapSize;//从叶节点开始上移
	//当父节点的值大于theElement时将父节点下移，目标位置上移
	while (current != 1 && heap[current / 2] > theElement)
	{
		heap[current] = heap[current / 2];
		current /= 2;
	}
	heap[current] = theElement;
}
//升序输出----------------------------
template<class T>
void treefirst(T* theHeap, int n)
{
	minHeap<T> tre(1);
	tre.create(theHeap, n);
	for (int i = n; i > 1; i--) {
		int x = tre.top();
		tre.pop();
		theHeap[i] = x;
	}
	tre.clear();
}
//以下主函数做测试用
int main()
{
	int n, x, m, d, num, new_size;
	int* z;
	cin >> n;
	minHeap<int> heap(5000);
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		heap.push(x);
	}
	cout << heap.top() << endl;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> d;
		switch (d)
		{
		case 1:
			cin >> num;
			heap.push(num);
			cout << heap.top() << endl;
			break;
		case 2:
			heap.pop();
			cout << heap.top() << endl;
			break;
		case 3:
			cin >> new_size;
			z = new int[new_size + 1];
			for (int k = 1; k < new_size + 1; k++)
				cin >> z[k];
			treefirst(z, new_size);
			for (int j = new_size; j >= 1; j--)
				cout << z[j] << ' ';
			break;
		default:
			break;
		}
	}
}
*/

//题目二
/*
#include<iostream>
#include<string>
using namespace std;

//队列节点-------------------
template<class T>
struct chainNode
{
	T data;
	chainNode<T>* next;

	chainNode() {}
	chainNode(const T& theElement) { this->data = theElement; }
	chainNode(const T& theElement, chainNode<T>* next)
	{
		this->data = theElement;
		this->next = next;
	}
};
//队列的链表定义---------------------------------------------------------------------
template<class T>
class linkedQueue
{
public:
	//构造函数析构函数
	linkedQueue(int initialCapacity = 10) { queueFront = NULL; ququeSize = 0; }
	~linkedQueue();
	//方法
	bool empty() const { return ququeSize == 0; }//判空
	int size() const { return ququeSize; }//返回个数
	T& theFront()
	{
		if (ququeSize == 0)
			exit(1);
		return queueFront->data;
	}
	T& theBack()
	{
		if (ququeSize == 0)
			exit(1);
		return queueBack->data;
	}
	void pop();
	void push(const T& theElement);
private:
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
	int ququeSize;//元素个数
};
//析构函数-------------------------------------------------
template<class T>
linkedQueue<T>::~linkedQueue()
{
	while (queueFront != NULL)
	{
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}
//弹出队首元素--------------------------------------------
template<class T>
void linkedQueue<T>::pop()
{
	if (queueFront == NULL)
		exit(1);
	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	ququeSize--;
}
//压入新元素------------------------------------------------------------------
template<class T>
void linkedQueue<T>::push(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	if (ququeSize == 0)//队列空
		queueFront = newNode;
	else//队列非空
		queueBack->next = newNode;
	//调整
	queueBack = newNode;
	ququeSize++;
}
//霍夫曼节点---------------
struct huffmanNode
{
	int element;
	huffmanNode* leftChild;
	huffmanNode* rightChild;
	int weight;
	huffmanNode(){}
};
//带霍夫曼节点的最小堆---------------------------------------
class minHeap {
public:
	minHeap()
	{
		heapSize = 0;
		heap = new huffmanNode * [26]; //只有26个字母
	}
	~minHeap() { delete[]heap; }
	void initialize(huffmanNode** arr, int n);
	void insert(huffmanNode* num);
	void pop();
	huffmanNode* top() { return heap[1]; }
private:
	int heapSize;//元素个数
	huffmanNode** heap;//存放huffman节点指针的数组
};
//将数组堆化-------------------------------------------------
void minHeap::initialize(huffmanNode** arr, int n)
{
	heapSize = n;
	for (int i = 0; i < n; i++)
		heap[i + 1] = arr[i];//0号位不用
	//堆化
	for (int root = heapSize / 2; root >= 1; root--)
	{
		huffmanNode* rootElement = heap[root];
		int child = 2 * root;
		while (child <= heapSize)
		{
			if (child<heapSize && heap[child]->element>heap[child + 1]->element)
				child++;
			if (rootElement->element <= heap[child]->element)
				break;
			else
			{
				heap[child / 2] = heap[child];
				child *= 2;
			}
		}
		heap[child/2] = rootElement;
	}
}
//插入--------------------------------------------------
void minHeap::insert(huffmanNode* num)
{
	int current = heapSize + 1;//元素要插入的位置
	heapSize++;
	while (current > 1 && heap[current / 2]->element > num->element)
	{
		heap[current] = heap[current / 2];
		current /= 2;
	}
	heap[current] = num;
}
//删除堆顶元素---------------------------------
void minHeap::pop()
{
	huffmanNode* lastNode = heap[heapSize];
	int root = 1, child = 2;
	heapSize--;
	while (child <= heapSize)
	{
		if (child<heapSize && heap[child]->element>heap[child + 1]->element)
			child++;
		if (lastNode->element <= heap[child]->element)
			break;
		heap[root] = heap[child];
		//重构子节点
		root = child;
		child *= 2;
	}
	heap[root] = lastNode;
}
//霍夫曼树的链式描述----------------------------------
class huffmanTree
{
public:
	huffmanNode* root;
	huffmanTree(){}
	~huffmanTree();
	void makeTree(int* arr, int n);//编码中有n种字母
	void length();//输出霍夫曼编码的长度
private:
	int size;//元素个数
};
//析构函数-------------------------------------------------
huffmanTree::~huffmanTree()
{
	linkedQueue<huffmanNode*> nodes;
	nodes.push(root);
	for (int i = 0; i < size; i++)
	{
		//每次删除根节点，将孩子放入队列
		huffmanNode* currentNode = nodes.theFront();
		nodes.pop();
		if (currentNode->leftChild != NULL)
			nodes.push(currentNode->leftChild);
		if (currentNode->rightChild != NULL)
			nodes.push(currentNode->rightChild);
		delete currentNode;
	}
}
//创建霍夫曼树-----------------------------------------------------
void huffmanTree::makeTree(int* arr, int n)
{
	//将数组转化为霍夫曼节点形式
	huffmanNode** nodeArr = new huffmanNode*[n];
	for (int i = 0; i < n; i++)
	{
		nodeArr[i] = new huffmanNode();
		nodeArr[i]->element = arr[i];
		nodeArr[i]->leftChild = nodeArr[i]->rightChild = NULL;
	}
	//将节点堆化为最小堆
	minHeap huffmanHeap;
	huffmanHeap.initialize(nodeArr, n);
	//构造霍夫曼树
	huffmanNode* lc, * rc, * tr;//leftChild,rightChild,theRoot
	for (int i = 1; i < n; i++)
	{//每一次取两个加一个，故第n-1次会取走第n-1个和第n个
		lc = huffmanHeap.top();
		huffmanHeap.pop();
		rc = huffmanHeap.top();
		huffmanHeap.pop();
		tr = new huffmanNode();
		tr->leftChild = lc;
		tr->rightChild = rc;
		tr->element = lc->element + rc->element;
		//此时取出的两个已经是外部节点，不作为树节点，故清空
		lc = NULL;
		rc = NULL;
		huffmanHeap.insert(tr);
	}
	size = n;
	root = huffmanHeap.top();
	huffmanHeap.pop();//???
}
//输出编码后的长度----------------------------------
void huffmanTree::length()
{
	int result = 0;
	linkedQueue<huffmanNode*>queue;
	queue.push(root);
	root->weight = 0;
	huffmanNode* currentNode;
	while (!queue.empty())
	{
		currentNode = queue.theFront();
		queue.pop();
		if (currentNode->leftChild != NULL)
		{
			queue.push(currentNode->leftChild);
			currentNode->leftChild->weight = currentNode->weight + 1;
		}
		if (currentNode->rightChild != NULL)
		{
			queue.push(currentNode->rightChild);
			currentNode->rightChild->weight = currentNode->weight + 1;
		}
		if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
			result = result + currentNode->weight * currentNode->element;
	}
	cout << result;
}
//以下主函数用于测试
int main()
{
	string str;
	int index = 0, n = 0;
	cin >> str;
	//统计各字母出现的次数
	int* frequency = new int[26];
	for (int i = 0; i < 26; i++)
		frequency[i] = 0;
	for (int j = 0; j < str.size(); j++)
	{
		frequency[(int)str[j] - 97]++;
		if (frequency[(int)str[j] - 97] == 1)
			n++;//第一次出现才计数
	}
	//出现过的字母数组
	int* alphabet = new int[n];
	for (int k = 0; k < 26; k++)
		if (frequency[k] != 0)
			alphabet[index++] = frequency[k];
	huffmanTree tree;
	tree.makeTree(alphabet, n);
	tree.length();
	return 0;
}
*/

//实验十一
/*
#include<iostream>
using namespace std;

//带索引的树节点--------------------
template<class T>
struct treeNode
{
	T element;
	int leftSize;
	treeNode<T>* leftChild;
	treeNode<T>* rightChild;
	treeNode(){}
	treeNode(const T& theElement)
	{
		element = theElement;
		leftSize = 0;
		leftChild = rightChild = NULL;
	}
};
//递归删除------------------------------
template<class T>
void erase(treeNode<T>*& theRoot)
{
	if (theRoot != NULL)
	{
		erase(theRoot->leftChild);
		erase(theRoot->rightChild);
		delete theRoot;
		theRoot = NULL;
	}
}
//二叉搜索树的链表描述-------------------------------------
template<class T>
class binarySearchTree
{
public:
	//构造函数、析构函数
	binarySearchTree(int initialCapacity = 10) { root = NULL; treeSize = 0; }
	~binarySearchTree() { erase(root); }
	//方法
	bool empty() { return treeSize == 0; }
	int size() { return treeSize; }
	void insert(const T& theElement);
	void find(const T& theElement);
	void del(const T& theElement);
	void find_rank(int rank);
	//void erase_rank(int rank);
	int rankOf(int rank);
private:
	treeNode<T>* root;
	int treeSize;
	//辅助方法
	bool search(const T& theElement);

};
//插入---------------------------------------------------------
template<class T>
void binarySearchTree<T>::insert(const T& theElement)
{
	if (search(theElement))
	{
		cout << 0 << endl;
		return;
	}
	int output_xor = 0;
	//寻找插入位置
	treeNode<T>* p = root;
	treeNode<T>* pp = NULL;//p节点的父节点
	while (p != NULL)
	{
		pp = p;//p会移动到子节点，故保存pp为p的父节点
		if (theElement < p->element)
		{
			//插左边，p的排位会增加
			output_xor ^= p->element;
			p->leftSize++;
			p = p->leftChild;
		}
		else if (theElement > p->element)
		{
			//插右边，p的排位不会增加
			output_xor ^= p->element;
			p = p->rightChild;
		}
	}
	//为element建立节点，与pp相连
	treeNode<T>* newNode = new treeNode<T>(theElement);
	if (root == NULL)
		root = newNode;
	else
		if (theElement < pp->element)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	treeSize++;
	cout << output_xor << endl;
}
//查询------------------------------------------------------
template<class T>
void binarySearchTree<T>::find(const T& theElement)
{
	int output_xor = theElement;
	treeNode<T>* searchNode = root;
	while (searchNode != NULL)
		if (theElement < searchNode->element)
		{
			output_xor ^= searchNode->element;
			searchNode = searchNode->leftChild;
		}
		else
			if (theElement > searchNode->element)
			{
				output_xor ^= searchNode->element;
				searchNode = searchNode->rightChild;
			}
			else
			{
				cout << output_xor << endl;
				return;
			}
	//没找到
	cout << 0 <<endl;
}
//判断元素是否在树中--------------------------------------
template<class T>
bool binarySearchTree<T>::search(const T& theElement)
{
	treeNode<T>* searchNode = root;
	while (searchNode != NULL)
		if (theElement < searchNode->element)
			searchNode = searchNode->leftChild;
		else
			if (theElement > searchNode->element)
				searchNode = searchNode->rightChild;
			else
				break;
	//判断
	if (searchNode != NULL)
		return true;
	else
		return false;
}
//删除--------------------------------------------------------
template<class T>
void binarySearchTree<T>::del(const T& theElement)
{
	if (!search(theElement))//没找到
	{
		cout << 0 << endl;
		return;
	}
	int output_xor = theElement;
	//寻找删除的位置
	treeNode<T>* p = root;
	treeNode<T>* pp = NULL;

	while (p->element != theElement)
	{
		pp = p;
		output_xor ^= p->element;
		if (theElement < p->element)
		{
			p->leftSize--;
			p = p->leftChild;
		}
		else
			p = p->rightChild;
	}

	//两个孩子都存在，重新组织树结构，使其变成只有一个孩子
	if (p->leftChild != NULL && p->rightChild != NULL)
	{
		//寻找右子树中最小的元素
		treeNode<T>* s = p->rightChild;
		treeNode<T>* ps = p;
		while (s->leftChild != NULL)
		{
			//疯狂左移
			ps = s;
			s->leftSize--;//妈的这屌细节没注意到一直runtime error
			s = s->leftChild;
		}
		//把要删除元素的右子树中最小的元素放在要删除的位置
		//同时重构该子树
		treeNode<T>* q = new treeNode<T>(s->element);
		q->leftSize = p->leftSize;//是否可以是ps？不能，否则指针会越界
		q->leftChild = p->leftChild;
		q->rightChild = p->rightChild;
		if (pp == NULL)
			root = q;
		else
			if (p == pp->leftChild)
				pp->leftChild = q;
			else
				pp->rightChild = q;
		//pp和p下移
		if (ps == p)
			pp = q;
		else
			pp = ps;
		delete p;
		p = s;
	}
	//此时p最多有一个孩子
	treeNode<T>* c;//把孩子指针存放在c
	if (p->leftChild != NULL)
		c = p->leftChild;
	else
		c = p->rightChild;
	//删除p
	if (p == root)
		root = c;
	else
		if (p == pp->leftChild)
			pp->leftChild = c;
		else
			pp->rightChild = c;
	treeSize--;
	delete p;
	//cout << pp->leftSize << "rank" << endl;
	cout << output_xor << endl;
}
//查询索引为rank的元素----------------------------------------
template<class T>
void binarySearchTree<T>::find_rank(int rank)
{
	if (rank <1 || rank > treeSize || root == NULL)//必然找不到
	{
		cout << 0 << endl;
		return;
	}
	int index = rank - 1;
	//一定能找到
	int output_xor = 0;
	treeNode<T>* searchNode = root;
	while (searchNode->leftSize != index && searchNode != NULL)
	{

		//左拐
		if (index < searchNode->leftSize)
		{
			output_xor ^= searchNode->element;
			searchNode = searchNode->leftChild;
		}
		else//右拐
		{
			output_xor ^= searchNode->element;
			index = index - (searchNode->leftSize + 1);
			searchNode = searchNode->rightChild;
		}
	}
	if (searchNode == NULL)
	{
		cout << 0 << endl;
		return;
	}
	output_xor ^= searchNode->element;
	cout << output_xor << endl;
}
//返回排名为rank的元素的值（排名比索引多1）--------------------
template<class T>
int binarySearchTree<T>::rankOf(int rank)
{
	if (rank <1 || rank > treeSize || root == NULL)//必然找不到
		return -1;
	int index = rank - 1;
	//一定能找到
	treeNode<T>* searchNode = root;
	while (searchNode->leftSize != index)
	{
		//左拐
		if (index < searchNode->leftSize)
			searchNode = searchNode->leftChild;
		else//右拐
		{
			index = index - (searchNode->leftSize + 1);
			searchNode = searchNode->rightChild;
		}
	}
	return searchNode->element;
}
//一下主函数用于测试
int main()
{
	binarySearchTree<int> tree1;
	int m, a, b,element;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a;
		switch (a)
		{
		case 0:
			cin >> b;
			tree1.insert(b);
			break;
		case 1:
			cin >> b;
			tree1.find(b);
			break;
		case 2:
			cin >> b;
			tree1.del(b);
			break;
		case 3:
			cin >> b;
			tree1.find_rank(b);
			break;
		case 4:
			cin >> b;
			element = tree1.rankOf(b);
			tree1.del(element);
		default:
			break;
		}
	}
	return 0;
}
*/

//实验十二
/*
#include<iostream>
#include<queue>
using namespace std;

//顶点节点--------------------------------------------------------
template<class T>
struct vertexNode
{
	T element;
	vertexNode<T>* nextNode;
	vertexNode() {}
	vertexNode(const T& theElement)
	{
		element = theElement;
		nextNode = NULL;
	}
	vertexNode(const T& theElement, vertexNode<T>* theNext)
	{
		element = theElement;
		nextNode = theNext;
	}
};
//无向图的邻接链表描述---------------------------------------------
template<class T>
class linkedGraph
{
public:
	//构造函数、析构函数
	linkedGraph(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			exit(1);
		grapgSize = initialCapacity;
		edgeSize = 0;
		num = new vertexNode<T>*[grapgSize + 1];
		for (int i = 1; i <= grapgSize; i++)
		{//0号位不用
			vertexNode<T>* newVertex = new vertexNode<T>(-1);
			num[i] = newVertex;
		}
		reach = new T[grapgSize + 1];//判断是否到达
		for (int i = 0; i <= grapgSize; i++)
			reach[i] = 0;
		order = new T[grapgSize + 1];//输出bfs序列，0号位为序列长度
		for (int i = 0; i <= grapgSize; i++)
			order[i] = 0;
		index = 1;
	}
	~linkedGraph()
	{
		delete[]num;
		delete[]reach;
		delete[]order;
	}
	//方法
	void combine(const T& vertex1, const T& vertex2);//在顶点1和2之间插入一条边
	void erase(const T& vertex1, const T& vertex2);//删除顶点1和2之间的边
	void bfs(const T& source);//广度优先搜索
	void bfs(T source, T reach[], int label);
	void dfs(const T& source);//深度优先搜索
	void rDfs(const T& source);//递归
	void labelComponent();//连通分量/构件
	void shortestPath(const T& start, const T& end);//最短路径
	//其他方法
	bool empty() const { return grapgSize == 0; }//判空
	int vertex() const { return grapgSize; }//返回顶点个数
	int edge() const { return edgeSize; }//返回边数
private:
	int grapgSize;//顶点数
	int edgeSize;//边数
	vertexNode<T>** num;//指向指针的数组，按顶点编号升序
	//深度优先搜索的数组
	T* reach;
	T* order;
	int index;
};
//插入1到2的一条边----------------------------------------------------------------
template<class T>
void linkedGraph<T>::combine(const T& vertex1, const T& vertex2)
{
	if ((vertex1 == vertex2) || vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* newVertex = new vertexNode<T>(vertex2);
	vertexNode<T>* p = num[vertex1];//搜索节点
	vertexNode<T>* pp = NULL;//搜索节点的父节点
	//为新节点寻找合适的位置
	while (p != NULL && p->element < vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	//插入
	if (p == NULL)//在尾部插入
		pp->nextNode = newVertex;
	else//在中间插入
	{
		pp->nextNode = newVertex;
		newVertex->nextNode = p;
	}
	edgeSize++;
}
//删除1到2的一条边--------------------------------------------------
template<class T>
void linkedGraph<T>::erase(const T& vertex1, const T& vertex2)
{
	if (vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* p = num[vertex1];//搜索节点
	vertexNode<T>* pp = NULL;//p的父节点
	//寻找删除位置
	while (p != NULL && p->element != vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	if (p == NULL)//没找到
		exit(1);
	else//找到了
		pp->nextNode = p->nextNode;
	edgeSize--;
}
//广度优先搜索----------------------------------
template<class T>
void linkedGraph<T>::bfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	queue<T> que;
	T* reach = new T[grapgSize + 1];//判断是否到达
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	T* order = new T[grapgSize + 1];//输出bfs序列，0号位为序列长度
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	reach[source] = 1;//标记为1
	int indexOfOrder = 1;//数组order的索引
	que.push(source);
	while (!que.empty())
	{
		//从队列中删除一个标记过的节点
		int vertex = que.front();
		order[indexOfOrder++] = vertex;
		order[0]++;
		que.pop();
		//标记所有邻接于vertex且没到达的节点
		vertexNode<T>* currentVertex = num[vertex];
		currentVertex = currentVertex->nextNode;
		while (currentVertex != NULL)
		{
			if (reach[currentVertex->element] == 0)
			{
				que.push(currentVertex->element);
				reach[currentVertex->element] = 1;
			}
			currentVertex = currentVertex->nextNode;
		}
	}
	cout << order[0] << endl;
	for (int i = 1; i <= grapgSize; i++)
	{
		if (order[i] == 0)
			break;
		else
			cout << order[i] << ' ';
	}
	cout << endl;
}
template<class T>
void linkedGraph<T>::bfs(T source, T reach[], int label)
{
	queue<T>que;
	reach[source] = label;
	que.push(source);
	while (!que.empty())
	{
		int w = que.front();
		que.pop();
		vertexNode<T>* u = num[w];
		u = u->nextNode;
		for (; u != NULL; u = u->nextNode)
			if (reach[u->element] == 0)
			{
				que.push(u->element);
				reach[u->element] = label;
			}
	}
}
//深度优先搜索----------------------------------------
template<class T>
void linkedGraph<T>::dfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	//重置
	delete[]reach;
	delete[]order;
	reach = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	order = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	index = 1;
	//递归进行深度优先搜索
	rDfs(source);
	cout << order[0] << endl;
	for (int i = 1; i <= grapgSize; i++)
	{
		if (order[i] == 0)
			break;
		else
			cout << order[i] << ' ';
	}
	cout << endl;
}
//递归-----------------------------------------------
template<class T>
void linkedGraph<T>::rDfs(const T& source)
{
	reach[source] = 1;
	order[0]++;
	order[index++] = source;
	vertexNode<T>* currentVertex = num[source];
	currentVertex = currentVertex->nextNode;
	for (; currentVertex != NULL; currentVertex = currentVertex->nextNode)
	{
		int w = currentVertex->element;
		if (reach[w] == 0)
			rDfs(w);
	}
}
//输出连通分量/构件-------------------------
template<class T>
void linkedGraph<T>::labelComponent()
{
	T* c = new T[grapgSize + 1];
	for (int i = 1; i <= grapgSize; i++)
		c[i] = 0;
	int label = 0;
	int* arr = new int[grapgSize + 1];
	int index = 1;
	for (int i = 1; i <= grapgSize; i++)
		if (c[i] == 0)
		{
			arr[index++] = i;
			label++;
			bfs(i, c, label);
		}
	cout << label << endl;
	for (int i = 1; i <= label; i++)
		cout << arr[i] << ' ';
	//下面这个输出的时间复杂度太大
	//for (int j = 1; j <= label; j++)
		//for (int i = 1; i <= grapgSize; i++)
			//if (c[i] == j)
			//{
				//cout << i << ' ';
				//break;
			//}
	cout << endl;
}
//最短路径--------------------------------------------------------------
template<class T>
void linkedGraph<T>::shortestPath(const T& start, const T& end)
{
	T* dist = new T[grapgSize + 1];//起始点到i节点最短路径的长度
	for (int i = 1; i <= grapgSize; i++)
		dist[i] = -1;//全部都未遍历过
	dist[start] = 0;//起始点到起始点的距离为0
	queue<T>que;
	que.push(start);
	while (!que.empty())
	{
		T top = que.front();
		que.pop();
		vertexNode<T>* theVertex = num[top];
		theVertex = theVertex->nextNode;//指向邻接于top的第一个节点
		for (; theVertex != NULL; theVertex = theVertex->nextNode)
			if (dist[theVertex->element] == -1)
			{
				que.push(theVertex->element);
				dist[theVertex->element] = dist[top] + 1;
			}
	}
	cout << dist[end] << endl;
}
//以下主函数做测试用
int main()
{
	int n, m, s, t, option, u, v;
	cin >> n >> m >> s >> t;
	linkedGraph<int>graph(n);
	for (int i = 0; i < m; i++)
	{
		cin >> option >> u >> v;
		if (option == 0)
		{
			graph.combine(u, v);
			graph.combine(v, u);
		}
		else if (option == 1)
		{
			graph.erase(u, v);
			graph.erase(v, u);
		}
	}
	graph.labelComponent();
	graph.dfs(s);
	graph.bfs(t);
	graph.shortestPath(s, t);
	return 0;
}
*/

//数据结构实验完结撒花