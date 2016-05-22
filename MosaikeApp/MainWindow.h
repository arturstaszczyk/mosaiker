#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void makeMosaicRequested();

    void onResourcesCount(quint32 resourcesCount);
    void onUpdateIndexBuildProgress(quint32 progress);
    void onIndexBuilt();
    void onMosaicCreated();

private:
    Ui::MainWindow *ui;

    PictureModel* mPrimaryImageModel;
    PictureModel* mSecondaryImageModel;

    ResourcesDirModel* mResourcesDirModelPtr;
    ProgressBarModel* mProgressBarModelPtr;

    CommandRecycler* mCommandRecycler;

};

#endif // MAINWINDOW_H
