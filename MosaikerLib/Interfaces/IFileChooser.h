#ifndef IFILECHOOSER_H
#define IFILECHOOSER_H

#include <QString>

class IFileChooser
{
public:
    virtual QString chooseFile() = 0;
};

#endif // IFILECHOOSER_H
