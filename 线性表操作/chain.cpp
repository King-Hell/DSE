#include"chain.h"
int main() {
	chain<int> a;
	//²âÊÔÊäÈë
	cout << "²âÊÔÊäÈë" << endl;
	cin >> a;
	cout << a<<endl;
	//²âÊÔ²åÈë
	cout << "²âÊÔ²åÈë" << endl;
	chain<int> b;
	b.insert(1);
	b.insert(2);
	b.insert(3);
	b.insert(4);
	cout << "b Êä³öÓ¦Îª4 3 2 1" << endl << b << endl;
	//²âÊÔÉ¾³ı
	cout << "²âÊÔÉ¾³ı" << endl;
	b.erase(2);
	b.erase(4);
	cout << "b Êä³öÓ¦Îª3 1" << endl<<b<<endl;
	//²âÊÔËÑË÷
	cout << "²âÊÔËÑË÷" << endl;
	cout << "Êä³öÓ¦Îª0 -1" << endl;
	cout<<b.indexOf(3)<<" ";
	cout << b.indexOf(2) << endl;
	//²âÊÔ·´ĞòÊä³ö
	cout << "²âÊÔ·´ĞòÊä³ö" << endl;
	a.inverse();
	//²âÊÔºÏ²¢
	cout << "²âÊÔºÏ²¢" << endl;
	chain<int> d;
	chain<int> e;
	d.insert(3);
	d.insert(1);
	e.insert(4);
	e.insert(2);
	chain<int>  c;
	c.merge(d, e);
	cout << "Êä³öÓ¦Îª1 2 3 4" << endl;
	cout << c << endl;
	system("pause");
	return 0;
}