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