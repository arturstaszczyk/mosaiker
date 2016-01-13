#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <FileChooser.h>
#include <Commands/CommandOpenImage.h>
#include <Commands/CommandOpenResourcesDir.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mImageModelPtr = new ImageModel(this);
    mResourcesDirModelPtr = new ResourcesDirModel(this);

    ui->quickWidget->engine()->addImageProvider("imageModel", mImageModelPtr);

    ui->quickWidget->rootContext()->setContextProperty("imageModel", mImageModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("resourcesDirModel", mResourcesDirModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();
    QObject::connect(root, SIGNAL(openImage()), this, SLOT(openOriginalFileRequest()));
    QObject::connect(root, SIGNAL(setResourcesPath()), this, SLOT(openResourcesDirRequested()));
    QObject::connect(root, SIGNAL(buildIndex()), this, SLOT(buildIndexRequested()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOriginalFileRequest()
{
    PathChooser pathChooser;

    CommandOpenImage openImageCommand(pathChooser);
    QObject::connect(&openImageCommand, SIGNAL(imageOpened(QImage)),
                     mImageModelPtr, SLOT(setOriginalImage(QImage)));

    openImageCommand.execute();
}

void MainWindow::openResourcesDirRequested()
{
    PathChooser pathChooser;

    CommandOpenResourcesDir openResourcesCommand(pathChooser);
    QObject::connect(&openResourcesCommand, SIGNAL(dirOpened(QString)),
                     mResourcesDirModelPtr, SLOT(setResourcesDir(QString)));

    openResourcesCommand.execute();
}

void MainWindow::buildIndexRequested()
{
    QString filePath = QDir::cleanPath(mResourcesDirModelPtr->resourcesDir() + "/" + ResourcesDirModel::INDEX_FILE);
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    file.close();

    qDebug() << "Written file " << filePath;

    mResourcesDirModelPtr->setIndexBuilt(file.exists());
}
