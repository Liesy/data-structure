#include"illegalParameterValue.h"

//2020-10-25 ����������output�д��Ľ�

//���е����鶨��----------------------------------------------------------------------------------------
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
	int size() const { return (theBack - theFront + arrayLength) % arrayLength; }//����Ԫ�ظ���
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
	delete []queue;
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
//��չ��Ķ���-----------------------------------------------------
template<class T>
class extendedQueue:public arrayQueue<T>
{
public:
	void input(int theSize = 5);//����
	void output();//���
	void split(arrayQueue<T>& a, arrayQueue<T>& b);//�ֽ�
	void combine(arrayQueue<T>& x);//�ϲ�
};
//����----------------------------------------------------------------------
template<class T>
void extendedQueue<T>::input(int theSize)
{
	for (int i = 0; i < theSize; i++)
		cin >> arrayQueue<T>::queue[i];
	arrayQueue<T>::queueFront = arrayQueue<T>::arrayLength - 1;
	arrayQueue<T>::queueBack = theSize - 1;
}
//���------------------------------------------------------------------------
template<class T>
void extendedQueue<T>::output()
{
	while (arrayQueue<T>::queueFront != arrayQueue<T>::queueBack)
	{
		cout << arrayQueue<T>::theFront() << ' ';
		arrayQueue<T>::pop();
	}
}
//�ֽ�----------------------------------------------------------------------------
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
//�ϲ�----------------------------------------------------------------------------
template<class T>
void extendedQueue<T>::combine(arrayQueue<T>& x)
{
	int newLength = arrayQueue<T>::size() + x.size();
	T* newQueue = new T[newLength];
	int i = 0;//����
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
	//����
	arrayQueue<T>::arrayLength = newLength;
	arrayQueue<T>::queueBack = arrayQueue<T>::arrayLength - 1;
	arrayQueue<T>::queueFront = arrayQueue<T>::queueBack;//��ʱ������
	delete[]arrayQueue<T>::queue;
	arrayQueue<T>::queue = newQueue;
}

//�ڵ�
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
	//��������
	void input(int theSize = 5);
	void output();
	void split(linkedQueue<T>& b);
	void combine(linkedQueue<T>& b);
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
		throw illegalParameterValue("queue empty");
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
//����----------------------------------------
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
//���---------------------------------------------
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
//����----------------------------------------------------------------
template<class T>
void linkedQueue<T>::split(linkedQueue<T>& b)
{
	if (ququeSize < 2)//0����1�����ֽ�
		throw illegalParameterValue("queue size is not matched");
	//�ҵ��ֽ��λ��
	chainNode<T>* splitNode = queueFront;
	int len = ququeSize / 2;
	for (int i = 1; i < len; i++)
		splitNode = splitNode->next;
	b.ququeSize = ququeSize - len;
	ququeSize = len;
	//�ֽ�
	b.queueFront = splitNode->next;
	b.queueBack = queueBack;
	queueBack = splitNode;
	queueBack->next = NULL;
}
//�ϲ�---------------------------------------------------------------------------------------
template<class T>
void linkedQueue<T>::combine(linkedQueue<T>& b)
{
	//����Ϊ����ʾ��������ֱ�Ӱ�ָ�����
	//����ʱ���b�������ε��´���
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