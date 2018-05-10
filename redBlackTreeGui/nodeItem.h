#pragma once
#include<qgraphicsitem.h>
#include"qpen.h"
#define RED 0
#define BLACK 1
template<class K,class E>
class nodeItem {
public:
	nodeItem() {};

	nodeItem(rbTreeNode<pair<const K, E>>* node,int x,int y,int level) {
		//传入参数：节点，横坐标，纵坐标，层次
		this->x = x;
		this->y = y;
		this->node = node;
		this->level = level;
	}

	void paint(QGraphicsScene *scene) //绘制nodeItem方法
	{
		QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(x, y, 50, 50);//横坐标x，纵坐标y，大小50*50
		ellipse->setPen(Qt::NoPen);
		QBrush brush;//设定画刷颜色、风格
		if (node->color == RED)
			brush.setColor(QColor("red"));
		else
			brush.setColor(QColor("black"));
		brush.setStyle(Qt::SolidPattern);
		ellipse->setBrush(brush);
		scene->addItem(ellipse);//绘制图像

		QGraphicsTextItem *text=new QGraphicsTextItem(node->element.first);
		text->setDefaultTextColor(QColor("white"));
		text->setFont(QFont("Microsoft YaHei UI", 20));
		text->setPos(x+12,y+2);
		scene->addItem(text);//绘制文字
	}

	
	bool hasLeftChild()//返回是否有左孩子
	{
		return node->leftChild != NULL;
	}
	rbTreeNode<pair<const K, E>>* getLeftChild() //返回左孩子指针
	{
		if (node->leftChild == NULL)
			return NULL;
		return node->leftChild;
	}
	bool hasRightChild() //返回是否有右孩子
	{
		
		return node->rightChild != NULL;
	}
	rbTreeNode<pair<const K, E>>* getRightChild() //返回右孩子指针
	{
		
		if (node->rightChild == NULL)
			return NULL;
		return node->rightChild;
	}

	int getX() { return x; }//返回横坐标
	int getY() { return y; }//返回纵坐标
	int getLevel() { return level; }//返回层次
	bool getColor() { return node->color; };//返回颜色
private:
	int x;//绘图区横坐标
	int y;//绘图区纵坐标
	int level;//该节点的层次
	rbTreeNode<pair<const K, E>>* node;//该节点内部数据指针
};