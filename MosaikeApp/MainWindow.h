﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Interfaces/IResourceFinder.h>

#include <Models/MatcherModel.h>
#include <Models/PictureModel.h>
#include <Models/SliceSizeModel.h>
#include <Models/ProgressBarModel.h>
#include <Models/ResourcesDirModel.h>
#include <Models/MosaicBuildButtonModel.h>

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
    void onOpenOriginalFileButton();
    void onOpenResourcesDirButton();
    void onBuildIndexButton();
    void onMakeMosaicButton();
    void onSaveMosaicButton();

    void onAsyncCommandProgress(quint32 progress);
    void onCommandIndexBuilt();
    void onCommandMosaicCreated();

private:
    void createModels();
    void setQmlContextProps();

private:
    Ui::MainWindow *ui;

    PictureModel* mPrimaryImageModel;

    MatcherModel* mMatcherModel;
    ResourcesDirModel* mResourcesDirModel;
    ProgressBarModel* mProgressBarModel;
    MosaicBuildButtonModel* mMakeMosaicButtonModel;
    SliceSizeModel* mSliceSizeModel;

    CommandRecycler* mCommandRecycler;

};

#endif // MAINWINDOW_H
