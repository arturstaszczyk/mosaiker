#include "FileChooser.h"

#include <QDebug>
#include <QFileDialog>

FileChooser::FileChooser(QObject* parent)
    : QObject(parent)
{

}

QString FileChooser::chooseFile(OperationType operationType)
{
    switch(operationType)
    {
        case OT_OPEN:
            return QFileDialog::getOpenFileName();
        case OT_WRITE:
            return QFileDialog::getSaveFileName();
    }
}

QString FileChooser::chooseDir()
{
    QString dirName = "";
    try
    {
        dirName = QFileDialog::getExistingDirectory();
    }
    catch(std::exception& ex)
    {
        qDebug() << ex.what();
    }

    return dirName;
}
