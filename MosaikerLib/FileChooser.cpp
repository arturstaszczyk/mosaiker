#include "FileChooser.h"

#include <QDebug>
#include <QFileDialog>

PathChooser::PathChooser(QObject* parent)
    : QObject(parent)
{

}

QString PathChooser::chooseFile(OperationType operationType)
{
    switch(operationType)
    {
        case OT_OPEN:
            return QFileDialog::getOpenFileName();
        case OT_WRITE:
            return QFileDialog::getSaveFileName();
    }
}

QString PathChooser::chooseDir()
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
