#include"adjacencyWDigraph.h"

using namespace std;


int main() {
	//--------------------�����ô���---------------------------------
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
	//�γ̰��Ŵ���
	int classSum;
	cout << "������γ�����" << endl;
	cin >> classSum;
	if (classSum < 1) {
		cout << "�γ�����������ڵ���1" << endl;//���Ϸ�����
		system("pause");
		return -1;
	}
	adjacencyWDigraph<int> g(classSum, 0);
	string op;
	int first, second;
	do {
		cout << "������һ���γ�" << endl;
		cin >> second;
		cout << "�����������пγ�" << endl;
		cin >> first;
		g.insertEdge(new edge<int>(first, second, 1));
		cout << "����������y" << endl;
		cin >> op;
	} while (op == "y" || op == "Y");
	int **list = new int*[classSum+1];
	for (int i = 0; i < classSum+1; i++) {
		list[i] = new int[classSum + 1];
		fill(list[i], list[i] + classSum + 1, 0);
	}
	g.AOV(list);//���γ̱�洢��list��
	int count = 0;
	for (int i = 1; i <= classSum; i++) {
		for (int j = 0; j < classSum+1; j++) {
			if (list[i][j] != 0) {
				cout << "��" << i << "ѧ�ڣ�" << list[i][j] << endl;
				count = i;
			}
		}
	}
	cout << "һ����Ҫ" << count<< "ѧ��"<<endl;
	cout << endl << endl << endl;

	//ҽԺѡַ����
	/*
	cout << "������ڵ���" << endl;
	int pointSum;
	cin >> pointSum;
	if (pointSum < 1) {
		cout << "�ڵ����������0" << endl;
		system("pause");
		return -1;
	}
	for (int i = 1; i <= pointSum; i++) {
		cout << "������ڵ�" << i << "����������ľ��룬�ո�ָ����������������Ϊ0" << endl;
		for (int j = 1; j <= pointSum; j++) {
			int dis;
			cin >> dis;
			g.insertEdge(new edge<int>(i, j, dis));
		}
	}
	cout << "ҽԺӦ����"<<g.findPoint() << endl;
	*/
	
	system("pause");
	return 0;
}