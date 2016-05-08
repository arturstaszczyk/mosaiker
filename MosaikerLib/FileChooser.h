#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QObject>

#include "Interfaces/IFileChooser.h"

class PathChooser : public QObject, public IPathChooser
{
    Q_OBJECT

public:
    explicit PathChooser(QObject* parent = nullptr);

    QString chooseFile() override;
    QString chooseDir() override;
};

#endif // FILECHOOSER_H
