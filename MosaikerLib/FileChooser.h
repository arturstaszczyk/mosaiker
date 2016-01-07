#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include "Interfaces/IFileChooser.h"

class FileChooser : public IFileChooser
{
public:
    FileChooser();

    QString chooseFile();
};

#endif // FILECHOOSER_H
