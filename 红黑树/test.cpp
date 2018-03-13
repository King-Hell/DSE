//ºìºÚÊ÷²âÊÔ

#include"redBlackTree.h"

int main() {

	redBlackTree<int, char> t;
	//²âÊÔ²åÈë
	t.insert(pair<int, char>(70, 'e'));
	t.insert(pair<int, char>(60, 'f'));
	t.insert(pair<int, char>(65, 'g'));
	t.insert(pair<int, char>(62, 'h'));
	

	//²âÊÔÉ¾³ı
	t.erase(90);
	t.erase(80);
	t.erase(70);
	system("pause");
	return 0;
}