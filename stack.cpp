#include"illegalParameterValue.h"
#include"change array length.h"
#include <iomanip>
//ʹ��iosmanip��setprecision(n)������������С����������Ϊnλ

//2020-10-21 ����ƥ���д��Ľ���Բ����Ҫ���ҷ����ų���֮ǰ���ƥ�䣬������Ǵ����
//2020-10-22 extendedStack���input��format�����޸ģ�ֻ�������ַ���

//ջ�����鶨��----------------------------------------------------------------------
template<class T>
class arrayStack
{
public:
	//���캯������������
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[]stack; }
	//����
	bool empty() const { return stackTop == -1; }//�ж��Ƿ�Ϊ��
	bool full() const { return stackTop == arrayLength - 1; }//�ж�ջ�Ƿ�����
	int size() const { return stackTop + 1; }//����Ԫ�ظ���
	T& top()//����ջ��Ԫ��
	{
		if (empty())//ջ��
			throw illegalParameterValue("stack is empty");
		return stack[stackTop];
	}
	void pop()//ɾ��ջ��Ԫ��
	{
		if (empty())
			throw illegalParameterValue("stack is empty");
		stack[stackTop--].~T();//����T����������
	}
	void push(const T&);//��Ԫ��ѹ��ջ��
	void copyStack(arrayStack<T>&);//����ջ
	void output()//���ջ��Ԫ�ص�����ջ
	{
		for (int i = size() - 1; i >= 0; i--)
			cout << stack[i] << ' ';
		cout << endl;
	}
protected:
	int stackTop;//ջ������
	int arrayLength;//ջ����
	T* stack;//Ԫ������
};
//���캯��-------------------------------------------------------------
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be >0");
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;//ջ��
}
//��ջ------------------------------------------------------------------
template<class T>
void arrayStack<T>::push(const T& element)
{
	if (full())//ջ��
	{
		changeLength(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = element;
}
//����ջ---------------------------------------------------------
template<class T>
void arrayStack<T>::copyStack(arrayStack<T>& x)
{
	delete[]stack;
	arrayLength = x.arrayLength;
	stack = new T[arrayLength];
	if (x.empty())
		stackTop = -1;
	else
	{
		stackTop = x.stackTop;
		for (int i = 0; i < x.size(); i++)
			stack[i] = x.stack[i];
	}
}
//��չջ�Ķ���----------------------------------------------------------------
template<class T>
class extendedStack:public arrayStack<T>
{
public:
	extendedStack(int initialCapacity = 10) :arrayStack<T>(initialCapacity) {};
	~extendedStack() {};
	void input();//����ջ
	string format();//��ջת��Ϊһ���ʺ�����Ĵ�
	void split(extendedStack<T>& a, extendedStack<T>& b);//ջ����
	void combine(extendedStack<T>&);//ջ�ϲ�
};
//����-----------------------------------------------------------------------------
template<class T>
void extendedStack<T>::input()
{
	string str;
	getline(cin, str);
	for (int i = 0; i < int(str.length()); i++)
		arrayStack<T>::push(str.at(i));
}
//ת����ʽ-----------------------------------------------------------
template<class T>
string extendedStack<T>::format()
{
	string str;
	int len = arrayStack<T>::size();
	for (int i = 0; i < len; i++)
	{
		str.insert((string::size_type)0, 1, arrayStack<T>::top());
		arrayStack<T>::pop();
	}
	return str;
}
//��һ��ջ����Ϊ����ջ----------------------------------------------------------
template<class T>
void extendedStack<T>::split(extendedStack<T>& a, extendedStack<T>& b)
{
	if (arrayStack<T>::empty())
		throw illegalParameterValue("stack can't split");
	for (int i = 0; i < arrayStack<T>::size(); i++)
		if (i < (arrayStack<T>::size() / 2))
			a.arrayStack<T>::push(arrayStack<T>::stack[i]);
		else
			b.arrayStack<T>::push(arrayStack<T>::stack[i]);
}
//ջ�ϲ�---------------------------------------------------------
template<class T>
void extendedStack<T>::combine(extendedStack<T>& x)
{
	if (x.arrayStack<T>::empty())
		return;
	for (int i = 0; i < x.arrayStack<T>::size(); i++)
		arrayStack<T>::push(x.arrayStack<T>::stack[i]);
}

//�ڵ�-----------------------------------------------------------------
template<class T>
struct chainNode
{
	T data;
	chainNode<T>* nextNode;

	chainNode() {}
	chainNode(const T& theElement) { this->data = theElement; }
	chainNode(const T& theElement, chainNode<T>* next)
	{
		this->data = theElement;
		this->nextNode = next;
	}
};
//ջ��������----------------------------------------------------
template<class T>
class linkedStack
{
public:
	//���캯������������
	linkedStack(int initialCapacity = 10)
	{
		stackTop = NULL;
		stackSize = 0;
	}
	~linkedStack();
	//����
	bool empty() const { return stackSize == 0; }//�п�
	int size() const { return stackSize; }//����ջ��Ԫ�ظ���
	T& top()//����ջ��Ԫ��
	{
		if (empty())
			throw illegalParameterValue("stack is empty");
		return stackTop->data;
	}
	void pop();//ɾ��ջ��Ԫ��
	void push(const T& theElement)//��Ԫ��ѹ��ջ
	{
		stackTop = new chainNode<T>(theElement, stackTop);
		stackSize++;
	}
private:
	chainNode<T>* stackTop;//ջ��ָ��
	int stackSize;//ջ��Ԫ�ظ���
};
//��������------------------------------------------------
template<class T>
linkedStack<T>::~linkedStack()
{
	while (stackTop != NULL)
	{
		chainNode<T>* nextNode = stackTop->nextNode;
		delete stackTop;
		stackTop = nextNode;
	}
}
//ɾ��ջ��Ԫ��----------------------------------------------
template<class T>
void linkedStack<T>::pop()
{
	if (empty())
		throw illegalParameterValue("stack is empty");
	chainNode<T>* nextNode = stackTop->nextNode;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}

//���ƥ�������-------------------------------------------
void PrintMatchedPairs(string expr)
{
	arrayStack<int> round_brackets;//Բ����ջ
	arrayStack<int> square_brackets;//������ջ
	int strLen = (int)expr.size();
	//ɨ����ʽѰ������
	for (int i = 0; i < strLen; i++)
		switch (expr.at(i))
		{
		case'(':
			round_brackets.push(i);
			break;
		case'[':
			square_brackets.push(i);
			break;
		case')':
			try
			{
				cout << round_brackets.top() << ' ' << i << endl;
				round_brackets.pop();
			}
			catch (illegalParameterValue message)
			{
				cout << "no match for right round bracket" << " at " << i << endl;
			}
			break;
		case']':
			try
			{
				cout << square_brackets.top() << ' ' << i << endl;
				square_brackets.pop();
			}
			catch (illegalParameterValue message)
			{
				cout << "no match for right square bracket" << " at " << i << endl;
			}
			break;
		default:
			break;
		}
	//��ջ��Ϊ�գ�����ջ�е������Ų�ƥ��
	while (!round_brackets.empty())
	{
		cout << "no match for left round bracket at " << round_brackets.top() << endl;
		round_brackets.pop();
	}
	while (!square_brackets.empty())
	{
		cout << "no match for left square bracket at " << square_brackets.top() << endl;
		square_brackets.pop();
	}
}
