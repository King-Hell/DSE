
//�ڽӾ����Ȩ����ͼ

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
	int n;//����        
	int e;//����   
	T **a;//�ڽӾ���洢           
	T noEdge;

public:
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0) {
		// ���췽��
		if (numberOfVertices < 0)
			throw "������������ڵ���0";
		n = numberOfVertices;
		e = 0;
		noEdge = theNoEdge;
		a = new int*[n + 1];
		for (int i = 0; i < n + 1; i++) {
			a[i] = new int[n + 1];
		}
		for (int i = 1; i <= n; i++)
			// ��ʼ���ڽӾ���
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
	{//�����Ƿ����i��j�ıߣ����ڷ���true�������ڷ���false
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
	{//����ߣ�����Ѵ��ڸ���Ȩֵ
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();

		if (a[v1][v2] == noEdge)
			e++;
		a[v1][v2] = theEdge->weight();
		dfs(v1);
		if (swi)
			throw exception("�бջ�������");
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
	{// ɾ��i��j�ı�
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			e--;
		}
	}

	void checkVertex(int theVertex) const
	{//�����Ƿ�Ϸ�
		if (theVertex < 1 || theVertex > n)
			throw "���Ϸ����㣡����";
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
		{// ������һ���ڽӽڵ�,û���򷵻�0
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
	{// ����theVertex�ĵ�����
		checkVertex(theVertex);
		return new vertexIterator(a[theVertex], noEdge, n);
	}


	void output(ostream& out) const
	{// ����ڽӾ���
		for (int i = 1; i <= n; i++)
		{
			copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, "  "));
			out << endl;
		}
	}


	void AOV(int **theList) {
		//����false�����ҽ�������ͼû����������
		//�������һ���������У����丳��theOrder[0:n-1]
		if (!directed())//ȷ���Ƿ�Ϊ����ͼ
			throw "��������ͼ";

		int n = numberOfVertices();

		// �������
		int *inDegree = new int[n + 1];
		fill(inDegree + 1, inDegree + n + 1, 0);
		int *Ve = new int[n + 1];
		fill(Ve+1, Ve + n + 1, 0);
		for (int i = 1; i <= n; i++)
		{// ����i�ĳ���
			vertexIterator *ii = iterator(i);
			int u;
			while ((u = ii->next()) != 0)
				// ���ʶ���i��һ���ڽӵ�
				inDegree[u]++;
		}

		// �������Ϊ0�Ķ������ջ
		stack<int> stack;
		for (int i = 1; i <= n; i++)
			if (inDegree[i] == 0) {
				stack.push(i);
				Ve[i] = 1;
			}
		
		// ������������
		int j = 0;  // ����theOrder������
		while (!stack.empty())
		{// ��ջ����ȡ����
			int nextVertex = stack.top();
			stack.pop();
			// ���������
			vertexIterator *iNextVertex = iterator(nextVertex);
			int u;
			while ((u = iNextVertex->next()) != 0)
			{// ���ʶ���nextVertex��һ���ڽӶ���
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
	{//Floy�㷨��c�洢���·�����ȣ�kay�������·��
		if (!weighted())
			throw "���Ǽ�Ȩͼ";
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
			cout << "��" << i << "�����е�ľ���֮��Ϊ" << sum << endl;
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
