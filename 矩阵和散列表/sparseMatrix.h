// 稀疏矩阵
#ifndef sparseMatrix_
#define sparseMatrix_

#include <iostream>
#include "matrixTerm.h"
#include "extendedArrayList.h"
#include "myExceptions.h"

template<class T>
class sparseMatrix
{
	template<class T>
	friend ostream& operator<<(ostream&, sparseMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, sparseMatrix<T>&);
public:
	sparseMatrix() {}//无参构造方法
	sparseMatrix(int rows, int cols) :rows(rows), cols(cols) {}//有参构造方法
	sparseMatrix(int rows, int cols, int size) :rows(rows), cols(cols) { terms.reSet(size); }//有参构造方法
	~sparseMatrix() {}//析构方法
	sparseMatrix(sparseMatrix<T> &x) :rows(x.rows), cols(x.cols) { terms = x.terms; }//复制构造方法
	sparseMatrix<T>* transpose();//矩阵转置
	sparseMatrix<T>* operator+(sparseMatrix<T> &right);//矩阵加法
	void insert(int row, int col,int value,int index) {
		matrixTerm<int> mTerm(row,col,value);
		terms.set(index, mTerm);
	}
private:
	int rows;
	int cols;
	arrayList<matrixTerm<T>> terms;
};

template<class T>
ostream& operator<<(ostream& out, sparseMatrix<T>& x)
{// 输出矩阵
	//先输出行列数，然后输出非0元素个数，再逐行输出矩阵
	out << "rows = " << x.rows << " columns = " << x.cols << endl;//输出行列数
	out << "nonzero terms = " << x.terms.size() << endl;//输出非0元素数
	arrayList<matrixTerm<int> >::iterator it = x.terms.begin();//声明迭代器
	for (int i = 1; i <= x.rows; i++) {
		for (int j = 1; j <= x.cols; j++) {
			if ((*it).row == i && (*it).col == j&&it != x.terms.end()) {//若该位置元素不为0，则输出
				cout << (*it).value << "\t";
				it++;
			}
			else
				cout << "0\t";//否则打印0
		}
		cout << endl;
	}
	return out;
}
template<class T>
istream& operator>>(istream& in, sparseMatrix<T>& x)
{//输入矩阵
	int numberOfTerms;
	cout << "Enter number of rows, columns, and number of terms" << endl;
	in >> x.rows >> x.cols >> numberOfTerms;
	//初始化terms大小
	x.terms.reSet(numberOfTerms);

	//输入元素
	matrixTerm<int> mTerm;
	for (int i = 0; i < numberOfTerms; i++){//每次重设mTerm的属性，作为set方法的参数拷贝进去
		cout << "Enter row, column, and value of term " << (i + 1) << endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;
		x.terms.set(i, mTerm);
	}

	return in;
}
template<class T>
sparseMatrix<T>* sparseMatrix<T>::transpose()
{//将*this转置，并返回指针
	sparseMatrix<T> *b = new sparseMatrix(cols, rows);//初始化b，使b的行等于*this的列，b的列等于*this的行
	b->terms.reSet(terms.size());
	// 初始化
	int* colSize = new int[cols + 1];//用来存放原矩阵每一列元素的数量
	int* rowNext = new int[cols + 1];//用来存放转置矩阵n行之前元素的个数

	// 寻找*this中每一列的项的数目
	for (int i = 1; i <= cols; i++) // 初始化
		colSize[i] = 0;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin(); i != terms.end(); i++)
		colSize[(*i).col]++;//确定每一列元素的个数
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];//计算转置矩阵第n行起始元素的位置

	//复制元素
	matrixTerm<T> mTerm;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin(); i != terms.end(); i++) {
		int j = rowNext[(*i).col]++;//j用来确定i中元素在转置矩阵中数组的下标
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b->terms.set(j, mTerm);
	}
	return b;
}

template<class T>
sparseMatrix<T>* sparseMatrix<T>::operator+(sparseMatrix<T> &right) {
	//计算c=*this+right，返回c指针
	if (rows != right.rows || cols != right.cols)//当两矩阵行列不相容时，无法相加
		throw matrixSizeMismatch();
	sparseMatrix<T> *c = new sparseMatrix<T>(rows, cols);
	//定义迭代器，便于矩阵相加操作，i为*this的迭代器，j为right的迭代器
	arrayList<matrixTerm<T> >::iterator i = terms.begin();
	arrayList<matrixTerm<T> >::iterator j = right.terms.begin();
	arrayList<matrixTerm<T> >::iterator iEnd = terms.end();
	arrayList<matrixTerm<T> >::iterator  jEnd = right.terms.end();
	int cSize = 0;
	while (i != iEnd&&j != jEnd) {
		//计算*i和*j的行列数
		int iIndex = (*i).row * cols + (*i).col;
		int jIndex = (*j).row * cols + (*j).col;
		if (iIndex < jIndex) {//当i在前时，插入*i
			c->terms.insert(cSize++, *i);
			i++;
		}
		else if (iIndex > jIndex) {//当j在前时，插入*j
			c->terms.insert(cSize++, *j);
			j++;
		}
		else {//当i与j在同一位置，若加和不为0，则插入两者和
			T sum = (*i).value + (*j).value;
			if (sum != 0) {
				matrixTerm<T> m((*i).row, (*i).col, sum);
				c->terms.insert(cSize++, m);
			}
			i++;
			j++;
		}
	}
	//将剩余矩阵元素复制
	for (; i != iEnd; i++)
		c->terms.insert(cSize++, *i);
	for (; j != jEnd; j++)
		c->terms.insert(cSize++, *j);
	return c;
}
#endif
