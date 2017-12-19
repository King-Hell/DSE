// Huffman tree

#include <iostream>
#include "minHeap.h"
#include "linkedBinaryTree.h"
#include "huffmanNode.h"

using namespace std;

template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//weightΪÿ�����ŵ�Ȩ�أ�nΪ�����С
	huffmanNode<T> *hNode = new huffmanNode<T>[n + 1];//����һ���������ڵ������
	linkedBinaryTree<int> emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];//��ֵÿ�����ŵ�Ȩ��
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);//����ÿ���ⲿ�ڵ�
	}

	// ����С���Ѳ�����С��
	minHeap<huffmanNode<T> > heap(1);
	heap.initialize(hNode, n);

	//����������С��
	huffmanNode<T> w, x, y;
	linkedBinaryTree<int> *z;
	for (int i = 1; i < n; i++)
	{
		x = heap.top(); heap.pop();//����������С��
		y = heap.top(); heap.pop();

		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);//�ϲ�������С��
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);//������С��
		delete x.tree;
		delete y.tree;
	}
	return heap.top().tree;
}

int main(void)
{
	int a[11];
	int n = 10;
	for (int i = 1; i <= n; i++)
		a[i] = i;
	linkedBinaryTree<int> *x = huffmanTree(a, n);
	cout << "Huffman tree created by 1,2,3......10 is" << endl;
	x->levelOrderOutput();
	system("pause");
	return 0;
}
