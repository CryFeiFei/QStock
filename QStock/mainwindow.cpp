#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstockinfo.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QStockInfo* stinfo = new QStockInfo(this);

}

MainWindow::~MainWindow()
{
	delete ui;
}

