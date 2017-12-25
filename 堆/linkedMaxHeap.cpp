// test max heap

#include <iostream>
#include "linkedMaxHeap.h"

using namespace std;
template<class T>
void heapSort(T a[], int size) {
	//堆排序，数组a中所有元素生成一个大根堆，再依次弹出根，即可实现由大到小排序
	linkedMaxHeap<T> h;
	for (int i = 0; i < size; i++)
		h.push(a[i]);
	for (int i = 0; i < size; i++) {
		a[i] = h.top();
		h.pop();
	}
}
int main(void)
{
	cout << "test constructor and push" << endl;
	linkedMaxHeap<int> h;
	h.push(10);
	h.push(20);
	h.push(5);
	h.push(15);
	h.push(30);
	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h;

	cout << endl << "test top and pop" << endl;
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "The max element is " << h.top() << endl;
	h.pop();
	//cout << "Heap size is " << h.size() << endl;
	//cout << "Elements in array order are" << endl;
	//cout << h << endl;

	cout << endl << "test initialize" << endl;
	int z[5] = {0,3,5,6,7};
	h.initialize(z, 5);
	cout << "Elements in array order are" << endl;
	cout << h ;

	cout << endl << "test heapSort" << endl;
	int a[6] = { 24,234,12,43,2,24 };
	for (int i = 0; i < 6; i++)
		cout << a[i] << "  ";
	cout << endl;
	heapSort(a, 6);
	for (int i = 0; i < 6; i++)
		cout << a[i] << "  ";
	cout << endl;
	cout << endl << "test cin" << endl;
	linkedMaxHeap<int> c;
	cin >> c;
	cout << c;
	system("pause");
	return 0;
}
