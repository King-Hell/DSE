//数组实现的栈
#ifndef arrayStack_
#define arrayStack_

#include "stack.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>


template<class T>
class arrayStack : public stack<T>{
   public:
      arrayStack(int initialCapacity = 10);//构造方法
      ~arrayStack() {delete [] stack;}//析构方法
      bool empty() const {return stackTop == -1;}//返回栈是否为空
      int size() const{return stackTop + 1;}//返回当前栈大小
      T& top(){//返回栈顶元素
            if (stackTop == -1)
               throw stackEmpty();
            return stack[stackTop];
         }
      void pop(){//删除栈顶元素
              if (stackTop == -1)
                 throw stackEmpty();
              stack[stackTop--].~T();  
           }
      void push(const T& theElement);
   private:
      int stackTop;         // 栈顶下标
      int arrayLength;      // 栈容量
      T *stack;           // 存放栈数组
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{// 构造方法
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
void arrayStack<T>::push(const T& theElement){// 将新元素压入栈顶
   if (stackTop == arrayLength - 1){//空间不足，数组加倍
         changeLength1D(stack, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }
   //压栈操作
   stack[++stackTop] = theElement;
}
#endif
