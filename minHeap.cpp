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