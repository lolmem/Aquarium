#include "qsender.h"

#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QTimer>

#include <QDebug>


QSender::QSender(QArea *a)
{
    m_area = a;
    QTimer::singleShot(1000, this, SLOT(sendMe()));
}

void QSender::sendMe()
{
    qDebug() << "send!";
    QString str;
    for(size_t i = 0; i < 256; i++)
    {
        str.append(QString::number(m_area->m_bestWord[i]));
        str.append(" ");
    }

    QProcess *p = new QProcess(this);

    QFile f;
    f.setFileName("send.bat");
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "can't create file: thread.bat";
        return;
    }

    QTextStream ts(&f);

    ts << "npm run sendMessage \"lol\"";// << "\"GENSTART " << str << " GENEND\"";
    f.close();

    QStringList sl;
    p->start("send.bat",sl);

    QTimer::singleShot(100000, this, SLOT(sendMe()));
}
