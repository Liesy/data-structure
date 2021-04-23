#include<iostream>
#include<queue>
using namespace std;

//����ڵ�--------------------------------------------------------
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
//����ͼ���ڽ���������---------------------------------------------
template<class T>
class linkedGraph
{
public:
	//���캯������������
	linkedGraph(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			exit(1);
		grapgSize = initialCapacity;
		edgeSize = 0;
		num = new vertexNode<T>*[grapgSize + 1];
		for (int i = 1; i <= grapgSize; i++)
		{//0��λ����
			vertexNode<T>* newVertex = new vertexNode<T>(-1);
			num[i] = newVertex;
		}
		reach = new T[grapgSize + 1];//�ж��Ƿ񵽴�
		for (int i = 0; i <= grapgSize; i++)
			reach[i] = 0;
		order = new T[grapgSize + 1];//���bfs���У�0��λΪ���г���
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
	//����
	void combine(const T& vertex1, const T& vertex2);//�ڶ���1��2֮�����һ����
	void erase(const T& vertex1, const T& vertex2);//ɾ������1��2֮��ı�
	void bfs(const T& source);//�����������
	void bfs(T source, T reach[], int label);
	void dfs(const T& source);//�����������
	void rDfs(const T& source);//�ݹ�
	void labelComponent();//��ͨ����/����
	void shortestPath(const T& start, const T& end);//���·��
	//��������
	bool empty() const { return grapgSize == 0; }//�п�
	int vertex() const { return grapgSize; }//���ض������
	int edge() const { return edgeSize; }//���ر���
private:
	int grapgSize;//������
	int edgeSize;//����
	vertexNode<T>** num;//ָ��ָ������飬������������
	//�����������������
	T* reach;
	T* order;
	int index;
};
//����1��2��һ����----------------------------------------------------------------
template<class T>
void linkedGraph<T>::combine(const T& vertex1, const T& vertex2)
{
	if ((vertex1 == vertex2) || vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* newVertex = new vertexNode<T>(vertex2);
	vertexNode<T>* p = num[vertex1];//�����ڵ�
	vertexNode<T>* pp = NULL;//�����ڵ�ĸ��ڵ�
	//Ϊ�½ڵ�Ѱ�Һ��ʵ�λ��
	while (p != NULL && p->element < vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	//����
	if (p == NULL)//��β������
		pp->nextNode = newVertex;
	else//���м����
	{
		pp->nextNode = newVertex;
		newVertex->nextNode = p;
	}
	edgeSize++;
}
//ɾ��1��2��һ����--------------------------------------------------
template<class T>
void linkedGraph<T>::erase(const T& vertex1, const T& vertex2)
{
	if (vertex1<1 || vertex2<1 || vertex1>grapgSize || vertex2>grapgSize)
		exit(1);
	vertexNode<T>* p = num[vertex1];//�����ڵ�
	vertexNode<T>* pp = NULL;//p�ĸ��ڵ�
	//Ѱ��ɾ��λ��
	while (p != NULL && p->element != vertex2)
	{
		pp = p;
		p = p->nextNode;
	}
	if (p == NULL)//û�ҵ�
		exit(1);
	else//�ҵ���
		pp->nextNode = p->nextNode;
	edgeSize--;
}
//�����������----------------------------------
template<class T>
void linkedGraph<T>::bfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	queue<T> que;
	T* reach = new T[grapgSize + 1];//�ж��Ƿ񵽴�
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	T* order = new T[grapgSize + 1];//���bfs���У�0��λΪ���г���
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	reach[source] = 1;//���Ϊ1
	int indexOfOrder = 1;//����order������
	que.push(source);
	while (!que.empty())
	{
		//�Ӷ�����ɾ��һ����ǹ��Ľڵ�
		int vertex = que.front();
		order[indexOfOrder++] = vertex;
		order[0]++;
		que.pop();
		//��������ڽ���vertex��û����Ľڵ�
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
//�����������----------------------------------------
template<class T>
void linkedGraph<T>::dfs(const T& source)
{
	if (source<1 || source>grapgSize)
		exit(1);
	//����
	delete[]reach;
	delete[]order;
	reach = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		reach[i] = 0;
	order = new T[grapgSize + 1];
	for (int i = 0; i <= grapgSize; i++)
		order[i] = 0;
	index = 1;
	//�ݹ���������������
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
//�ݹ�-----------------------------------------------
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
//�����ͨ����/����-------------------------
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
	//������������ʱ�临�Ӷ�̫��
	//for (int j = 1; j <= label; j++)
		//for (int i = 1; i <= grapgSize; i++)
			//if (c[i] == j)
			//{
				//cout << i << ' ';
				//break;
			//}
	cout << endl;
}
//���·��--------------------------------------------------------------
template<class T>
void linkedGraph<T>::shortestPath(const T& start, const T& end)
{
	T* dist = new T[grapgSize + 1];//��ʼ�㵽i�ڵ����·���ĳ���
	for (int i = 1; i <= grapgSize; i++)
		dist[i] = -1;//ȫ����δ������
	dist[start] = 0;//��ʼ�㵽��ʼ��ľ���Ϊ0
	queue<T>que;
	que.push(start);
	while (!que.empty())
	{
		T top = que.front();
		que.pop();
		vertexNode<T>* theVertex = num[top];
		theVertex = theVertex->nextNode;//ָ���ڽ���top�ĵ�һ���ڵ�
		for (; theVertex != NULL; theVertex = theVertex->nextNode)
			if (dist[theVertex->element] == -1)
			{
				que.push(theVertex->element);
				dist[theVertex->element] = dist[top] + 1;
			}
	}
	cout << dist[end] << endl;
}
//������������������
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