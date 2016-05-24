#ifndef IFILECHOOSER_H
#define IFILECHOOSER_H

#include <QString>

class IPathChooser
{
public:
    enum OperationType
    {
        OT_OPEN,
        OT_WRITE,
    };

public:
    virtual QString chooseFile(OperationType) = 0;
    virtual QString chooseDir() = 0;
};

#endif // IFILECHOOSER_H
