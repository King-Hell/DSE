//����ʵ�ֵ�ջ
#ifndef arrayStack_
#define arrayStack_

#include "stack.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>


template<class T>
class arrayStack : public stack<T>{
   public:
      arrayStack(int initialCapacity = 10);//���췽��
      ~arrayStack() {delete [] stack;}//��������
      bool empty() const {return stackTop == -1;}//����ջ�Ƿ�Ϊ��
      int size() const{return stackTop + 1;}//���ص�ǰջ��С
      T& top(){//����ջ��Ԫ��
            if (stackTop == -1)
               throw stackEmpty();
            return stack[stackTop];
         }
      void pop(){//ɾ��ջ��Ԫ��
              if (stackTop == -1)
                 throw stackEmpty();
              stack[stackTop--].~T();  
           }
      void push(const T& theElement);
   private:
      int stackTop;         // ջ���±�
      int arrayLength;      // ջ����
      T *stack;           // ���ջ����
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{// ���췽��
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity;
   stack = new T[arrayLength];
   stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement){// ����Ԫ��ѹ��ջ��
   if (stackTop == arrayLength - 1){//�ռ䲻�㣬����ӱ�
         changeLength1D(stack, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }
   //ѹջ����
   stack[++stackTop] = theElement;
}
#endif
