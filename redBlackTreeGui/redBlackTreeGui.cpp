#include "redBlackTreeGui.h"
#include<math.h>
#include<qqueue.h>

redBlackTreeGui::redBlackTreeGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//scene.setSceneRect(-200, -200, 400, 400);
	ui.graphicsView->setScene(&scene);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing, true);
	ui.graphicsView->setRenderHint(QPainter::TextAntialiasing, true);
	ui.graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
}

void redBlackTreeGui::insert() {
	QString string = ui.lineEdit->text();
	if (string.length() != 1) {
		QMessageBox msgBox(QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("非法字符，请重新输入"), QMessageBox::Critical, QMessageBox::Ok | QMessageBox::Default, 0, 0);
		msgBox.exec();
		return;
	}
	QChar ch = string.at(0);
	pair<QChar, char> p(ch, ' ');
	tree.insert(p);
	draw();
	
}

void redBlackTreeGui::erase() {
	QString string = ui.lineEdit->text();
	if (string.length() != 1) {
		QMessageBox msgBox(QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("非法字符，请重新输入"), QMessageBox::Critical, QMessageBox::Ok | QMessageBox::Default, 0, 0);
		msgBox.exec();
		return;
	}
	QChar ch = string.at(0);
	tree.erase(ch);
	draw();
}

void redBlackTreeGui::clear() {
	scene.clear();
	tree.clear();
}

void redBlackTreeGui::draw() {
	ui.lineEdit->clear();
	scene.clear();
	if (tree.getRoot() == NULL)
		return;
	QPen pen(QColor("blcak"));
	pen.setWidth(8);
	int height = 2 * log(tree.size() + 1);
	QQueue<nodeItem*> queueNode;
	nodeItem *node = new nodeItem(tree.getRoot(), 0, 0, 1);
	queueNode.push_back(node);
	while (!queueNode.empty()) {
		nodeItem *p = queueNode.front();
		int x = p->getX();
		int y = p->getY();
		int level = p->getLevel();
		int space = HORIZONSPACE * pow(2, height - level);
		if (p->hasLeftChild()) {
			node = new nodeItem(p->getLeftChild(), x - space / 4, y + VERTICALSPACE, level + 1);
			queueNode.push_back(node);
			if (node->getColor() == RED)
				pen.setColor(QColor("red"));
			else
				pen.setColor(QColor("black"));
			scene.addLine(x + 25, y + 25, x - space / 4 + 25, y + VERTICALSPACE + 25, pen);
		}
		if (p->hasRightChild()) {
			node = new nodeItem(p->getRightChild(), x + space / 4, y + VERTICALSPACE, level + 1);
			queueNode.push_back(node);
			if (node->getColor() == RED)
				pen.setColor(QColor("red"));
			else
				pen.setColor(QColor("black"));
			scene.addLine(x + 25, y + 25, x + space / 4 + 25, y + VERTICALSPACE + 25, pen);
		}
		p->paint(&scene);
		queueNode.pop_front();
	}

}