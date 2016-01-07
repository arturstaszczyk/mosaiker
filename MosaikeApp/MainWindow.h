#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <ImageLibs/ImageLibraryDevIL.h>

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
    void openFileRequest();
    void requestedImageOpened(QImage image);

private:
    Ui::MainWindow *ui;

    ImageLibraryDevIL mImageLibrary;
};

#endif // MAINWINDOW_H
