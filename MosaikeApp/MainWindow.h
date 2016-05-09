#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>

#include <Interfaces/IResourceFinder.h>

#include <Models/MainImageModel.h>
#include <Models/ProgressBarModel.h>
#include <Models/ResourcesDirModel.h>

#include <Commands/CommandRecycler.h>

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

    void onResourcesCount(quint32 resourcesCount);
    void onUpdateIndexBuildProgress(quint32 progress);

    void fileOpened(QString name){
        qDebug() << name;
    }

private:
    Ui::MainWindow *ui;

    MainImageModel* mImageModelPtr;
    ResourcesDirModel* mResourcesDirModelPtr;
    ProgressBarModel* mProgressBarModelPtr;

    CommandRecycler* mCommandRecycler;

};

#endif // MAINWINDOW_H
