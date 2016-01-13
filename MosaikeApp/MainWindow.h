#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <Models/ImageModel.h>

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

    void fileOpened(QString name){
        qDebug() << name;
    }

private:
    Ui::MainWindow *ui;

    ImageModel* mImageModelPtr;
};

#endif // MAINWINDOW_H
