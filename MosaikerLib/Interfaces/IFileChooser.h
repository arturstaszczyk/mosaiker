#ifndef IFILECHOOSER_H
#define IFILECHOOSER_H

#include <QString>

class IPathChooser
{
public:
    virtual QString chooseFile() = 0;
    virtual QString chooseDir() = 0;
};

#endif // IFILECHOOSER_H
