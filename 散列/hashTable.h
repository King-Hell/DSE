//线性开型寻址
#ifndef hashTable_
#define hashTable_

#include <iostream>
#include "myExceptions.h"
#include "mHash.h"

using namespace std;

template<class K, class E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);//构造方法
	~hashTable() { delete[] table; }//析构方法

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;//查找
	void insert(const pair<const K, E>&);//插入
	void output(ostream& out) const;//输出

protected:
	int search(const K&) const;
	pair<const K, E>** table;  // hash表
	mHash<K> hash;              //hash转换
	int dSize;                 // 字典数
	int divisor;               // 桶数
};

template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = NULL;
}

template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const {
	//有三种情况，1、关键字对应的桶为空，可以直接插入
	//2、关键字对应的桶不为空，则不断向后搜索，直到可以插入
	//3、表已满，表示不可插入
	int i = (int)hash(theKey) % divisor;  //将当前theKey转化为整数，找到关键字对应的桶
	int j = i;    // 初始化遍历器开始值
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)//先查找关键字对应的桶，若为空或关键字已存在，则返回下标
			return j;
		j = (j + 1) % divisor;  // 否则检测下一个桶是否为空
	} while (j != i);          // 当所有桶均检测一遍时，表已满

	return j;  // 返回表已满时的下标
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const {//查找
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;           // 没有匹配关键字，返回空
	return table[b];  // 有匹配关键字，返回对应字典
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair){// 插入
	int b = search(thePair.first);
	// 查找是否已存在关键字
	if (table[b] == NULL) {
		//若关键字不存在且可以插入
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else {
		if (table[b]->first == thePair.first)
		{//若关键字已存在
			table[b]->second = thePair.second;
		}
		else // 若hash表已满
			throw hashTableFull();
	}
}

template<class K, class E>
void hashTable<K, E>::output(ostream& out) const{//输出
	for (int i = 0; i < divisor; i++)
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " "
			<< table[i]->second << endl;
}

// 重载输出操作符
template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out); return out;
}

#endif
