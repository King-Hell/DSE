#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_redBlackTreeGui.h"

class redBlackTreeGui : public QMainWindow
{
	Q_OBJECT

public:
	redBlackTreeGui(QWidget *parent = Q_NULLPTR);

private:
	Ui::redBlackTreeGuiClass ui;
};
