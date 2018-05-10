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

#define K QChar //当需要修改存储类型时仅需更改这两处即可
#define E char

class redBlackTreeGui : public QMainWindow
{
	Q_OBJECT

public:
	redBlackTreeGui(QWidget *parent = Q_NULLPTR);
	void draw();//重绘方法，红黑树的插入删除完成后调用此方法重绘界面
signals:
	
public slots :
	void insert();//插入按钮被点击后执行此方法，将编辑框中值对应的节点插入
	void erase();//删除按钮被点击后执行此方法，将编辑框中值对应的节点删除
	void clear();//清空按钮被点击后执行此方法，删除所有节点
	void insertAll();//初始化按钮被点击后执行此方法，将编辑框中所有数据初始化成红黑树

private:
	Ui::redBlackTreeGuiClass ui;//QT定义的UI类，用于描述界面中的空间
	QGraphicsScene scene;//QT场景类，用于在窗口中定义绘图区域
	redBlackTree<K, E> tree;//红黑树的内部存储形式
	int HORIZONSPACE=100;//两圆形的水平间距
	int VERTICALSPACE = 100;//两圆形的垂直间距
};
