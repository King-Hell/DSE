//红黑树节点定义
#ifndef rbTreeNode_
#define rbTreeNode_

#define RED 0
#define BLACK 1

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
		parent = NULL;
	}

	rbTreeNode(const T& theElement):element(theElement){
		//指定数据构造方法
		leftChild = rightChild = NULL;
		parent = NULL;
	}

	rbTreeNode(const T& theElement, bool theColor, rbTreeNode<T>* theParent=NULL) :element(theElement) {
		//指定数据、颜色与父节点构造方法
		leftChild = rightChild = NULL;
		color = theColor;
		parent = theParent;
	}

	void setLeftChild(rbTreeNode<T>* leftChild) {
		if (leftChild != NULL) {
			this->leftChild = leftChild;
			leftChild->parent = this;
		}
	}

	void setRightChild(rbTreeNode<T>* rightChild) {
		if (rightChild != NULL) {
			this->rightChild = rightChild;
			rightChild->parent = this;
		}
	}
};

#endif
