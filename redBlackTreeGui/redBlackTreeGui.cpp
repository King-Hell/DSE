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

}

void redBlackTreeGui::insert() {
	QString string = ui.lineEdit->text();
	pair<int, char> p(ui.lineEdit->text().toInt(), ' ');
	tree.insert(p);
	draw();	
}

void redBlackTreeGui::erase() {
	QString string = ui.lineEdit->text();
	tree.erase(string.toInt());
	draw();
}

void redBlackTreeGui::clear() {
	scene.clear();
	ui.lineEdit->setText("World");
}

void redBlackTreeGui::draw() {
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(QColor(255, 0, 0));
	int height = 2 * log(tree.size() + 1);
	QQueue<nodeItem*> queueNode;
	nodeItem *node = new nodeItem(tree.getRoot(), 0, 0,1);
	queueNode.push_back(node);
	while (!queueNode.empty()) {
		nodeItem *p = queueNode.front();
		p->paint(&scene);
		int x = p->getX();
		int y = p->getY();
		int level = p->getLevel();
		int space = HORIZONSPACE * pow(2, height - level);
		if (p->hasLeftChild()) {
			node = new nodeItem(p->getLeftChild(),x-space/4,y+VERTICALSPACE,level+1);
			queueNode.push_back(node);
		}
		if (p->hasRightChild()) {
			node = new nodeItem(p->getRightChild(), x + space / 4, y + VERTICALSPACE, level + 1);
			queueNode.push_back(node);
		}
		queueNode.pop_front();
	}

}