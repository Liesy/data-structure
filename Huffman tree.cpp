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