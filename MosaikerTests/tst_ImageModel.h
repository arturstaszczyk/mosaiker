#ifndef TST_IMAGEMODEL_H
#define TST_IMAGEMODEL_H

#include <QObject>

class ImageModelTest : public QObject
{
    Q_OBJECT

private slots:
    void testImageModelResized();
    void testImageModelOriginal();
};

#endif // TST_IMAGEMODEL_H
