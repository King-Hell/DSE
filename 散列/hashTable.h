//���Կ���Ѱַ
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
	hashTable(int theDivisor = 11);//���췽��
	~hashTable() { delete[] table; }//��������

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;//����
	void insert(const pair<const K, E>&);//����
	void output(ostream& out) const;//���

protected:
	int search(const K&) const;
	pair<const K, E>** table;  // hash��
	mHash<K> hash;              //hashת��
	int dSize;                 // �ֵ���
	int divisor;               // Ͱ��
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
	//�����������1���ؼ��ֶ�Ӧ��ͰΪ�գ�����ֱ�Ӳ���
	//2���ؼ��ֶ�Ӧ��Ͱ��Ϊ�գ��򲻶����������ֱ�����Բ���
	//3������������ʾ���ɲ���
	int i = (int)hash(theKey) % divisor;  //����ǰtheKeyת��Ϊ�������ҵ��ؼ��ֶ�Ӧ��Ͱ
	int j = i;    // ��ʼ����������ʼֵ
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)//�Ȳ��ҹؼ��ֶ�Ӧ��Ͱ����Ϊ�ջ�ؼ����Ѵ��ڣ��򷵻��±�
			return j;
		j = (j + 1) % divisor;  // ��������һ��Ͱ�Ƿ�Ϊ��
	} while (j != i);          // ������Ͱ�����һ��ʱ��������

	return j;  // ���ر�����ʱ���±�
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const {//����
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;           // û��ƥ��ؼ��֣����ؿ�
	return table[b];  // ��ƥ��ؼ��֣����ض�Ӧ�ֵ�
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair){// ����
	int b = search(thePair.first);
	// �����Ƿ��Ѵ��ڹؼ���
	if (table[b] == NULL) {
		//���ؼ��ֲ������ҿ��Բ���
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else {
		if (table[b]->first == thePair.first)
		{//���ؼ����Ѵ���
			table[b]->second = thePair.second;
		}
		else // ��hash������
			throw hashTableFull();
	}
}

template<class K, class E>
void hashTable<K, E>::output(ostream& out) const{//���
	for (int i = 0; i < divisor; i++)
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " "
			<< table[i]->second << endl;
}

// �������������
template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out); return out;
}

#endif
