#ifndef PROGRESSBARMODEL_H
#define PROGRESSBARMODEL_H

#include <QObject>

class ProgressBarModel : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarModel(QObject *parent = 0);

    Q_PROPERTY(quint32 value MEMBER mValue WRITE setValue NOTIFY valueChanged)

public :
    void setValue(quint32 val);

signals:
    void valueChanged(quint32);

private:
    quint32 mValue;
};

#endif // PROGRESSBARMODEL_H
