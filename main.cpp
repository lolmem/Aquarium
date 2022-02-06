#include "widget.h"

#include <QApplication>
#include "qsender.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QArea qa;
    QObject::connect(&qa,SIGNAL(myImg(QPixmap)),&w,SLOT(myImg(QPixmap)));

    QSender sender(&qa);
    QString str;

    if(argc > 1)
    {
        str = (argv[1]);
        qa.m_iiiii = str.toULongLong();
    }
    else
    {
        qa.m_iiiii = 10000000;
    }

    return a.exec();
}
