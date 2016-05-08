#ifndef PROGRESSBARMODEL_H
#define PROGRESSBARMODEL_H

#include <QObject>

class ProgressBarModel : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarModel(QObject *parent = 0);

    Q_PROPERTY(quint32 maxValue MEMBER mMaxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(quint32 value MEMBER mValue WRITE setValue NOTIFY valueChanged)

public :
    void setMaxValue(quint32 maxVal);
    void setValue(quint32 val);

signals:
    void maxValueChanged(quint32);
    void valueChanged(quint32);

private:
    quint32 mMaxValue;
    quint32 mValue;
};

#endif // PROGRESSBARMODEL_H
