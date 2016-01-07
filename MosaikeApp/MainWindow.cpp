#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QQuickItem>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <FileChooser.h>
#include <ImageManipulatorBuilder.h>
#include <Commands/CommandOpenImage.h>
#include <ImageLibs/ImageLibraryDevIL.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();
    QObject::connect(root, SIGNAL(openImage()),
            this, SLOT(openFileRequest()));

    ilInit();
    iluInit();
    ilEnable(IL_FILE_OVERWRITE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileRequest()
{
    FileChooser fileChooser;

    ImageLibraryDevIL imageLibrary;
    ImageManipulatorBuilder builder(imageLibrary);

    CommandOpenImage openImageCommand(builder, fileChooser);
    QObject::connect(&openImageCommand, SIGNAL(imageOpened(QImage)),
                     this, SLOT(requestedImageOpened(QImage)));

    openImageCommand.execute();
}

void MainWindow::requestedImageOpened(QImage image)
{
    qDebug() << "Opened" << image.width() << " " << image.height();
}
