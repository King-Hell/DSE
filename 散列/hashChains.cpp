//// test hash table class
//#include <iostream>
//#include "hashchains.h"
//#include <ctime>
//#include <cstdlib>
//
//using namespace std;
//
//int main()
//{
//	hashChains<int, int> z(961);
//	pair<int, int> p;
//
//	srand((unsigned)time(NULL));
//	// test insert
//	for (int i = 0; z.size() < 500; i++) {
//		p.first = rand() % 1000;
//		p.second = rand() % 100;
//		z.insert(p);
//	}
//	cout << "the dictionary is " << endl << z << endl;
//	cout << "its size is " << z.size() << endl;
//
//	// test find
//	cout << "--------------------------" << endl;
//	p.first = 2; p.second = 10;
//	z.insert(p);
//	p.first = 10; p.second = 50;
//	z.insert(p);
//	p.first = 24; p.second = 120;
//	z.insert(p);
//	p.first = 32; p.second = 160;
//	z.insert(p);
//	p.first = 3; p.second = 15;
//	z.insert(p);
//	p.first = 12; p.second = 60;
//	z.insert(p);
//	cout << "element associated with 2 is " << z.find(2)->second << endl;
//	cout << "element associated with 10 is " << z.find(10)->second << endl;
//	cout << "element associated with 12 is " << z.find(12)->second << endl;
//	cout << "element associated with 32 is " << z.find(32)->second << endl;
//	system("pause");
//	return 0;
//}
