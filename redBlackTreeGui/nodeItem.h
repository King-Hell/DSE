#pragma once
#include<qgraphicsitem.h>
#include"qpen.h"
#define RED 0
#define BLACK 1
class nodeItem {
public:
	nodeItem() {};

	nodeItem(rbTreeNode<pair<const QChar, char>>* node,int x,int y,int level) {
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
			brush.setColor(QColor("red"));
		else
			brush.setColor(QColor("black"));
		brush.setStyle(Qt::SolidPattern);
		ellipse->setBrush(brush);
		scene->addItem(ellipse);
		QGraphicsTextItem *text=new QGraphicsTextItem(node->element.first);
		text->setDefaultTextColor(QColor("white"));
		text->setFont(QFont("Microsoft YaHei UI", 20));
		text->setPos(x+12,y+2);
		scene->addItem(text);
	}

	bool hasLeftChild() {
		return node->leftChild != NULL;
	}
	rbTreeNode<pair<const QChar, char>>* getLeftChild() {
		if (node->leftChild == NULL)
			return NULL;
		return node->leftChild;
	}
	bool hasRightChild() {
		return node->rightChild != NULL;
	}
	rbTreeNode<pair<const QChar, char>>* getRightChild() {
		if (node->rightChild == NULL)
			return NULL;
		return node->rightChild;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getLevel() { return level; }
	bool getColor() { return node->color; };
private:
	int x;
	int y;
	int level;
	rbTreeNode<pair<const QChar, char>>* node;
};