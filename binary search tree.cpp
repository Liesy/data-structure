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