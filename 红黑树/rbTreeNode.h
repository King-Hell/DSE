//������ڵ㶨��
#ifndef rbTreeNode_
#define rbTreeNode_

#define RED=0
#define BLACK=1

using namespace std;

template <class T>
struct rbTreeNode{
	T element;//������
	rbTreeNode<T> *leftChild,*rightChild;  // ���Һ���
	rbTreeNode<T> *parent;//����
	bool color;//��ɫ��0Ϊ��ɫ��1Ϊ��ɫ

	rbTreeNode() { 
		//�޲ι��췽��
		leftChild = rightChild = NULL; color = BLACK; 
	}

	rbTreeNode(const T& theElement){
		//ָ�����ݹ��췽��
		element = theElement;
		leftChild = rightChild = NULL;
	}

	rbTreeNode(const T& theElement,bool theColor) {
		//ָ����������ɫ���췽��
		element = theElement;
		leftChild = rightChild = NULL;
		color = theColor;
	}

};

#endif
