#include "FileChooser.h"

#include <QFileDialog>

FileChooser::FileChooser()
{

}

QString FileChooser::chooseFile()
{
    return QFileDialog::getOpenFileName();
}
