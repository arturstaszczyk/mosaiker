#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QQuickItem>

#include <FileChooser.h>
#include <ImageManipulatorBuilder.h>
#include <Commands/CommandOpenImage.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();
    QObject::connect(root, SIGNAL(openImage()),
            this, SLOT(openFileRequest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileRequest()
{
    FileChooser fileChooser;

    ImageManipulatorBuilder builder(mImageLibrary);

    CommandOpenImage openImageCommand(builder, fileChooser);
    QObject::connect(&openImageCommand, SIGNAL(imageOpened(QImage)),
                     this, SLOT(requestedImageOpened(QImage)));

    openImageCommand.execute();
}

void MainWindow::requestedImageOpened(QImage image)
{
    qDebug() << "Opened" << image.width() << " " << image.height();
}
