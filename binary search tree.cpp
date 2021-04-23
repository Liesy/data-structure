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