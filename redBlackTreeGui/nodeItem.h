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
		//����������ڵ㣬�����꣬�����꣬���
		this->x = x;
		this->y = y;
		this->node = node;
		this->level = level;
	}

	void paint(QGraphicsScene *scene) //����nodeItem����
	{
		QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(x, y, 50, 50);//������x��������y����С50*50
		ellipse->setPen(Qt::NoPen);
		QBrush brush;//�趨��ˢ��ɫ�����
		if (node->color == RED)
			brush.setColor(QColor("red"));
		else
			brush.setColor(QColor("black"));
		brush.setStyle(Qt::SolidPattern);
		ellipse->setBrush(brush);
		scene->addItem(ellipse);//����ͼ��

		QGraphicsTextItem *text=new QGraphicsTextItem(node->element.first);
		text->setDefaultTextColor(QColor("white"));
		text->setFont(QFont("Microsoft YaHei UI", 20));
		text->setPos(x+12,y+2);
		scene->addItem(text);//��������
	}

	
	bool hasLeftChild()//�����Ƿ�������
	{
		return node->leftChild != NULL;
	}
	rbTreeNode<pair<const K, E>>* getLeftChild() //��������ָ��
	{
		if (node->leftChild == NULL)
			return NULL;
		return node->leftChild;
	}
	bool hasRightChild() //�����Ƿ����Һ���
	{
		
		return node->rightChild != NULL;
	}
	rbTreeNode<pair<const K, E>>* getRightChild() //�����Һ���ָ��
	{
		
		if (node->rightChild == NULL)
			return NULL;
		return node->rightChild;
	}

	int getX() { return x; }//���غ�����
	int getY() { return y; }//����������
	int getLevel() { return level; }//���ز��
	bool getColor() { return node->color; };//������ɫ
private:
	int x;//��ͼ��������
	int y;//��ͼ��������
	int level;//�ýڵ�Ĳ��
	rbTreeNode<pair<const K, E>>* node;//�ýڵ��ڲ�����ָ��
};