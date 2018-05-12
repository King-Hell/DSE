#include"adjacencyWDigraph.h"

using namespace std;


int main() {
	//--------------------测试用代码---------------------------------
	/*int **a = new int*[6];
	a[1] = new int[6] {0, 1, 4, 4, 8, 2};
	a[2] = new int[6] {0, 3, 2, 1, 5, 9};
	a[3] = new int[6] {0, 2, 2, 0, 1, 8};
	a[4] = new int[6] {0, 8, 8, 9, 0, 1};
	a[5] = new int[6] {0, 8, 8, 2, 9, 0};
	adjacencyWDigraph<int> g(7, 0);
	try{
		g.insertEdge(new edge<int>(1, 3, 1));
		g.insertEdge(new edge<int>(2, 4, 1));
		g.insertEdge(new edge<int>(3, 5, 1));
		g.insertEdge(new edge<int>(4, 6, 1));
		g.insertEdge(new edge<int>(3, 7, 1));
		g.insertEdge(new edge<int>(5, 1, 1));
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}*/
	//---------------------------------------------------------------
	//课程安排代码
	int classSum;
	cout << "请输入课程总数" << endl;
	cin >> classSum;
	if (classSum < 1) {
		cout << "课程总数必须大于等于1" << endl;//不合法数据
		system("pause");
		return -1;
	}
	adjacencyWDigraph<int> g(classSum, 0);
	string op;
	int first, second;
	do {
		cout << "请输入一个课程" << endl;
		cin >> second;
		cout << "请输入其先行课程" << endl;
		cin >> first;
		g.insertEdge(new edge<int>(first, second, 1));
		cout << "继续请输入y" << endl;
		cin >> op;
	} while (op == "y" || op == "Y");
	int **list = new int*[classSum+1];
	for (int i = 0; i < classSum+1; i++) {
		list[i] = new int[classSum + 1];
		fill(list[i], list[i] + classSum + 1, 0);
	}
	g.AOV(list);//将课程表存储在list中
	int count = 0;
	for (int i = 1; i <= classSum; i++) {
		for (int j = 0; j < classSum+1; j++) {
			if (list[i][j] != 0) {
				cout << "第" << i << "学期：" << list[i][j] << endl;
				count = i;
			}
		}
	}
	cout << "一共需要" << count<< "学期"<<endl;
	cout << endl << endl << endl;

	//医院选址代码
	/*
	cout << "请输入节点数" << endl;
	int pointSum;
	cin >> pointSum;
	if (pointSum < 1) {
		cout << "节点数必须大于0" << endl;
		system("pause");
		return -1;
	}
	for (int i = 1; i <= pointSum; i++) {
		cout << "请输入节点" << i << "到其他各点的距离，空格分隔，到自身距离输入为0" << endl;
		for (int j = 1; j <= pointSum; j++) {
			int dis;
			cin >> dis;
			g.insertEdge(new edge<int>(i, j, dis));
		}
	}
	cout << "医院应建在"<<g.findPoint() << endl;
	*/
	
	system("pause");
	return 0;
}