#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_redBlackTreeGui.h"
#include<qgraphicsscene.h>
#include<redBlackTree.h>
#include<qpushbutton.h>
#include<qlineedit.h>
#include<qstring.h>
#include<qgraphicsitem.h>
#include"nodeItem.h"
#include<qmessagebox.h>

#define K QChar //����Ҫ�޸Ĵ洢����ʱ�����������������
#define E char

class redBlackTreeGui : public QMainWindow
{
	Q_OBJECT

public:
	redBlackTreeGui(QWidget *parent = Q_NULLPTR);
	void draw();//�ػ淽����������Ĳ���ɾ����ɺ���ô˷����ػ����
signals:
	
public slots :
	void insert();//���밴ť�������ִ�д˷��������༭����ֵ��Ӧ�Ľڵ����
	void erase();//ɾ����ť�������ִ�д˷��������༭����ֵ��Ӧ�Ľڵ�ɾ��
	void clear();//��հ�ť�������ִ�д˷�����ɾ�����нڵ�
	void insertAll();//��ʼ����ť�������ִ�д˷��������༭�����������ݳ�ʼ���ɺ����

private:
	Ui::redBlackTreeGuiClass ui;//QT�����UI�࣬�������������еĿռ�
	QGraphicsScene scene;//QT�����࣬�����ڴ����ж����ͼ����
	redBlackTree<K, E> tree;//��������ڲ��洢��ʽ
	int HORIZONSPACE=100;//��Բ�ε�ˮƽ���
	int VERTICALSPACE = 100;//��Բ�εĴ�ֱ���
};
