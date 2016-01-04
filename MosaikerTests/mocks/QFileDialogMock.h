#ifndef QFILEDIALOGMOCK_H
#define QFILEDIALOGMOCK_H

#include <QFileDialog>
#include <QtMock.h>

class QFileDialogMock : public QFileDialog, public QtMockExt::QtMock
{
    int exec() override { MOCK_CALL; return RETURN_VALUES(int); }

    QStringList selectedFiles() { MOCK_CALL; return RETURN_VALUES(QStringList); }
};

#endif // QFILEDIALOGMOCK_H
