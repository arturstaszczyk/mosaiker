#include "FileChooser.h"

#include <QFileDialog>

PathChooser::PathChooser()
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
