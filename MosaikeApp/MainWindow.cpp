#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    ui->quickWidget->rootObject();
}

MainWindow::~MainWindow()
{
    delete ui;
}
