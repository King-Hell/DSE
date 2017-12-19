// Huffman tree

#include <iostream>
#include "minHeap.h"
#include "linkedBinaryTree.h"
#include "huffmanNode.h"

using namespace std;

template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//weight为每个符号的权重，n为数组大小
	huffmanNode<T> *hNode = new huffmanNode<T>[n + 1];//构建一个哈夫曼节点的数组
	linkedBinaryTree<int> emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];//赋值每个符号的权重
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);//构造每个外部节点
	}

	// 利用小根堆查找最小树
	minHeap<huffmanNode<T> > heap(1);
	heap.initialize(hNode, n);

	//连接两个最小树
	huffmanNode<T> w, x, y;
	linkedBinaryTree<int> *z;
	for (int i = 1; i < n; i++)
	{
		x = heap.top(); heap.pop();//弹出两个最小树
		y = heap.top(); heap.pop();

		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);//合并两个最小树
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);//构造最小树
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
