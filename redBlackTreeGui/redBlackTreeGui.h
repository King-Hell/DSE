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

class redBlackTreeGui : public QMainWindow
{
	Q_OBJECT

public:
	redBlackTreeGui(QWidget *parent = Q_NULLPTR);
	void draw();
signals:
	
public slots :
	void insert();
	void erase();
	void clear();

private:
	Ui::redBlackTreeGuiClass ui;
	QGraphicsScene scene;
	redBlackTree<QChar, char> tree;
	int HORIZONSPACE=100;//水平间距
	int VERTICALSPACE = 100;//垂直间距
};
