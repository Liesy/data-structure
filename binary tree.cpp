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
