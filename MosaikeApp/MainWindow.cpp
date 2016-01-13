#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <FileChooser.h>
#include <Commands/CommandOpenImage.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mImageModelPtr = new ImageModel();

    ui->quickWidget->engine()->addImageProvider("imageModel", mImageModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("imageModel", mImageModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();
    QObject::connect(root, SIGNAL(openImage()), this, SLOT(openOriginalFileRequest()));
    QObject::connect(root, SIGNAL(setResourcesPath()), this, SLOT(openResourcesDirRequested()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOriginalFileRequest()
{
    FileChooser fileChooser;

    CommandOpenImage openImageCommand(fileChooser);
    QObject::connect(&openImageCommand, SIGNAL(imageOpened(QImage)),
                     mImageModelPtr, SLOT(setOriginalImage(QImage)));

    openImageCommand.execute();
}

void MainWindow::openResourcesDirRequested()
{
    qDebug() << "choose resources";
}
