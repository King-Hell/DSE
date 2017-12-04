// a term in sparseMatrix

#ifndef matrixTerm_
#define matrixTerm_

using namespace std;

template <class T>
struct matrixTerm 
{
   int row,//��
       col;//��
   T value;//ֵ
   matrixTerm() {};
   matrixTerm(int row, int col, T &value) :row(row), col(col), value(value) {};
   operator T() const {return value;}
      // type conversion from matrixTerm to T
};

#endif
