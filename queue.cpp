#include"illegalParameterValue.h"

//2020-10-25 数组描述的output尚待改进

//队列的数组定义----------------------------------------------------------------------------------------
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
	int size() const { return (theBack - theFront + arrayLength) % arrayLength; }//返回元素个数
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
	delete []queue;
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
//扩展类的定义-----------------------------------------------------
template<class T>
class extendedQueue:public arrayQueue<T>
{
public:
	void input(int theSize = 5);//创建
	void output();//输出
	void split(arrayQueue<T>& a, arrayQueue<T>& b);//分解
	void combine(arrayQueue<T>& x);//合并
};
//输入----------------------------------------------------------------------
template<class T>
void extendedQueue<T>::input(int theSize)
{
	for (int i = 0; i < theSize; i++)
		cin >> arrayQueue<T>::queue[i];
	arrayQueue<T>::queueFront = arrayQueue<T>::arrayLength - 1;
	arrayQueue<T>::queueBack = theSize - 1;
}
//输出------------------------------------------------------------------------
template<class T>
void extendedQueue<T>::output()
{
	while (arrayQueue<T>::queueFront != arrayQueue<T>::queueBack)
	{
		cout << arrayQueue<T>::theFront() << ' ';
		arrayQueue<T>::pop();
	}
}
//分解----------------------------------------------------------------------------
template<class T>
void extendedQueue<T>::split(arrayQueue<T>& a, arrayQueue<T>& b)
{
	int len = arrayQueue<T>::size();
	for (int i = 0; i < len; i++)
		if (i % 2 == 0)
		{
			a.push(arrayQueue<T>::theFront);
			arrayQueue<T>::pop();
		}
		else
		{
			b.push(arrayQueue<T>::theFront);
			arrayQueue<T>::pop();
		}
}
//合并----------------------------------------------------------------------------
template<class T>
void extendedQueue<T>::combine(arrayQueue<T>& x)
{
	int newLength = arrayQueue<T>::size() + x.size();
	T* newQueue = new T[newLength];
	int i = 0;//计数
	while (arrayQueue<T>::queueFront != arrayQueue<T>::queueBack
		&& x.queueFront != x.queueBack)
		if (i % 2 == 0)
		{
			newQueue[i] = arrayQueue<T>::theFront();
			arrayQueue<T>::pop();
			i++;
		}
		else
		{
			newQueue[i] = x.theFront();
			x.pop();
			i++;
		}
	while (arrayQueue<T>::queueFront != arrayQueue<T>::queueBack)
	{
		newQueue[i] = arrayQueue<T>::theFront();
		arrayQueue<T>::pop();
		i++;
	}
	while (x.queueFront != x.queueBack)
	{
		newQueue[i] = x.theFront();
		x.pop();
		i++;
	}
	//重置
	arrayQueue<T>::arrayLength = newLength;
	arrayQueue<T>::queueBack = arrayQueue<T>::arrayLength - 1;
	arrayQueue<T>::queueFront = arrayQueue<T>::queueBack;//此时队列满
	delete[]arrayQueue<T>::queue;
	arrayQueue<T>::queue = newQueue;
}

//节点
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
	T&theFront()
	{
		if (ququeSize == 0)
			throw illegalParameterValue("queue empty");
		return queueFront->data;
	}
	T& theBack()
	{
		if(ququeSize==0)
			throw illegalParameterValue("queue empty");
		return queueBack->data;
	}
	void pop();
	void push(const T& theElement);
	//其他方法
	void input(int theSize = 5);
	void output();
	void split(linkedQueue<T>& b);
	void combine(linkedQueue<T>& b);
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
		throw illegalParameterValue("queue empty");
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
//创建----------------------------------------
template<class T>
void linkedQueue<T>::input(int theSize)
{
	T element;
	for (int i = 0; i < theSize; i++)
	{
		cin >> element;
		push(element);
	}
}
//输出---------------------------------------------
template<class T>
void linkedQueue<T>::output()
{
	chainNode<T>* currentNode = queueFront;
	while (currentNode != NULL)
	{
		cout << currentNode->data << ' ';
		currentNode = currentNode->next;
	}
}
//分裂----------------------------------------------------------------
template<class T>
void linkedQueue<T>::split(linkedQueue<T>& b)
{
	if (ququeSize < 2)//0个和1个不分解
		throw illegalParameterValue("queue size is not matched");
	//找到分解的位置
	chainNode<T>* splitNode = queueFront;
	int len = ququeSize / 2;
	for (int i = 1; i < len; i++)
		splitNode = splitNode->next;
	b.ququeSize = ququeSize - len;
	ququeSize = len;
	//分解
	b.queueFront = splitNode->next;
	b.queueBack = queueBack;
	queueBack = splitNode;
	queueBack->next = NULL;
}
//合并---------------------------------------------------------------------------------------
template<class T>
void linkedQueue<T>::combine(linkedQueue<T>& b)
{
	//以下为错误示范，不能直接把指针相接
	//析构时会对b析构两次导致错误
	//chainNode<T>* newNode = b.queueFront;
	//queueBack->next = newNode;
	//queueBack = b.queueBack;
	//ququeSize = ququeSize + b.ququeSize;
	chainNode<T>*currentNode = b.queueFront;
	while (currentNode != NULL)
	{
		chainNode<T>* newBack = new chainNode<T>(currentNode->data,NULL);
		queueBack->next = newBack;
		queueBack = newBack;
		ququeSize++;
		currentNode = currentNode->next;
	}
}