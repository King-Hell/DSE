#pragma once
#include<qgraphicsitem.h>
#include"qpen.h"
#define RED 0
#define BLACK 1
class nodeItem {
public:
	nodeItem() {};

	nodeItem(rbTreeNode<pair<const int, char>>* node,int x,int y,int level) {
		this->x = x;
		this->y = y;
		this->node = node;
		this->level = level;
	}
	~nodeItem() {};

	void paint(QGraphicsScene *scene) {
		QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(x, y, 50, 50);
		ellipse->setPen(Qt::NoPen);
		QBrush brush;
		if (node->color == RED)
			brush.setColor(QColor(255, 0, 0));
		else
			brush.setColor(QColor(255, 255, 255));
		brush.setStyle(Qt::SolidPattern);
		ellipse->setBrush(brush);
		scene->addItem(ellipse);
	}

	bool hasLeftChild() {
		return node->leftChild == NULL;
	}
	rbTreeNode<pair<const int, char>>* getLeftChild() {
		if (node->leftChild == NULL)
			return NULL;
		return node->leftChild;
	}
	bool hasRightChild() {
		return node->rightChild == NULL;
	}
	rbTreeNode<pair<const int, char>>* getRightChild() {
		if (node->rightChild == NULL)
			return NULL;
		return node->rightChild;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getLevel() { return level; }
private:
	int x;
	int y;
	int level;
	rbTreeNode<pair<const int, char>>* node;
};