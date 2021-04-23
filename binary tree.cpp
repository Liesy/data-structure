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
