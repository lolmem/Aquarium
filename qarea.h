#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QRgb>

#include "qbot.h"

QT_BEGIN_NAMESPACE
namespace ar { class QArea; }
QT_END_NAMESPACE

class QArea : public QObject
{
    Q_OBJECT

public:
    QArea();
    ~QArea();

    uint64_t m_iter;
    int m_maxB;
    int m_maxS;

    uint64_t m_bestRating;
    uint64_t m_bestWord[256];
    uint64_t m_anotherWord[256];
    uint64_t m_iiiii;

private:
    std::vector<QBot*> m_bots;
    QBot* m_empty;
//    std::vector<QSpider*> m_spiders;

//    QSpider *m_zero;

public slots:
    void testMe();

signals:
    void myImg(QPixmap map);
};
#endif // AREA_H
