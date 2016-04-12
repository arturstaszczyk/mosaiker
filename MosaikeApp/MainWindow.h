#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>

#include <Interfaces/IResourceFinder.h>

#include <Models/ImageModel.h>
#include <Models/ResourcesDirModel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openOriginalFileRequest();
    void openResourcesDirRequested();
    void buildIndexRequested();

    void fileOpened(QString name){
        qDebug() << name;
    }

private:
    Ui::MainWindow *ui;

    ImageModel* mImageModelPtr;
    ResourcesDirModel* mResourcesDirModelPtr;
};

#endif // MAINWINDOW_H
