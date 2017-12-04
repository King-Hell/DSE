//链表散列
//链表散列比较简单，只需调用sortedChain已定义的各种方法即可
#ifndef hashChains_
#define hashChains_

#include <iostream>
#include "dictionary.h"
#include "sortedChain.h"
#include "mHash.h"

using namespace std;

template<class K, class E>
class hashChains : public dictionary<K,E>
{
   public:
      hashChains(int theDivisor = 11){//构造方法
         divisor = theDivisor;
         dSize = 0;
         table = new sortedChain<K,E> [divisor];//初始化桶
      }

      ~hashChains(){delete [] table;}//析构方法

      bool empty() const {return dSize == 0;}
      int size() const {return dSize;}

      pair<const K, E>* find(const K& theKey) const//查找
         {return table[hash(theKey) % divisor].find(theKey);}

      void insert(const pair<const K, E>& thePair) {//插入
         int homeBucket = (int) hash(thePair.first) % divisor;
         int homeSize = table[homeBucket].size();
         table[homeBucket].insert(thePair);
         if (table[homeBucket].size() > homeSize)//插入成功
            dSize++;
      }

      void erase(const K& theKey)
         {table[hash(theKey) % divisor].erase(theKey);}

      void output(ostream& out) const {//输出
         for (int i = 0; i < divisor; i++)
            if (table[i].size() == 0)
               cout << "NULL" << endl;
            else
               cout << table[i] ;
      }

   protected:
      sortedChain<K, E>* table;  // hash表
      mHash<K> hash;              // hash转换
      int dSize;                 // 元素个数
      int divisor;               // 桶数
};

//重载输出操作符
template <class K, class E>
ostream& operator<<(ostream& out, const hashChains<K,E>& x)
   {x.output(out); return out;}

#endif
