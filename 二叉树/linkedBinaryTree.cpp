// test linked binary tree class

#include <iostream>
#include "linkedBinaryTree.h"
using namespace std;

int main(void)
{
	cout << "Test linkedBinaryTree" << endl;
	linkedBinaryTree<int> a, x, y, z;
	y.makeTree(1, a, a);
	z.makeTree(2, a, a);
	x.makeTree(3, y, z);
	y.makeTree(4, x, a);
	cout << "Number of nodes = ";
	cout << y.size() << endl;
	cout << "height = ";
	cout << y.height() << endl;
	cout << "Preorder sequence is ";
	y.preOrderOutput();
	cout << "Inorder sequence is ";
	y.inOrderOutput();
	cout << "Postorder sequence is ";
	y.postOrderOutput();
	cout << "Level order sequence is ";
	y.levelOrderOutput();
	cout << "=====================================" << endl;
	cout << "Test make binaryTree by preorder and inorder" << endl;
	linkedBinaryTree<char> t;
	char pre[8] = { 'A','B','D','H','E','C','F','G' };
	char in[8] = { 'H','D','B','E','A','F','C','G' };
	t.makeTreebyPre(pre, in, 8);
	cout << "Preorder sequence is ";
	t.preOrderOutput();
	cout << "Inorder sequence is ";
	t.inOrderOutput();
	cout << "Postorder sequence is ";
	t.postOrderOutput();
	cout << "Level order sequence is ";
	t.levelOrderOutput();
	system("pause");
	return 0;
}
