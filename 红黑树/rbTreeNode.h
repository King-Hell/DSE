//红黑树节点定义
#ifndef rbTreeNode_
#define rbTreeNode_

#define RED=0
#define BLACK=1

using namespace std;

template <class T>
struct rbTreeNode{
	T element;//数据域
	rbTreeNode<T> *leftChild,*rightChild;  // 左右孩子
	rbTreeNode<T> *parent;//父亲
	bool color;//颜色，0为红色，1为黑色

	rbTreeNode() { 
		//无参构造方法
		leftChild = rightChild = NULL; color = BLACK; 
	}

	rbTreeNode(const T& theElement){
		//指定数据构造方法
		element = theElement;
		leftChild = rightChild = NULL;
	}

	rbTreeNode(const T& theElement,bool theColor) {
		//指定数据与颜色构造方法
		element = theElement;
		leftChild = rightChild = NULL;
		color = theColor;
	}

};

#endif
