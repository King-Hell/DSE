// ϡ�����
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
	sparseMatrix() {}//�޲ι��췽��
	sparseMatrix(int rows, int cols) :rows(rows), cols(cols) {}//�вι��췽��
	sparseMatrix(int rows, int cols, int size) :rows(rows), cols(cols) { terms.reSet(size); }//�вι��췽��
	~sparseMatrix() {}//��������
	sparseMatrix(sparseMatrix<T> &x) :rows(x.rows), cols(x.cols) { terms = x.terms; }//���ƹ��췽��
	sparseMatrix<T>* transpose();//����ת��
	sparseMatrix<T>* operator+(sparseMatrix<T> &right);//����ӷ�
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
{// �������
	//�������������Ȼ�������0Ԫ�ظ������������������
	out << "rows = " << x.rows << " columns = " << x.cols << endl;//���������
	out << "nonzero terms = " << x.terms.size() << endl;//�����0Ԫ����
	arrayList<matrixTerm<int> >::iterator it = x.terms.begin();//����������
	for (int i = 1; i <= x.rows; i++) {
		for (int j = 1; j <= x.cols; j++) {
			if ((*it).row == i && (*it).col == j&&it != x.terms.end()) {//����λ��Ԫ�ز�Ϊ0�������
				cout << (*it).value << "\t";
				it++;
			}
			else
				cout << "0\t";//�����ӡ0
		}
		cout << endl;
	}
	return out;
}
template<class T>
istream& operator>>(istream& in, sparseMatrix<T>& x)
{//�������
	int numberOfTerms;
	cout << "Enter number of rows, columns, and number of terms" << endl;
	in >> x.rows >> x.cols >> numberOfTerms;
	//��ʼ��terms��С
	x.terms.reSet(numberOfTerms);

	//����Ԫ��
	matrixTerm<int> mTerm;
	for (int i = 0; i < numberOfTerms; i++){//ÿ������mTerm�����ԣ���Ϊset�����Ĳ���������ȥ
		cout << "Enter row, column, and value of term " << (i + 1) << endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;
		x.terms.set(i, mTerm);
	}

	return in;
}
template<class T>
sparseMatrix<T>* sparseMatrix<T>::transpose()
{//��*thisת�ã�������ָ��
	sparseMatrix<T> *b = new sparseMatrix(cols, rows);//��ʼ��b��ʹb���е���*this���У�b���е���*this����
	b->terms.reSet(terms.size());
	// ��ʼ��
	int* colSize = new int[cols + 1];//�������ԭ����ÿһ��Ԫ�ص�����
	int* rowNext = new int[cols + 1];//�������ת�þ���n��֮ǰԪ�صĸ���

	// Ѱ��*this��ÿһ�е������Ŀ
	for (int i = 1; i <= cols; i++) // ��ʼ��
		colSize[i] = 0;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin(); i != terms.end(); i++)
		colSize[(*i).col]++;//ȷ��ÿһ��Ԫ�صĸ���
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];//����ת�þ����n����ʼԪ�ص�λ��

	//����Ԫ��
	matrixTerm<T> mTerm;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin(); i != terms.end(); i++) {
		int j = rowNext[(*i).col]++;//j����ȷ��i��Ԫ����ת�þ�����������±�
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b->terms.set(j, mTerm);
	}
	return b;
}

template<class T>
sparseMatrix<T>* sparseMatrix<T>::operator+(sparseMatrix<T> &right) {
	//����c=*this+right������cָ��
	if (rows != right.rows || cols != right.cols)//�����������в�����ʱ���޷����
		throw matrixSizeMismatch();
	sparseMatrix<T> *c = new sparseMatrix<T>(rows, cols);
	//��������������ھ�����Ӳ�����iΪ*this�ĵ�������jΪright�ĵ�����
	arrayList<matrixTerm<T> >::iterator i = terms.begin();
	arrayList<matrixTerm<T> >::iterator j = right.terms.begin();
	arrayList<matrixTerm<T> >::iterator iEnd = terms.end();
	arrayList<matrixTerm<T> >::iterator  jEnd = right.terms.end();
	int cSize = 0;
	while (i != iEnd&&j != jEnd) {
		//����*i��*j��������
		int iIndex = (*i).row * cols + (*i).col;
		int jIndex = (*j).row * cols + (*j).col;
		if (iIndex < jIndex) {//��i��ǰʱ������*i
			c->terms.insert(cSize++, *i);
			i++;
		}
		else if (iIndex > jIndex) {//��j��ǰʱ������*j
			c->terms.insert(cSize++, *j);
			j++;
		}
		else {//��i��j��ͬһλ�ã����ӺͲ�Ϊ0����������ߺ�
			T sum = (*i).value + (*j).value;
			if (sum != 0) {
				matrixTerm<T> m((*i).row, (*i).col, sum);
				c->terms.insert(cSize++, m);
			}
			i++;
			j++;
		}
	}
	//��ʣ�����Ԫ�ظ���
	for (; i != iEnd; i++)
		c->terms.insert(cSize++, *i);
	for (; j != jEnd; j++)
		c->terms.insert(cSize++, *j);
	return c;
}
#endif
