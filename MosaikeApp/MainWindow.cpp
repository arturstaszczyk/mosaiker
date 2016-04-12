#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <ResourceFinder.h>
#include <FileChooser.h>
#include <Commands/CommandOpenImage.h>
#include <Commands/CommandOpenResourcesDir.h>
#include <Commands/CommandBuildIndex.h>


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
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);
    QFile indexFile(indexFilePath);

    ResourceFinder finder(resourcesDir);
    CommandBuildIndex buildIndex(finder, indexFile);
    buildIndex.execute();

    qDebug() << "Written file " << indexFilePath;
    mResourcesDirModelPtr->setIndexBuilt(indexFile.exists());
}
