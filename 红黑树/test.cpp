//���������

#include"redBlackTree.h"

int main() {

	redBlackTree<int, char> t;
	//���Բ���
	t.insert(pair<int, char>(70, 'e'));
	t.insert(pair<int, char>(60, 'f'));
	t.insert(pair<int, char>(65, 'g'));
	t.insert(pair<int, char>(62, 'h'));
	system("pause");
	return 0;
}