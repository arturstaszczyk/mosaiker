#ifndef FILECHOOSERMOCK_H
#define FILECHOOSERMOCK_H

#include <QtMock.h>

#include "Interfaces/IFileChooser.h"

class FileChooserMock : public IFileChooser, public QtMockExt::QtMock
{
public:
    QString chooseFile() override
    {
        MOCK_CALL;
        return RETURN_VALUES(QString);
    }
};

#endif // FILECHOOSERMOCK_H
