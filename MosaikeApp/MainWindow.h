#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QTimer>
#include <QMainWindow>

#include<Commands/Command.h>
#include <Interfaces/IResourceFinder.h>

#include <Models/ImageModel.h>
#include <Models/ProgressBarModel.h>
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

private:
    void setupCommandsRecycler(quint32 msecDelay);

private slots:
    void recycleCommands();

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

    ImageModel* mImageModelPtr;
    ResourcesDirModel* mResourcesDirModelPtr;
    ProgressBarModel* mProgressBarModelPtr;

    QTimer* mCommandRecyclerTimer;
    QList<Command*> mCommandRecycler;
};

#endif // MAINWINDOW_H
