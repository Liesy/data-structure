#include<iostream>
#include<queue>
using namespace std;

//顶点节点--------------------------------------------------------
template<class T>
struct vertexNode
{
	T element;
	vertexNode<T>* nextNode;
	vertexNode() {}
	vertexNode(const T& theElement)
	{
		element = theElement;
		nextNode = NULL;
	}
	vertexNode(const T& theElement, vertexNode<T>* theNext)
	{
		element = theElement;
		nextNode = theNext;
	}
};
//无向图的邻接链表描述---------------------------------------------
template<class T>
class linkedGraph
{
public:
	//构造函数、析构函数
	linkedGraph(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			exit(1);
		grapgSize = initialCapacity;
		edgeSize = 0;
		num = new vertexNode<T>*[grapgSize + 1];
		for (int i = 1; i <= grapgSize; i++)
		{//0号位不用
			vertexNode<T>* newVertex = new vertexNode<T>(-1);
			num[i] = newVertex;
		}
		reach = new T[grapgSize + 1];//判断是否到达
		for (int i = 0; i <= grapgSize; i++)
			reach[i] = 0;
		order = new T[grapgSize + 1];//输出bfs序列，0号位为序列长度
		for (int i = 0; i <= grapgSize; i++)
			order[i] = 0;
		index = 1;
	}
	~linkedGraph()
	{
		delete[]num;
		delete[]reach;
		delete[]order;
	}
	//方法
	void combine(const T& vertex1, const T& vertex2);//在顶点1和2之间插入一条边
	void erase(const T& vertex1, const T& vertex2);//删除顶点1和2之间的边
	void bfs(const T& source);//广度优先搜索
	void bfs(T source, T reach[], int label);
	void dfs(const T& source);//深度优先搜索
	void rDfs(const T& source);//递归
	void labelComponent();//连通分量/构件
	void shortestPath(const T& start, const T& end);//最短路径
	//其他方法
	bool empty() const { return grapgSize == 0; }//判空
	int vertex() const { return grapgSize; }//返回顶点个数
	int edge() const { return edgeSize; }//返回边数
private:
	int grapgSize;//顶点数
	int edgeSize;//边数
	vertexNode<T>** num;//指向指针的数组，按顶点编号升序
	//深度优先搜索的数组
	T* reach;
	T* order;
	int index;
};
//插入1到2的一条边----------------------------------------------------------------
template<class T>
void linkedGraph<T>::combine(const T& vertex1, const T& vertex2)
{
	if ((vertex1 == vertex2) || vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* newVertex = new vertexNode<T>(vertex2);
	vertexNode<T>* p = num[vertex1];//搜索节点
	vertexNode<T>* pp = NULL;//搜索节点的父节点
	//为新节点寻找合适的位置
	while (p != NULL && p->element < vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	//插入
	if (p == NULL)//在尾部插入
		pp->nextNode = newVertex;
	else//在中间插入
	{
		pp->nextNode = newVertex;
		newVertex->nextNode = p;
	}
	edgeSize++;
}
//删除1到2的一条边--------------------------------------------------
template<class T>
void linkedGraph<T>::erase(const T& vertex1, const T& vertex2)
{
	if (vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* p = num[vertex1];//搜索节点
	vertexNode<T>* pp = NULL;//p的父节点
	//寻找删除位置
	while (p != NULL && p->element != vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	if (p == NULL)//没找到
		exit(1);
	else//找到了
		pp->nextNode = p->nextNode;
	edgeSize--;
}
//广度优先搜索----------------------------------
template<class T>
void linkedGraph<T>::bfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	queue<T> que;
	T* reach = new T[grapgSize + 1];//判断是否到达
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	T* order = new T[grapgSize + 1];//输出bfs序列，0号位为序列长度
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	reach[source] = 1;//标记为1
	int indexOfOrder = 1;//数组order的索引
	que.push(source);
	while (!que.empty())
	{
		//从队列中删除一个标记过的节点
		int vertex = que.front();
		order[indexOfOrder++] = vertex;
		order[0]++;
		que.pop();
		//标记所有邻接于vertex且没到达的节点
		vertexNode<T>* currentVertex = num[vertex];
		currentVertex = currentVertex->nextNode;
		while (currentVertex != NULL)
		{
			if (reach[currentVertex->element] == 0)
			{
				que.push(currentVertex->element);
				reach[currentVertex->element] = 1;
			}
			currentVertex = currentVertex->nextNode;
		}
	}
	cout << order[0] << endl;
	for (int i = 1; i <= grapgSize; i++)
	{
		if (order[i] == 0)
			break;
		else
			cout << order[i] << ' ';
	}
	cout << endl;
}
template<class T>
void linkedGraph<T>::bfs(T source, T reach[], int label)
{
	queue<T>que;
	reach[source] = label;
	que.push(source);
	while (!que.empty())
	{
		int w = que.front();
		que.pop();
		vertexNode<T>* u = num[w];
		u = u->nextNode;
		for (; u != NULL; u = u->nextNode)
			if (reach[u->element] == 0)
			{
				que.push(u->element);
				reach[u->element] = label;
			}
	}
}
//深度优先搜索----------------------------------------
template<class T>
void linkedGraph<T>::dfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	//重置
	delete[]reach;
	delete[]order;
	reach = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	order = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	index = 1;
	//递归进行深度优先搜索
	rDfs(source);
	cout << order[0] << endl;
	for (int i = 1; i <= grapgSize; i++)
	{
		if (order[i] == 0)
			break;
		else
			cout << order[i] << ' ';
	}
	cout << endl;
}
//递归-----------------------------------------------
template<class T>
void linkedGraph<T>::rDfs(const T& source)
{
	reach[source] = 1;
	order[0]++;
	order[index++] = source;
	vertexNode<T>* currentVertex = num[source];
	currentVertex = currentVertex->nextNode;
	for (; currentVertex != NULL; currentVertex = currentVertex->nextNode)
	{
		int w = currentVertex->element;
		if (reach[w] == 0)
			rDfs(w);
	}
}
//输出连通分量/构件-------------------------
template<class T>
void linkedGraph<T>::labelComponent()
{
	T* c = new T[grapgSize + 1];
	for (int i = 1; i <= grapgSize; i++)
		c[i] = 0;
	int label = 0;
	int* arr = new int[grapgSize + 1];
	int index = 1;
	for (int i = 1; i <= grapgSize; i++)
		if (c[i] == 0)
		{
			arr[index++] = i;
			label++;
			bfs(i, c, label);
		}
	cout << label << endl;
	for (int i = 1; i <= label; i++)
		cout << arr[i] << ' ';
	//下面这个输出的时间复杂度太大
	//for (int j = 1; j <= label; j++)
		//for (int i = 1; i <= grapgSize; i++)
			//if (c[i] == j)
			//{
				//cout << i << ' ';
				//break;
			//}
	cout << endl;
}
//最短路径--------------------------------------------------------------
template<class T>
void linkedGraph<T>::shortestPath(const T& start, const T& end)
{
	T* dist = new T[grapgSize + 1];//起始点到i节点最短路径的长度
	for (int i = 1; i <= grapgSize; i++)
		dist[i] = -1;//全部都未遍历过
	dist[start] = 0;//起始点到起始点的距离为0
	queue<T>que;
	que.push(start);
	while (!que.empty())
	{
		T top = que.front();
		que.pop();
		vertexNode<T>* theVertex = num[top];
		theVertex = theVertex->nextNode;//指向邻接于top的第一个节点
		for (; theVertex != NULL; theVertex = theVertex->nextNode)
			if (dist[theVertex->element] == -1)
			{
				que.push(theVertex->element);
				dist[theVertex->element] = dist[top] + 1;
			}
	}
	cout << dist[end] << endl;
}
//以下主函数做测试用
int main()
{
	int n, m, s, t, option, u, v;
	cin >> n >> m >> s >> t;
	linkedGraph<int>graph(n);
	for (int i = 0; i < m; i++)
	{
		cin >> option >> u >> v;
		if (option == 0)
		{
			graph.combine(u, v);
			graph.combine(v, u);
		}
		else if (option == 1)
		{
			graph.erase(u, v);
			graph.erase(v, u);
		}
	}
	graph.labelComponent();
	graph.dfs(s);
	graph.bfs(t);
	graph.shortestPath(s, t);
	return 0;
}