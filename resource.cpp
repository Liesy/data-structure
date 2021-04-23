#include<iostream>
#include<cmath>
#include<string>
#include <iomanip>
#include"illegalParameterValue.h"
#include"change array length.h"
using namespace std;

//ʵ��һ

//��Ŀһ ȫ���е�����
/*
template<class T>
void change(T &a, T &b) //�����ǵ�ַ�Ľ���
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int value_num = 0; //���ڱ�����Ǽ��ϼ�ֵ����ĵڼ���Ԫ��
template<class T>
void perm(T arr[], T value[], int begin, int end)  // ����ÿ�����еļ�ֵ
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
	
	int permSum = 1;//������ϵĸ���
	for (int i = 2; i <= n; i++)
		permSum *= i;

	int* arr = new int[n];
	int* value = new int[permSum];
	for (int i = 0; i < n; i++) // ��ʼ��
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

//��Ŀ�� �Ӽ��ļ�ֵ
/*
int sign_value_num = 0; //���ڱ�ʶ�����Ӽ���ֵ����ĵڼ���Ԫ��

void calculate(int arr_judge[], int arr_num[], int all_value[], int end)
{
	int sign_subset_num=0; // ���ڱ�ʶ�����Ӽ��еĵڼ���Ԫ��
	int subset_value=0; //���ڼ�¼���Ӽ��ļ�ֵ

	for (int i = 0; i < end; i++) // �����Ӽ���ֵ
	{
		if (arr_judge[i])
		{
			sign_subset_num++; //Ԫ�ظ�����1��ʼ
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
	int subsetNum = (int)pow(2, n); //�Ӽ�����Ϊ2^n��

	int* arr_num = new int[n];
	int* arr_judge = new int[n]; 
	for (int i = 0; i < n; i++)//��ʼ��
	{
		cin >> arr_num[i];
		arr_judge[i] = 0;
	}
	
	int* all_value = new int[subsetNum]; //��Ÿ����Ӽ��ļ�ֵ

	subset(arr_judge, arr_num, all_value, 0, n);

	unsigned long xor_sum = all_value[0] ^ all_value[1]; //������
	for (int i = 2; i < subsetNum; i++)
		xor_sum ^= all_value[i];

	cout << xor_sum;
}
*/


//ʵ���
//����������������ѡ������ð�����򣬲�������
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

template<class T>  //��������
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
	//���
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			if (rank[j] == i)
			{
				cout << arr[j] << ' ';
				break;
			}
	delete[]rank;
}

template<class T> //ѡ������
void Sort<T>::selectSort(T arr[], int len)
{
	T temp;
	bool sorted = false; //�����ж�ǰ���Ԫ���Ƿ��Ѿ���˳���ź���
	for (int size = len; (size > 1) && !sorted; size--) //sizeΪ���鳤��
	{
		int index_max = 0; //������ֵ���±�
		sorted = true;
		for (int j = 1; j < size ; j++)
		{
			if (arr[index_max] <= arr[j])
				index_max = j;
			else
				sorted = false; //
		}
		//�����ֵ������Ե����
		temp = arr[size-1];
		arr[size-1] = arr[index_max];
		arr[index_max] = temp;
	}
	//���
	for (int i = 0; i < len - 1; i++)
		cout << arr[i] << ' ';
	cout << arr[len - 1] << endl;
}

template<class T> //ð������
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
	//���
	for (int i = 0; i < len - 1; i++)
		cout << arr[i] << ' ';
	cout << arr[len];
}

template<class T> //��������
void Sort<T>::insertSort(T arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		T temp = arr[i]; //�ӵڶ���Ԫ�ؿ�ʼȡ��
		int j;
		// �Ӻ���ǰ��[0:i]��������бȽϣ��ҵ�arr[i]λ�ã�����arr[i]�����������һ��λ��
		for (j = i - 1; j >= 0 && arr[j] > temp; j--)
			arr[j + 1] = arr[j]; //��ʱarr[i]�Ѿ������浫��ֵ����temp��
		arr[j + 1] = temp; 
		//j-- ֮�� j ��λ����һ����arr[i]С�������ʰ�temp��arr[j+1]
	}
	//���
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


//ʵ����
//���Ա����������
/*
struct student //ѧ����
{
	string name; // ����
	string phone; //�绰
	int class_num; //�༶
	int dorm; //����
};

template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //�����ֱ�����ָ�룬ĩָ�룬Ŀ��λ��ָ��
	delete[]arr;
	arr = temp;
}

class linearlist
{
	public:
		//���캯��
		linearlist(int n = 10);
		//��������
		~linearlist() { delete []stu; };
		//���ֲ���
		void insert(string& name, string& phone, int& class_num, int& dorm);
		void erase(string &name);
		void edit_phone(string &name,string &new_info);
		void edit_class_dorm(string& name, int decision, int &new_info);
		bool serch(string &name);
		//��������ŵ����ֵ
		int calculate_xor(int &class_num); 
	private:
		struct student* stu;
		int len; //��������
		int size; //Ԫ�ظ���
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
	int index = 0;//name��Ӧ��Ԫ�ص�����
	while (stu[index].name != name && index < size)
		index++;

	copy(stu + index + 1, stu + size, stu + index);
	stu[--size].~student(); //������������
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

//��main�������޷�ֱ����ѭ���ж��з���size����дΪһ���ڲ�����
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

//ʵ����
//���Ա����ʽ����
/*
//��Ŀһ
template<class T>
struct chainNode  //����ڵ�
{
	//���ݳ�Ա
	T element;
	chainNode<T>* next;

	//���캯��
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
	//���캯��
	chain(int n= 5);
	//��������
	~chain();

	//����
	void insert(int theIndex,const T& theElement);
	void del(const T& theElement);
	int theIndexOf(int theElement);
	void reverse();
	unsigned long output_xor();
	void combine(chain<T>& a, chain<T>& b);

	//��������
	void create(chainNode<T>* theFirstNode) { firstNode = theFirstNode; }
	int getListSize() { return size; } // ���Ԫ�س���
	void setSize(int theSize) { size = theSize; } // �޸�Ԫ�س���
	chainNode<T>* getFirstNode() { return firstNode; }//��ȡ���������ָ��
	void output();
	void insertSort();
protected:
	chainNode<T>* firstNode; //ָ����Ԫ�صĵ�ַ
	int size;
};

template<class T>
chain<T>::chain(int n) // ���캯��
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
chain<T>::~chain() //��������
{
	//����һ���ڵ��Ϊ��һ���ڵ㣬����һ���ڵ�ɾ��
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next; //element��ֵ��ʱ�Ѿ�����ν��
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
		for (int i = 0; i < theIndex - 1; i++)//�ҵ�����ָ���Ԫ�ص�ǰ��
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
		//�ҵ�Ҫɾ��Ԫ�ص�ǰ��
		while (searchNode->next->element != theElement)
			searchNode = searchNode->next;
		searchNode->next = searchNode->next->next;
	}
	size--;
}

template<class T>
int chain<T>::theIndexOf(int theElement)
{
	int last_index = -1; //Ĭ��û�ҵ�
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
	dummy->next = firstNode;//���ڹ̶�����
	chainNode<T>* headNode = firstNode;//��һ��Ԫ�صĽڵ�
	chainNode<T>* reverseNode = headNode->next;//����תԪ�صĽڵ�
	while (reverseNode != NULL)
	{
		//���淴תԪ�ص���һ���ڵ��ֹ��ʧ
		headNode->next = reverseNode->next;
		//������תԪ�ط��ڵ�һ��Ԫ�ص�λ��
		reverseNode->next = dummy->next;
		dummy->next = reverseNode;
		//��ת��һ��Ԫ��
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
	//��������
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
//��Ŀ��
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
		chainNode<T>* searchNode;//Ѱ�����һ������С��Ԫ��
		while (unsortedNode_head != NULL)
		{
			un_head_next = unsortedNode_head->next;
			searchNode = firstNode;
			while (searchNode->next != NULL && searchNode->next->element <= unsortedNode_head->element)
				searchNode = searchNode->next;

			if (searchNode == firstNode && searchNode->element > unsortedNode_head->element)
			{
				unsortedNode_head->next = searchNode;
				this->create(unsortedNode_head);//����firstNode
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
	//��������
	
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

//ʵ����
//ϡ�����

/*
template<class T>
struct matrixTerm  //�����ڵ㣬�������������һ��Ԫ�ص�  �У��У���ֵ
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
void sparseMatrix<T>::set(int m, int n, int t) //m,n�ֱ�������������
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
int sparseMatrix<T>::multiply(sparseMatrix<T>& q)   //�˷�
{//����q�������Ϣ
	int qrows = q.getRow();
	int qcols = q.getCols();
	int qlistsize = q.getListsize();
	// �����������ƥ��
	if (cols != qrows)
	{
		delete[] element;
		element = q.getAddress(); //�� element ָ�� q �е� element 
		listsize = qlistsize;
		rows = qrows;
		cols = qcols;
		return -1;
	}

	else
	{
		matrixTerm<T>* result = new matrixTerm<T>[rows * qcols + 1];//������
		int number = 0;//Ŀǰû�н��
		//ͳ��this------------------------------------------------------------------------------------
		int* irowsize = new int[rows + 1];//ͳ��ÿһ���м�����0Ԫ��
		int* irowtop = new int[rows + 1];//ͳ��ÿһ�еķ�0Ԫ����element�����е�����

		for (int i = 1; i <= rows; i++)
			irowsize[i] = 0;//��ʼ��Ϊ0

		for (int i = 1; i <= listsize; i++)
			irowsize[element[i].r]++;

		irowtop[1] = 1;
		for (int i = 2; i <= rows; i++)
			irowtop[i] = irowtop[i - 1] + irowsize[i - 1];
		//ͳ�ƾ���q--------------------------------------------------------------------------------------
		q.transpose();//ת�þ���q
		//ת�ú�ľ���q�������Ϣ
		qrows = q.getRow();
		qcols = q.getCols();

		int* qrowsize = new int[qrows + 1];//ͳ��ÿһ���м�����0Ԫ��
		int* qrowtop = new int[qrows + 1];//ͳ��ÿһ�еķ�0Ԫ����element�����е�����

		for (int i = 1; i <= qrows; i++)
			qrowsize[i] = 0;//��ʼ��Ϊ0

		for (int i = 1; i <= qlistsize; i++)
			qrowsize[q.returnElement(i).r]++;

		qrowtop[1] = 1;
		for (int i = 2; i <= qrows; i++)
			qrowtop[i] = qrowtop[i - 1] + qrowsize[i - 1];
		//�˷��㷨-----------------------------------------------------------------------------------------
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= qrows; j++)
			{
				int temp = 0;//����������ĳ��i��j������ֵ
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
	int* colsize = new int[cols + 1];//��¼����ÿһ�еķ�0Ԫ�ظ���
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
	int w; //w Ϊִ�в�����
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

//ʵ����   ջ
/*
//#include<iostream>
//#include<string>
//#include <iomanip>
//using namespace std;
//ʹ��iosmanip��setprecision(n)������������С����������Ϊnλ

//ջ-----------------------------------------------------------------------------
template<class T>
class arrayStack
{
public:
	//���캯������������
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[]stack; }
	//����
	bool empty() const { return stackTop == -1; }//�ж��Ƿ�Ϊ��
	bool full() const { return stackTop == arrayLength - 1; }//�ж�ջ�Ƿ�����
	int size() const { return stackTop + 1; }//����Ԫ�ظ���
	T& top()//����ջ��Ԫ��
	{
		if (stackTop == -1)//ջ��
			throw illegalParameterValue("stack is empty");
		return stack[stackTop];
	}
	void pop()//ɾ��ջ��Ԫ��
	{
		if (stackTop == -1)
			throw illegalParameterValue("stack is empty");
		stack[stackTop--].~T();//����T����������
	}
	void push(const T&);//��Ԫ��ѹ��ջ��
protected:
	int stackTop;//ջ������
	int arrayLength;//ջ����
	T* stack;//Ԫ������
};
//���캯��-------------------------------------------------------------
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be >0");
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;//ջ��
}
//��ջ------------------------------------------------------------------
template<class T>
void arrayStack<T>::push(const T& element)
{
	if (stackTop == arrayLength - 1)//ջ��
	{
		changeLength(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = element;
}
//����-----------------------------------------------------------------
void calculate(arrayStack<double>& num, arrayStack<char>& sym)
{
	//����ջ��Ϊ�����ţ���������������
	if (sym.top() == '(')
		return;
	//�Ƴ���һ��������
	double num1 = num.top();
	num.pop();
	//�Ƴ��ڶ���������
	double num2 = num.top();
	num.pop();
	//���ݷ���ջ��ջ��Ԫ�ز�ͬ���в�ͬ����
	//ע����ͳ����������˳��
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
	sym.pop();//������������ķ���
}
//��һ���ַ��Ĵ���--------------------------------
void process(string str, int str_len)
{
	bool minus = false;//���ű�ʶ
	arrayStack<double> num(str_len);//����ջ
	arrayStack<char> symbol(str_len);//�����ջ
	//�����ַ���
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] == ' ')//�����ո�
			continue;
		if (str[i] >= '0' && str[i] <= '9')//����
		{
			int temp = str[i] - '0';
			while (str[i + 1] >= '0' && str[i + 1] <= '9')//��һ��Ҳ�����֣�˵�����Ǹ���λ��
			{
				temp = 10 * temp + (str[i + 1] - '0');
				i++;
			}
			if (minus)//��Ϊ��
			{
				temp = -temp;
				minus = false;
			}
			num.push(temp);//��ջ
		}
		else//��������
		{
			if ((i == 0 || str[i - 1] == '(') && str[i] == '-')//���ţ��ų����Ÿ��ţ�
			{
				minus = true;
				continue;
			}
			switch (str[i])
			{
				//�Ӽ����ȼ���ͬ
			case'+':
			case'-':
				if (symbol.empty() || symbol.top() == '(')
					symbol.push(str[i]);
				else
				{
					calculate(num, symbol);
					//����Ƕ��
					if (!symbol.empty() && symbol.top() != '(')
						calculate(num, symbol);
					symbol.push(str[i]);
				}
				break;
				//�˳����ȼ���ͬ
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
			case'('://������ֱ����ջ
				symbol.push(str[i]);
				break;
			case')'://����������������������
				while (symbol.top() != '(')
					calculate(num, symbol);
				symbol.pop();//�����ŵ���
				break;
			default:
				break;
			}
		}
	}
	//�������ս��
	while (!symbol.empty())
		calculate(num, symbol);
	//�޸ľ���
	cout << setprecision(2) << fixed << num.top() << endl;
}
//������--------------------------------------------------------
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

//ʵ����   ����
//���е����鶨��
/*
template<class T>
class arrayQueue
{
public:
	//���캯����������
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[]queue; }
	//����
	bool empty() const { return queueFront == queueBack; }//�п�
	bool full() const { return queueFront == (queueBack + 1) % arrayLength; }//����
	int size() const { return (queueBack - queueFront + arrayLength) % arrayLength; }//����Ԫ�ظ���
	T& theFront()//���ض���Ԫ��
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		return queue[(queueFront + 1) % arrayLength];
	}
	T& theBack()//���ض�βԪ��
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		return queue[queueBack];
	}
	void pop()//��������Ԫ��
	{
		if (queueFront == queueBack)
			throw illegalParameterValue("queue is empty");
		queueFront = (queueFront + 1) % arrayLength;
		queue[queueFront].~T();
	}
	void adjustLength();//������ʱ���鳤�ȼӱ�
	void push(const T& theElement);//ѹ�����
protected:
	int queueFront;//ָ�����Ԫ�ص�ǰһ��λ��
	int queueBack;//��βԪ��λ��
	int arrayLength;//�����С
	T* queue;//Ԫ������
};
//���캯��---------------------------------------------------------
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
//�������鳤�ȼӱ�---------------------------------------------------------------
template<class T>
void arrayQueue<T>::adjustLength()
{
	if (!full())//���鲻�����ӱ�
		return;
	T* newQueue = new T[arrayLength * 2];
	int start = (queueFront + 1) % arrayLength;//����Ԫ��λ��
	if (start <= 1)//û���γɻ�
		//����
		copy(queue + start, queue + start + arrayLength - 1, newQueue);
	else//�γɻ�
	{
		copy(queue + start, queue + start + arrayLength - 1, newQueue);
		copy(queue, queue + queueBack + 1, newQueue + arrayLength - start);
	}
	//����
	queueFront = 2 * arrayLength - 1;
	queueBack = arrayLength - 2;
	arrayLength *= 2;
	delete[]queue;
	queue = newQueue;
}
//ѹ�����----------------------------------------------
template<class T>
void arrayQueue<T>::push(const T& theElement)
{
	adjustLength();
	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
}
//����-------------------------------------------------
int operate(arrayQueue<int>& card)
{
	int numOfCard = card.size();
	while (numOfCard >= 2)
	{
		card.pop();//�ӵ���һ��
		numOfCard--;
		card.push(card.theFront());//���µĵ�һ�ŷ������
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

//ʵ���   ɢ�б�
//��Ŀһ
/*
//#include<iostream>
//using namespace std;
//�ڵ�---------------------------------------------------------------------
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
//������������------------------------------------------------------
template<class T>
class sortedChain
{
public:
	//���캯����������
	sortedChain(int initialDivisor = 10) { firstNode = NULL; dSize = 0; }
	~sortedChain();
	//����
	bool empty() { return dSize == 0; }
	int size() { return dSize; }
	void insert(const T&);
	void search(const T&);
	void erase(const T&);
protected:
	int dSize;//Ԫ�ظ���
	chainNode<T>* firstNode;//��ָ��
};
//��������----------------------------------------------
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
//����--------------------------------------------------------------------------
template<class T>
void sortedChain<T>::insert(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;//ָ��Ҫ����λ��
	chainNode<T>* lastNode = NULL;//ָ��Ҫ����λ�õ�ǰһ��Ԫ��
	while (currentNode != NULL && currentNode->element < theKey)
	{//��λ��
		lastNode = currentNode;//Ѱ�Һ��ʵ�λ��(���һ��С��key)
		currentNode = currentNode->next;//��ʱҪô=keyҪô>key
	}
	if (currentNode != NULL && currentNode->element == theKey)
	{
		//�ҵ�����ͬ��Ԫ��
		cout << "Exist" << endl;
		return;
	}
	//û�ҵ�
	chainNode<T>* newNode = new chainNode<T>(theKey, currentNode);
	if (lastNode == NULL)//���ڱ�ͷ
		firstNode = newNode;
	else//��������λ��
		lastNode->next = newNode;
	dSize++;
	return;
}
//����------------------------------------------------------------------------
template<class T>
void sortedChain<T>::search(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element != theKey)
		currentNode = currentNode->next;
	if (currentNode != NULL && currentNode->element == theKey)
		//�ҵ���
		cout << size() << endl;
	else
		cout << "Not Found" << endl;
}
//ɾ��-----------------------------------------------------------------------
template<class T>
void sortedChain<T>::erase(const T& theKey)
{
	chainNode<T>* currentNode = firstNode;//ָ��Ҫɾ����Ԫ��
	chainNode<T>* lastNode = NULL;//ָ��ǰһ��Ԫ��
	while (currentNode != NULL && currentNode->element < theKey)
	{
		//��λ��
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode != NULL && currentNode->element == theKey)
	{
		//�ҵ���
		if (lastNode == NULL)//ɾ��ͷ
			firstNode = currentNode->next;
		else
			lastNode->next = currentNode->next;
		dSize--;
		cout << dSize << endl;
	}
	else//û�ҵ�
		cout << "Delete Failed" << endl;
}
//ɢ�б�����鶨��------------------------------------------------------
template<class T>
class hashTable
{
public:
	//���캯������������
	hashTable(int initialDivisor = 11)
	{
		divisor = initialDivisor;
		dSize = 0;
		table = new sortedChain<T>[divisor];
	}
	~hashTable() { delete[]table; }
	//����
	bool empty() { return dSize == 0; }
	int size() { return dSize; }
	void find(const T& theKey) const
	{
		table[theKey % divisor].search(theKey);
	}
	void insert(const T& theKey)
	{
		int homeBucket = theKey % divisor;//��ʼͰ
		int homeSize = table[homeBucket].size();//��ʼͰ��Ԫ������
		table[homeBucket].insert(theKey);//����
		if (table[homeBucket].size() == homeSize)//�ɹ�����
			dSize++;
	}
	void del(const T& theKey)
	{
		table[theKey % divisor].erase(theKey);
	}
protected:
	int divisor;//����
	int dSize;//Ԫ�ظ���
	sortedChain<T>* table;//��
};
//������----------------------------------------------
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

//��Ŀ��
/*
//#include<iostream>
//using namespace std;
//�Զ�����쳣��
//class illegalParameterValue
//{
//public:
	//illegalParameterValue(string s = "value is illegal") :message(s) {};
	//void output() { cout << message; }
//private:
	//string message;
//};
//ɢ�е����鶨��----------------------------------------
template<class T>
class hashTable
{
public:
	//���캯������������
	hashTable(int theDivisor = 11);
	~hashTable() { delete[] table; }
	//����
	bool empty() const { return dSize == 0; }//�п�
	int size() const { return dSize; }//����Ԫ�ظ���
	void find(const T&) const;//��ѯ
	void insert(const T&);//�����f (k)����Ԫ�ط���f (k)λ��
	void del(T&);//ɾ��
protected:
	int search(const T&) const;//�����f (k)��Ȼ�󿴱���f (k)���Ƿ���Ԫ��(��������)
	T* table;//���ָ���ɢ�б�
	int dSize;//���е�Ԫ�ظ���
	int divisor;//������
};
//���캯��-----------------------------------------
template<class T>
hashTable<T>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	table = new T[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = -1;
}
//�����Ƿ���theKey��Ԫ���ڱ���--------------------------
template<class T>
void hashTable<T>::find(const T& theKey) const
{
	int homeBucket = theKey % divisor;//������Ҫװ���Ͱ��λ��
	int currentBucket = homeBucket;//��ʱ������һ��Ͱ
	do
	{
		if (table[currentBucket] == theKey)
		{
			cout << currentBucket << endl;
			return;
		}
		currentBucket = (currentBucket + 1) % divisor;//ָ����һ��Ͱ
	} while (currentBucket != homeBucket);
	//�ֻص������homeBucket
	cout << -1 << endl;
	return;
}
//���루K,E�������Ѿ�����----------------------------
template<class T>
void hashTable<T>::insert(const T& theKey)
{
	int index = search(theKey);
	if (table[index] == -1)//û�ҵ������ұ�û��
	{
		table[index] = theKey;
		dSize++;
		cout << index << endl;
	}
	else
		if (table[index] == theKey)//�ҵ���,����Ӧ��ֵ
			cout << "Existed" << endl;
		else//������
			throw illegalParameterValue("table full");
}
//�������������ҵ���Ԫ�ػ���õ�Ԫ���򷵻�λ���±�------------------------
template<class T>
int hashTable<T>::search(const T& theKey) const
{
	int homeBucket = theKey % divisor;//������Ҫװ���Ͱ��λ��
	int currentBucket = homeBucket;//��ʱ������һ��Ͱ
	do
	{
		if (table[currentBucket] == -1 || table[currentBucket] == theKey)
			return currentBucket;
		currentBucket = (currentBucket + 1) % divisor;//ָ����һ��Ͱ
	} while (currentBucket != homeBucket);
	//�ֻص������homeBucket
	return currentBucket;//��ʱ��ȫ��
}
//ɾ��---------------------------------------------------------------------
template<class T>
void hashTable<T>::del(T& theKey)
{
	int delBucket = search(theKey);
	if (table[delBucket] == -50000 || table[delBucket] != theKey)//û�ҵ�
	{
		cout << "Not Found" << endl;
		return;
	}
	//�ҵ���
	int currentBucket = delBucket;
	int correctBucket;//��ȷ��Ͱ
	int sum = 0;//�ƶ�Ͱ�ĸ���
	table[delBucket] = -50000;//���Ϊ��
	do
	{
		currentBucket = (currentBucket + 1) % divisor;//������һ��Ͱ
		if (table[currentBucket] == -50000)//��ǰΪ�գ�������
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

//ʵ���   ������
//��Ŀһ
/*
#include<iostream>
using namespace std;

//�쳣��--------------------------------------------------
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
//�ڵ�---------------------------------------------------------------
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
//���е���ʽ����--------------------------------------------------
template<class T>
class linkedQueue
{
public:
	//���캯����������
	linkedQueue() { theFront = 0; theBack = 0; queueSize = 0; }
	~linkedQueue();
	//����
	bool empty() const { return queueSize == 0; }//�п�
	int size() const { return queueSize; }//���ض�����Ԫ�صĸ���
	T& front()//����ͷԪ�ص�����
	{
		if (queueSize == 0)
			throw queueEmpty();
		return theFront->element;
	}
	T& back()//����βԪ�ص�����
	{
		if (queueSize == 0)
			throw queueEmpty();
		return theBack->element;
	}
	chainNode<T>*& getFront() { return theFront; }//���ض���Ԫ��ȫ����Ϣ
	void pop();//������Ԫ��
	void push(const T& theElement);//��Ԫ��theElementѹ�����
private:
	chainNode<T>* theFront;//��Ԫ��
	chainNode<T>* theBack;//βԪ��
	int queueSize;//Ԫ�ظ���
};
//һ���򵥵���������--------------
template<class T>
linkedQueue<T>::~linkedQueue()
{
	while (theFront != NULL)
		pop();
}
//�Ӷ����е���Ԫ��------------------------------
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
//ѹ�����------------------------------------------------
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
//�������ڵ�-------------------------------------------------------
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
	//�������캯��
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
//����ɾ��������----------------------------
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
//������----------------------------------------------------------------------
template<class T>
class binaryTree
{
public:
	//���캯����������
	binaryTree();
	~binaryTree() { erase(root); }
	//����
	void create();//������
	int heightOf(binaryTreeNode<T>* t);//�� t Ϊ���ڵ�����ĸ߶�
	int count(binaryTreeNode<T>* t);//�� t Ϊ���ڵ�����Ľڵ����
	binaryTreeNode<T>*& theRoot() { return root; }//���ڵ��ָ��
	binaryTreeNode<T>*& elementOf(int i) { return num[i]; }//��i���ڵ��ָ��
	//���ֱ�����ʽ
	void preOrder(binaryTreeNode<T>* t);//ǰ��
	void midOrder(binaryTreeNode<T>* t);//����
	void postOrder(binaryTreeNode<T>* t);//����
	void levelOrder(binaryTreeNode<T>* t);//���
	//���
	void outputHeight()//˳��������߶�
	{
		for (int i = 1; i <= treeSize; i++)
		cout << heightOf(num[i]) << " ";
	}
	void outputCounts()//˳������ڵ����
	{
		for (int i = 1; i <= treeSize; i++)
			cout << count(num[i]) << " ";
	}
private:
	binaryTreeNode<T>* root;//���ڵ�ָ��
	int treeSize;//��������Ԫ�صĸ���
	binaryTreeNode<T>** num;//����������ʼ������
};
//���캯��-------------------------------------------------
template<class T>
binaryTree<T>::binaryTree()
{
	int n;
	cin >> n;
	treeSize = n;
	num = new binaryTreeNode<T>*[n + 1];//0��λ����
	//��ÿ��ָ���ʼ��
	for (int i = 1; i <= treeSize; i++)
		num[i] = new binaryTreeNode<T>(-1);
	//����ĿҪ��ֵ
	for (int i = 1; i <= treeSize; i++)
		num[i]->element = i;
	root = num[1];//��number[1]��ֵ��root��ֱ�Ӷ�number�������Ǹı�������ṹ
}
//����----------------------------------
template<class T>
void binaryTree<T>::create()
{
	int a, b;//�������ӵĽڵ���
	for (int i = 1; i <= treeSize; i++)
	{
		cin >> a >> b;//���Ϊi�Ľڵ�����Һ���Ϊa��b
		if (a != -1)
			num[i]->leftChild = num[a];//���a����-1��������Ϊ��i���ڵ������
		if (b != -1)
			num[i]->rightChild = num[b];//���b����-1��������Ϊ��i���ڵ���ֺ���
	}
}
//ǰ�����-----------------------------------------------------
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
//�������---------------------------------------------------
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
//�������------------------------------------------------------
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
//��α���--------------------------------------------------------
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
//��������----------------------------------------------
template<class T>
int binaryTree<T>::heightOf(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return 0;
	int hl = heightOf(t->leftChild);//�������ĸ߶�
	int hr = heightOf(t->rightChild);//�������ĸ߶�
	if (hl >= hr)
		return ++hl;
	else
		return ++hr;
}
//����ڵ����---------------------------------------
template<class T>
int binaryTree<T>::count(binaryTreeNode<T>* t)
{
	int sum = 0;
	if (t != NULL)
		sum = count(t->leftChild) + count(t->rightChild) + 1;
	return sum;
}
//�������������ڲ���-------------------
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

//��Ŀ��
/*
#include<iostream>
using namespace std;

//�������ڵ�-------------------------------------------------------
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
	//�������캯��
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
//����ɾ��������----------------------------
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
//������----------------------------------------------------------------------
template<class T>
class binaryTree
{
public:
	//���캯����������
	binaryTree();
	~binaryTree() { erase(root); }
	//����
	void postOrder(binaryTreeNode<T>* t);//����
	void operate();//��ԭ
	binaryTreeNode<T>*& theRoot() { return root; }//���ڵ��ָ��
	binaryTreeNode<T>*& elementOf(int i) { return num[i]; }//��i���ڵ��ָ��
	int index_inArr(T theElement);//���ص�i���ڵ������������е�����
private:
	binaryTreeNode<T>* root;//���ڵ�ָ��
	int treeSize;//��������Ԫ�صĸ���
	binaryTreeNode<T>** num;//����������ʼ������
	T* preArr;//ǰ������
	T* inArr;//��������
};
//���캯��-------------------------------------------------
template<class T>
binaryTree<T>::binaryTree()
{
	int n;
	cin >> n;
	treeSize = n;
	num = new binaryTreeNode<T>*[n + 1];//0��λ����
	preArr = new T[n + 1];
	inArr = new T[n + 1];
	//��ÿ��ָ���ʼ��
	for (int i = 1; i <= treeSize; i++)
		num[i] = new binaryTreeNode<T>(i);
	//����ǰ����������
	for (int i = 1; i <= treeSize; i++)
		cin >> preArr[i];
	for (int i = 1; i <= treeSize; i++)
		cin >> inArr[i];
	root = num[preArr[1]];//���ڵ�
}
//�������------------------------------------------------------
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
//���������������е�����-----------------------------
template<class T>
int binaryTree<T>::index_inArr(T theElement)
{
	for (int i = 1; i <= treeSize; i++)
		if (inArr[i] == theElement)
			return i;
	return 0;//û�ҵ�
}
//�������ֱ���������--------------------------------
template<class T>
void binaryTree<T>::operate()
{
	T current;//Ҫ����Ľڵ��ֵ
	int index_c;//����������е�����
	binaryTreeNode<T>* node;
	int index_n;
	for (int i = 2; i <= treeSize; i++)
	{
		current = preArr[i];//��ǰ�������еڶ�����ʼ����ȡ��
		index_c = index_inArr(current);
		node = root;//�Ӹ��ڵ㿪ʼ�Ƚ�
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
//�������������ڲ���-------------------
int main()
{
	binaryTree<int> tree_1;
	tree_1.operate();
	tree_1.postOrder(tree_1.theRoot());
}
*/

//ʵ��ʮ
//��Ŀһ
/*
#include<iostream>
#include<iterator>
using namespace std;

//���鳤�ȼӱ�-----------------------------------------------
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp);
	//�����ֱ�����ָ�룬ĩָ�룬Ŀ��λ��ָ��
	delete[]arr;
	arr = temp;
}
//С���ѵ���������------------------------------------------------------
template<class T>
class minHeap
{
public:
	//���캯��&��������
	minHeap(int initialCapacity = 10);
	~minHeap() { delete[]heap; }
	//����
	void create(T*, int);//����С����
	void clear() { heap = NULL; arrayLength = heapSize = 0; }//��ն�
	bool empty() { return heapSize == 0; }//�п�
	int size() { return heapSize; }//����Ԫ�ظ���
	const T& top()//���ضѶ�Ԫ��
	{
		if (heapSize == 0)//�ѿ�
			exit(1);
		return heap[1];//0��λ����
	}
	void pop();//�ӶѶ�����Ԫ��
	void push(const T&);//ѹ���
private:
	T* heap;//������
	int arrayLength;//������
	int heapSize;//Ԫ�ظ���
};
//���캯��------------------------------------
template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	if (initialCapacity < 1)
		exit(1);
	arrayLength = initialCapacity + 1;//0����
	heap = new T[arrayLength];
	heapSize = 0;
}
//����ĿҪ�󴴽�С����----------------------------
template<class T>
void minHeap<T>::create(T* theHeap, int theSize)
{
	delete[]heap;
	heap = theHeap;
	heapSize = theSize;
	//�ѻ�
	for (int root = heapSize / 2; root >= 1; root--)//�����һ���к��ӵĽ�㿪ʼ
	{//root��ʾ���ڴ���Ľ��
		T rootElement = heap[root];//���游�ڵ��ֵ
		//ΪrootElementѰ�Һ��ʵ�λ��
		int child = 2 * root;//��������
		while (child <= heapSize)
		{
			//child<heapSize��֤child+1����
			//�Ƚ����Һ��ӣ���heap[child]�������ֵ��еĽ�С��
			if (child < heapSize && heap[child] > heap[child + 1])
				child++;
			//�ж��Ƿ���Խ�rootElement����heap[child/2]
			if (rootElement <= heap[child])
				break;//����
			//������
			heap[child / 2] = heap[child];//�Ѻ�������
			child *= 2;//ָ������һ�㣬ȥ��������
		}
		//�������������child/2����root
		//���������child/2��child(��Ϊchild*2/2=child)
		heap[child / 2] = rootElement;
	}
}
//�ӶѶ�ɾ��Ԫ��------------------------------------
template<class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
		exit(1);
	heap[1].~T();
	//�������һ��Ԫ��ֵ
	//heapSize--��ʾɾ�������һ��
	T lastElement = heap[heapSize--];
	//�Ӹ���ʼΪ���һ��Ԫ��Ѱ�Һ��ʵ�λ��
	int current = 1, child = 2;
	while (child <= heapSize)
	{
		if (child<heapSize && heap[child]>heap[child + 1])
			child++;//�������ӵĽ�С��
		if (lastElement <= heap[child])
			break;//���԰�lastElemeny����current��λ��
		//������
		heap[current] = heap[child];
		current = child;//ȥ��������
		child *= 2;
	}
	heap[current] = lastElement;
}
//��Ԫ�ؼ����-----------------------------------
template<class T>
void minHeap<T>::push(const T& theElement)
{
	//�������ӱ�
	if (heapSize == arrayLength - 1)
	{
		changeLength(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	//Ѱ��λ��
	int current = ++heapSize;//��Ҷ�ڵ㿪ʼ����
	//�����ڵ��ֵ����theElementʱ�����ڵ����ƣ�Ŀ��λ������
	while (current != 1 && heap[current / 2] > theElement)
	{
		heap[current] = heap[current / 2];
		current /= 2;
	}
	heap[current] = theElement;
}
//�������----------------------------
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
//������������������
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

//��Ŀ��
/*
#include<iostream>
#include<string>
using namespace std;

//���нڵ�-------------------
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
//���е�������---------------------------------------------------------------------
template<class T>
class linkedQueue
{
public:
	//���캯����������
	linkedQueue(int initialCapacity = 10) { queueFront = NULL; ququeSize = 0; }
	~linkedQueue();
	//����
	bool empty() const { return ququeSize == 0; }//�п�
	int size() const { return ququeSize; }//���ظ���
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
	int ququeSize;//Ԫ�ظ���
};
//��������-------------------------------------------------
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
//��������Ԫ��--------------------------------------------
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
//ѹ����Ԫ��------------------------------------------------------------------
template<class T>
void linkedQueue<T>::push(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	if (ququeSize == 0)//���п�
		queueFront = newNode;
	else//���зǿ�
		queueBack->next = newNode;
	//����
	queueBack = newNode;
	ququeSize++;
}
//�������ڵ�---------------
struct huffmanNode
{
	int element;
	huffmanNode* leftChild;
	huffmanNode* rightChild;
	int weight;
	huffmanNode(){}
};
//���������ڵ����С��---------------------------------------
class minHeap {
public:
	minHeap()
	{
		heapSize = 0;
		heap = new huffmanNode * [26]; //ֻ��26����ĸ
	}
	~minHeap() { delete[]heap; }
	void initialize(huffmanNode** arr, int n);
	void insert(huffmanNode* num);
	void pop();
	huffmanNode* top() { return heap[1]; }
private:
	int heapSize;//Ԫ�ظ���
	huffmanNode** heap;//���huffman�ڵ�ָ�������
};
//������ѻ�-------------------------------------------------
void minHeap::initialize(huffmanNode** arr, int n)
{
	heapSize = n;
	for (int i = 0; i < n; i++)
		heap[i + 1] = arr[i];//0��λ����
	//�ѻ�
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
//����--------------------------------------------------
void minHeap::insert(huffmanNode* num)
{
	int current = heapSize + 1;//Ԫ��Ҫ�����λ��
	heapSize++;
	while (current > 1 && heap[current / 2]->element > num->element)
	{
		heap[current] = heap[current / 2];
		current /= 2;
	}
	heap[current] = num;
}
//ɾ���Ѷ�Ԫ��---------------------------------
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
		//�ع��ӽڵ�
		root = child;
		child *= 2;
	}
	heap[root] = lastNode;
}
//������������ʽ����----------------------------------
class huffmanTree
{
public:
	huffmanNode* root;
	huffmanTree(){}
	~huffmanTree();
	void makeTree(int* arr, int n);//��������n����ĸ
	void length();//�������������ĳ���
private:
	int size;//Ԫ�ظ���
};
//��������-------------------------------------------------
huffmanTree::~huffmanTree()
{
	linkedQueue<huffmanNode*> nodes;
	nodes.push(root);
	for (int i = 0; i < size; i++)
	{
		//ÿ��ɾ�����ڵ㣬�����ӷ������
		huffmanNode* currentNode = nodes.theFront();
		nodes.pop();
		if (currentNode->leftChild != NULL)
			nodes.push(currentNode->leftChild);
		if (currentNode->rightChild != NULL)
			nodes.push(currentNode->rightChild);
		delete currentNode;
	}
}
//������������-----------------------------------------------------
void huffmanTree::makeTree(int* arr, int n)
{
	//������ת��Ϊ�������ڵ���ʽ
	huffmanNode** nodeArr = new huffmanNode*[n];
	for (int i = 0; i < n; i++)
	{
		nodeArr[i] = new huffmanNode();
		nodeArr[i]->element = arr[i];
		nodeArr[i]->leftChild = nodeArr[i]->rightChild = NULL;
	}
	//���ڵ�ѻ�Ϊ��С��
	minHeap huffmanHeap;
	huffmanHeap.initialize(nodeArr, n);
	//�����������
	huffmanNode* lc, * rc, * tr;//leftChild,rightChild,theRoot
	for (int i = 1; i < n; i++)
	{//ÿһ��ȡ������һ�����ʵ�n-1�λ�ȡ�ߵ�n-1���͵�n��
		lc = huffmanHeap.top();
		huffmanHeap.pop();
		rc = huffmanHeap.top();
		huffmanHeap.pop();
		tr = new huffmanNode();
		tr->leftChild = lc;
		tr->rightChild = rc;
		tr->element = lc->element + rc->element;
		//��ʱȡ���������Ѿ����ⲿ�ڵ㣬����Ϊ���ڵ㣬�����
		lc = NULL;
		rc = NULL;
		huffmanHeap.insert(tr);
	}
	size = n;
	root = huffmanHeap.top();
	huffmanHeap.pop();//???
}
//��������ĳ���----------------------------------
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
//�������������ڲ���
int main()
{
	string str;
	int index = 0, n = 0;
	cin >> str;
	//ͳ�Ƹ���ĸ���ֵĴ���
	int* frequency = new int[26];
	for (int i = 0; i < 26; i++)
		frequency[i] = 0;
	for (int j = 0; j < str.size(); j++)
	{
		frequency[(int)str[j] - 97]++;
		if (frequency[(int)str[j] - 97] == 1)
			n++;//��һ�γ��ֲż���
	}
	//���ֹ�����ĸ����
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

//ʵ��ʮһ
/*
#include<iostream>
using namespace std;

//�����������ڵ�--------------------
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
//�ݹ�ɾ��------------------------------
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
//��������������������-------------------------------------
template<class T>
class binarySearchTree
{
public:
	//���캯������������
	binarySearchTree(int initialCapacity = 10) { root = NULL; treeSize = 0; }
	~binarySearchTree() { erase(root); }
	//����
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
	//��������
	bool search(const T& theElement);

};
//����---------------------------------------------------------
template<class T>
void binarySearchTree<T>::insert(const T& theElement)
{
	if (search(theElement))
	{
		cout << 0 << endl;
		return;
	}
	int output_xor = 0;
	//Ѱ�Ҳ���λ��
	treeNode<T>* p = root;
	treeNode<T>* pp = NULL;//p�ڵ�ĸ��ڵ�
	while (p != NULL)
	{
		pp = p;//p���ƶ����ӽڵ㣬�ʱ���ppΪp�ĸ��ڵ�
		if (theElement < p->element)
		{
			//����ߣ�p����λ������
			output_xor ^= p->element;
			p->leftSize++;
			p = p->leftChild;
		}
		else if (theElement > p->element)
		{
			//���ұߣ�p����λ��������
			output_xor ^= p->element;
			p = p->rightChild;
		}
	}
	//Ϊelement�����ڵ㣬��pp����
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
//��ѯ------------------------------------------------------
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
	//û�ҵ�
	cout << 0 <<endl;
}
//�ж�Ԫ���Ƿ�������--------------------------------------
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
	//�ж�
	if (searchNode != NULL)
		return true;
	else
		return false;
}
//ɾ��--------------------------------------------------------
template<class T>
void binarySearchTree<T>::del(const T& theElement)
{
	if (!search(theElement))//û�ҵ�
	{
		cout << 0 << endl;
		return;
	}
	int output_xor = theElement;
	//Ѱ��ɾ����λ��
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

	//�������Ӷ����ڣ�������֯���ṹ��ʹ����ֻ��һ������
	if (p->leftChild != NULL && p->rightChild != NULL)
	{
		//Ѱ������������С��Ԫ��
		treeNode<T>* s = p->rightChild;
		treeNode<T>* ps = p;
		while (s->leftChild != NULL)
		{
			//�������
			ps = s;
			s->leftSize--;//������ϸ��ûע�⵽һֱruntime error
			s = s->leftChild;
		}
		//��Ҫɾ��Ԫ�ص�����������С��Ԫ�ط���Ҫɾ����λ��
		//ͬʱ�ع�������
		treeNode<T>* q = new treeNode<T>(s->element);
		q->leftSize = p->leftSize;//�Ƿ������ps�����ܣ�����ָ���Խ��
		q->leftChild = p->leftChild;
		q->rightChild = p->rightChild;
		if (pp == NULL)
			root = q;
		else
			if (p == pp->leftChild)
				pp->leftChild = q;
			else
				pp->rightChild = q;
		//pp��p����
		if (ps == p)
			pp = q;
		else
			pp = ps;
		delete p;
		p = s;
	}
	//��ʱp�����һ������
	treeNode<T>* c;//�Ѻ���ָ������c
	if (p->leftChild != NULL)
		c = p->leftChild;
	else
		c = p->rightChild;
	//ɾ��p
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
//��ѯ����Ϊrank��Ԫ��----------------------------------------
template<class T>
void binarySearchTree<T>::find_rank(int rank)
{
	if (rank <1 || rank > treeSize || root == NULL)//��Ȼ�Ҳ���
	{
		cout << 0 << endl;
		return;
	}
	int index = rank - 1;
	//һ�����ҵ�
	int output_xor = 0;
	treeNode<T>* searchNode = root;
	while (searchNode->leftSize != index && searchNode != NULL)
	{

		//���
		if (index < searchNode->leftSize)
		{
			output_xor ^= searchNode->element;
			searchNode = searchNode->leftChild;
		}
		else//�ҹ�
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
//��������Ϊrank��Ԫ�ص�ֵ��������������1��--------------------
template<class T>
int binarySearchTree<T>::rankOf(int rank)
{
	if (rank <1 || rank > treeSize || root == NULL)//��Ȼ�Ҳ���
		return -1;
	int index = rank - 1;
	//һ�����ҵ�
	treeNode<T>* searchNode = root;
	while (searchNode->leftSize != index)
	{
		//���
		if (index < searchNode->leftSize)
			searchNode = searchNode->leftChild;
		else//�ҹ�
		{
			index = index - (searchNode->leftSize + 1);
			searchNode = searchNode->rightChild;
		}
	}
	return searchNode->element;
}
//һ�����������ڲ���
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

//ʵ��ʮ��
/*
#include<iostream>
#include<queue>
using namespace std;

//����ڵ�--------------------------------------------------------
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
//����ͼ���ڽ���������---------------------------------------------
template<class T>
class linkedGraph
{
public:
	//���캯������������
	linkedGraph(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			exit(1);
		grapgSize = initialCapacity;
		edgeSize = 0;
		num = new vertexNode<T>*[grapgSize + 1];
		for (int i = 1; i <= grapgSize; i++)
		{//0��λ����
			vertexNode<T>* newVertex = new vertexNode<T>(-1);
			num[i] = newVertex;
		}
		reach = new T[grapgSize + 1];//�ж��Ƿ񵽴�
		for (int i = 0; i <= grapgSize; i++)
			reach[i] = 0;
		order = new T[grapgSize + 1];//���bfs���У�0��λΪ���г���
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
	//����
	void combine(const T& vertex1, const T& vertex2);//�ڶ���1��2֮�����һ����
	void erase(const T& vertex1, const T& vertex2);//ɾ������1��2֮��ı�
	void bfs(const T& source);//�����������
	void bfs(T source, T reach[], int label);
	void dfs(const T& source);//�����������
	void rDfs(const T& source);//�ݹ�
	void labelComponent();//��ͨ����/����
	void shortestPath(const T& start, const T& end);//���·��
	//��������
	bool empty() const { return grapgSize == 0; }//�п�
	int vertex() const { return grapgSize; }//���ض������
	int edge() const { return edgeSize; }//���ر���
private:
	int grapgSize;//������
	int edgeSize;//����
	vertexNode<T>** num;//ָ��ָ������飬������������
	//�����������������
	T* reach;
	T* order;
	int index;
};
//����1��2��һ����----------------------------------------------------------------
template<class T>
void linkedGraph<T>::combine(const T& vertex1, const T& vertex2)
{
	if ((vertex1 == vertex2) || vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* newVertex = new vertexNode<T>(vertex2);
	vertexNode<T>* p = num[vertex1];//�����ڵ�
	vertexNode<T>* pp = NULL;//�����ڵ�ĸ��ڵ�
	//Ϊ�½ڵ�Ѱ�Һ��ʵ�λ��
	while (p != NULL && p->element < vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	//����
	if (p == NULL)//��β������
		pp->nextNode = newVertex;
	else//���м����
	{
		pp->nextNode = newVertex;
		newVertex->nextNode = p;
	}
	edgeSize++;
}
//ɾ��1��2��һ����--------------------------------------------------
template<class T>
void linkedGraph<T>::erase(const T& vertex1, const T& vertex2)
{
	if (vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* p = num[vertex1];//�����ڵ�
	vertexNode<T>* pp = NULL;//p�ĸ��ڵ�
	//Ѱ��ɾ��λ��
	while (p != NULL && p->element != vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	if (p == NULL)//û�ҵ�
		exit(1);
	else//�ҵ���
		pp->nextNode = p->nextNode;
	edgeSize--;
}
//�����������----------------------------------
template<class T>
void linkedGraph<T>::bfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	queue<T> que;
	T* reach = new T[grapgSize + 1];//�ж��Ƿ񵽴�
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	T* order = new T[grapgSize + 1];//���bfs���У�0��λΪ���г���
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	reach[source] = 1;//���Ϊ1
	int indexOfOrder = 1;//����order������
	que.push(source);
	while (!que.empty())
	{
		//�Ӷ�����ɾ��һ����ǹ��Ľڵ�
		int vertex = que.front();
		order[indexOfOrder++] = vertex;
		order[0]++;
		que.pop();
		//��������ڽ���vertex��û����Ľڵ�
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
//�����������----------------------------------------
template<class T>
void linkedGraph<T>::dfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	//����
	delete[]reach;
	delete[]order;
	reach = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	order = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	index = 1;
	//�ݹ���������������
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
//�ݹ�-----------------------------------------------
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
//�����ͨ����/����-------------------------
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
	//������������ʱ�临�Ӷ�̫��
	//for (int j = 1; j <= label; j++)
		//for (int i = 1; i <= grapgSize; i++)
			//if (c[i] == j)
			//{
				//cout << i << ' ';
				//break;
			//}
	cout << endl;
}
//���·��--------------------------------------------------------------
template<class T>
void linkedGraph<T>::shortestPath(const T& start, const T& end)
{
	T* dist = new T[grapgSize + 1];//��ʼ�㵽i�ڵ����·���ĳ���
	for (int i = 1; i <= grapgSize; i++)
		dist[i] = -1;//ȫ����δ������
	dist[start] = 0;//��ʼ�㵽��ʼ��ľ���Ϊ0
	queue<T>que;
	que.push(start);
	while (!que.empty())
	{
		T top = que.front();
		que.pop();
		vertexNode<T>* theVertex = num[top];
		theVertex = theVertex->nextNode;//ָ���ڽ���top�ĵ�һ���ڵ�
		for (; theVertex != NULL; theVertex = theVertex->nextNode)
			if (dist[theVertex->element] == -1)
			{
				que.push(theVertex->element);
				dist[theVertex->element] = dist[top] + 1;
			}
	}
	cout << dist[end] << endl;
}
//������������������
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

//���ݽṹʵ���������