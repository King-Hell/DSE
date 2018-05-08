#include"adjacencyWDigraph.h"

using namespace std;


int main() {
	int **a = new int*[6];
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
	}
	
	int **list = new int*[8];
	for (int i = 0; i < 8; i++) {
		list[i] = new int[8];
		fill(list[i], list[i] + 8, 0);
	}
	g.AOV(list);
	int count = 0;
	for (int i = 1; i <= 7; i++) {
		for (int j = 0; j < 8; j++) {
			if (list[i][j] != 0) {
				cout << "第" << i << "学期：" << list[i][j] << endl;
				count = i;
			}
		}
	}
	cout << "一共需要" << count<< "学期"<<endl;
	cout << endl << endl << endl;

	adjacencyWDigraph<int> h(5, 0);
	h.initByArray(a);
	cout << "医院应建在"<<h.findPoint() << endl;
	system("pause");
	return 0;
}