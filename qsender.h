#ifndef QSENDER_H
#define QSENDER_H

#include <QObject>
#include "qarea.h"

class QSender: public QObject
{
    Q_OBJECT
public:
    QSender(QArea *a);
private:
    QArea *m_area;

public slots:
    void sendMe();
};

#endif // QSENDER_H
