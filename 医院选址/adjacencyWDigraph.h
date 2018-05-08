
//邻接矩阵加权有向图

#ifndef adjacencyWDigraph_
#define adjacencyWDigraph_

#include <iostream>
#include <sstream>
#include<stack>
#include"weightedEdge.h"

using namespace std;

template <class T>
class adjacencyWDigraph
{
protected:
	int n;//点数        
	int e;//边数   
	T **a;//邻接矩阵存储           
	T noEdge;

public:
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0) {
		// 构造方法
		if (numberOfVertices < 0)
			throw "顶点数必须大于等于0";
		n = numberOfVertices;
		e = 0;
		noEdge = theNoEdge;
		a = new int*[n + 1];
		for (int i = 0; i < n + 1; i++) {
			a[i] = new int[n + 1];
		}
		for (int i = 1; i <= n; i++)
			// 初始化邻接矩阵
			fill(a[i], a[i] + n + 1, noEdge);
	}

	~adjacencyWDigraph() { delete2dArray(a, n + 1); }

	int numberOfVertices() const { return n; }

	int numberOfEdges() const { return e; }

	bool directed() const { return true; }

	bool weighted() const { return true; }

	void initByArray(int **arr) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				a[i][j] = arr[i][j];
			}
		}
	}

	bool existsEdge(int i, int j) const
	{//返回是否存在i到j的边，存在返回true，不存在返回false
		if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
			return false;
		else
			return true;
	}

	void delete2dArray(T ** &theArray, int numberOfRows)
	{

		for (int i = 0; i < numberOfRows; i++)
			delete[] theArray[i];

		delete[] theArray;
		theArray = 0;
	}



	void insertEdge(edge<T> *theEdge)
	{//插入边，如果已存在更新权值
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();

		if (a[v1][v2] == noEdge)
			e++;
		a[v1][v2] = theEdge->weight();
		dfs(v1);
		if (swi)
			throw exception("有闭环！！！");
	}


	int vis[2600];
	bool swi=false;
	bool dfs(int v) {
		vis[v] = -1;
		for (int i = 1; i <= n; i++)
		{
			if (a[v][i] != 0 && !vis[i]) {
				dfs(i);
				vis[i] = 1;
			}
			if (a[v][i] != 0 && vis[i] == -1) {
				swi = true;
				return true;
			}
		}
		return false;
	}

	void eraseEdge(int i, int j)
	{// 删除i到j的边
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			e--;
		}
	}

	void checkVertex(int theVertex) const
	{//检查点是否合法
		if (theVertex < 1 || theVertex > n)
			throw "不合法顶点！！！";
	}

	class vertexIterator
	{
	public:
		vertexIterator(T* theRow, T theNoEdge, int numberOfVertices)
		{
			row = theRow;
			noEdge = theNoEdge;
			n = numberOfVertices;
			currentVertex = 1;
		}

		~vertexIterator() {}

		int next()
		{// 返回下一个邻接节点,没有则返回0
			for (int j = currentVertex; j <= n; j++)
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					return j;
				}
			currentVertex = n + 1;
			return 0;
		}
	protected:
		T * row;       
		T noEdge;
		int n;
		int currentVertex;
	};

	vertexIterator* iterator(int theVertex)
	{// 返回theVertex的迭代器
		checkVertex(theVertex);
		return new vertexIterator(a[theVertex], noEdge, n);
	}


	void output(ostream& out) const
	{// 输出邻接矩阵
		for (int i = 1; i <= n; i++)
		{
			copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, "  "));
			out << endl;
		}
	}


	void AOV(int **theList) {
		//返回false，当且仅当有向图没有拓扑序列
		//如果存在一个拓扑序列，将其赋给theOrder[0:n-1]
		if (!directed())//确定是否为有向图
			throw "不是有向图";

		int n = numberOfVertices();

		// 计算入度
		int *inDegree = new int[n + 1];
		fill(inDegree + 1, inDegree + n + 1, 0);
		int *Ve = new int[n + 1];
		fill(Ve+1, Ve + n + 1, 0);
		for (int i = 1; i <= n; i++)
		{// 顶点i的出边
			vertexIterator *ii = iterator(i);
			int u;
			while ((u = ii->next()) != 0)
				// 访问顶点i的一个邻接点
				inDegree[u]++;
		}

		// 把入边数为0的顶点加入栈
		stack<int> stack;
		for (int i = 1; i <= n; i++)
			if (inDegree[i] == 0) {
				stack.push(i);
				Ve[i] = 1;
			}
		
		// 生成拓扑序列
		int j = 0;  // 数组theOrder的索引
		while (!stack.empty())
		{// 从栈中提取顶点
			int nextVertex = stack.top();
			stack.pop();
			// 更新入边数
			vertexIterator *iNextVertex = iterator(nextVertex);
			int u;
			while ((u = iNextVertex->next()) != 0)
			{// 访问顶点nextVertex的一个邻接顶点
				inDegree[u]--;
				if (Ve[nextVertex] + 1 > Ve[u])
					Ve[u] = Ve[nextVertex] + 1;
				if (inDegree[u] == 0)
					stack.push(u);
			}
		}
		for (int i = 1; i <= n; i++) {
			int row = Ve[i];
			int j = 0;
			while (theList[row][j] != 0)
				j++;
			theList[row][j] = i;
		}
	}

	int findPoint()
	{//Floy算法，c存储最短路径长度，kay保存回溯路径
		if (!weighted())
			throw "不是加权图";
		int **c = new int*[n + 1];
		for (int i = 1; i <= n; i++)
			c[i] = new int[n + 1];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				c[i][j] = a[i][j];
				//kay[i][j] = 0;
			}
		for (int i = 1; i <= n; i++)
			c[i][i] = 0;

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (c[i][k] != noEdge && c[k][j] != noEdge &&
						(c[i][j] == noEdge || c[i][j] > c[i][k] + c[k][j]))
					{
						c[i][j] = c[i][k] + c[k][j];
						//kay[i][j] = k;
					}
		int min = INT_MAX;
		int point = 0;
		for (int i = 1; i <= n; i++) {
			int sum = 0;
			for (int j = 1; j <= n; j++)
				sum += c[i][j];
			cout << "点" << i << "到所有点的距离之和为" << sum << endl;
			if (sum < min)
				min = sum, point = i;
		}
		return point;
	}

};
template <class T>
ostream& operator<<(ostream& out, const adjacencyWDigraph<T>& x)
{
	x.output(out); return out;
}
#endif
