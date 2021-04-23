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