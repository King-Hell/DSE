#include "redBlackTreeGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	redBlackTreeGui w;
	w.show();
	return a.exec();
}
