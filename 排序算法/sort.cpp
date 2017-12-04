#include"Sorts.h"
int main() {
	//Test selectionSort
	cout << "Test selectionSort" << endl;
	int a[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::selectionSort(a, 10);
	//Test bubbleSort
	cout << "Test bubbleSort" << endl;
	int b[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::bubbleSort(b, 10);
	//Test insertSort
	cout << "Test insertSort" << endl;
	int c[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::insertSort(c, 10);
	//Test radixSort
	cout << "Test radixSort" << endl;
	int d[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::radixSort(d, 10);
	//Test quickSort
	cout << "Test quickSort" << endl;
	int e[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::quickSort(e, 10);
	//Test mergeSort
	cout << "Test mergeSort" << endl;
	int f[10] = { 34,643,1,244,88,97,677,45,78,99 };
	sorts::mergeSort(f, 10);
	system("pause");
	return 0;
}