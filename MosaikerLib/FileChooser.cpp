#include "FileChooser.h"

#include <QDebug>
#include <QFileDialog>

PathChooser::PathChooser(QObject* parent)
    : QObject(parent)
{

}

QString PathChooser::chooseFile()
{
    return QFileDialog::getOpenFileName();
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
