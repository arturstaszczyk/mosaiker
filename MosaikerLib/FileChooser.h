#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include "Interfaces/IFileChooser.h"

class PathChooser : public IPathChooser
{
public:
    PathChooser();

    QString chooseFile() override;
    QString chooseDir() override;
};

#endif // FILECHOOSER_H
