// test array based sparse matrix class

#include <iostream>
#include "sparseMatrix.h"

int main(){
	sparseMatrix<int> a, b;

	// test input and output
   /* cin >> a;
	cout << "Matrix a is" << endl << a;
	cin >> b;
	cout << "Matrix b is" << endl << b;*/

	sparseMatrix<int> e(2, 5, 4);
	e.insert(1, 1, 1, 0);
	e.insert(1, 3, 4, 1);
	e.insert(1, 4, 2, 2);
	e.insert(2, 3, 5, 3);
	cout << "Matrix e is" << endl << e;
	sparseMatrix<int> f(2, 5, 5);
	f.insert(1, 2, 1, 0);
	f.insert(1, 3, 2, 1);
	f.insert(1, 5, 2, 2);
	f.insert(2, 2, 4, 3);
	f.insert(2, 3, 7, 4);
	cout << "Matrix f is" << endl << f;
	// test transpose
	sparseMatrix<int> *c;
	c = f.transpose();
	cout << "The transpose of e is" << endl << *c;

	// test add
	sparseMatrix<int> *d;
	d = e + f;
	//d = a + b;
	cout << "The sum of e and f is" << endl << *d;
	system("pause");
	return 0;
}
