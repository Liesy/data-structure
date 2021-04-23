#include"illegalParameterValue.h"
#include"change array length.h"
#include <iomanip>
//使用iosmanip的setprecision(n)函数将浮点数小数部分设置为n位

//2020-10-21 括号匹配尚待改进，圆括号要在右方括号出现之前完成匹配，否则就是错误的
//2020-10-22 extendedStack类的input和format尚需修改，只能输入字符串

//栈的数组定义----------------------------------------------------------------------
template<class T>
class arrayStack
{
public:
	//构造函数、析构函数
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[]stack; }
	//方法
	bool empty() const { return stackTop == -1; }//判断是否为空
	bool full() const { return stackTop == arrayLength - 1; }//判断栈是否已满
	int size() const { return stackTop + 1; }//返回元素个数
	T& top()//返回栈顶元素
	{
		if (empty())//栈空
			throw illegalParameterValue("stack is empty");
		return stack[stackTop];
	}
	void pop()//删除栈顶元素
	{
		if (empty())
			throw illegalParameterValue("stack is empty");
		stack[stackTop--].~T();//调用T的析构函数
	}
	void push(const T&);//将元素压入栈顶
	void copyStack(arrayStack<T>&);//复制栈
	void output()//输出栈内元素但保留栈
	{
		for (int i = size() - 1; i >= 0; i--)
			cout << stack[i] << ' ';
		cout << endl;
	}
protected:
	int stackTop;//栈顶索引
	int arrayLength;//栈容量
	T* stack;//元素数组
};
//构造函数-------------------------------------------------------------
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be >0");
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;//栈空
}
//入栈------------------------------------------------------------------
template<class T>
void arrayStack<T>::push(const T& element)
{
	if (full())//栈满
	{
		changeLength(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = element;
}
//复制栈---------------------------------------------------------
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
//扩展栈的定义----------------------------------------------------------------
template<class T>
class extendedStack:public arrayStack<T>
{
public:
	extendedStack(int initialCapacity = 10) :arrayStack<T>(initialCapacity) {};
	~extendedStack() {};
	void input();//输入栈
	string format();//将栈转变为一个适合输出的串
	void split(extendedStack<T>& a, extendedStack<T>& b);//栈分裂
	void combine(extendedStack<T>&);//栈合并
};
//输入-----------------------------------------------------------------------------
template<class T>
void extendedStack<T>::input()
{
	string str;
	getline(cin, str);
	for (int i = 0; i < int(str.length()); i++)
		arrayStack<T>::push(str.at(i));
}
//转换格式-----------------------------------------------------------
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
//将一个栈分裂为两个栈----------------------------------------------------------
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
//栈合并---------------------------------------------------------
template<class T>
void extendedStack<T>::combine(extendedStack<T>& x)
{
	if (x.arrayStack<T>::empty())
		return;
	for (int i = 0; i < x.arrayStack<T>::size(); i++)
		arrayStack<T>::push(x.arrayStack<T>::stack[i]);
}

//节点-----------------------------------------------------------------
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
//栈的链表定义----------------------------------------------------
template<class T>
class linkedStack
{
public:
	//构造函数、析构函数
	linkedStack(int initialCapacity = 10)
	{
		stackTop = NULL;
		stackSize = 0;
	}
	~linkedStack();
	//方法
	bool empty() const { return stackSize == 0; }//判空
	int size() const { return stackSize; }//返回栈内元素个数
	T& top()//返回栈顶元素
	{
		if (empty())
			throw illegalParameterValue("stack is empty");
		return stackTop->data;
	}
	void pop();//删除栈顶元素
	void push(const T& theElement)//将元素压入栈
	{
		stackTop = new chainNode<T>(theElement, stackTop);
		stackSize++;
	}
private:
	chainNode<T>* stackTop;//栈顶指针
	int stackSize;//栈中元素个数
};
//析构函数------------------------------------------------
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
//删除栈顶元素----------------------------------------------
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

//输出匹配的括号-------------------------------------------
void PrintMatchedPairs(string expr)
{
	arrayStack<int> round_brackets;//圆括号栈
	arrayStack<int> square_brackets;//方括号栈
	int strLen = (int)expr.size();
	//扫描表达式寻找括号
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
	//若栈不为空，则在栈中的左括号不匹配
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
