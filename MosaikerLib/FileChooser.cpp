#include "FileChooser.h"

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
    return QFileDialog::getExistingDirectory();
}
