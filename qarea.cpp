#include "qarea.h"

#include <QTimer>
#include <QDebug>
#include <QCoreApplication>

QArea::QArea()
{
    m_empty = new QBot;

    for(size_t i = 0; i < (256 * 256); i++)
    {
        m_bots.push_back(m_empty);
    }

    for(size_t i = 0; i < (256 * 256)/2; i++)
    {

        QBot *b = new QBot;
        b->m_rating = 256;
        m_bots[i] = b;

    }


    QTimer::singleShot(0, this, SLOT(testMe()));

    m_iter = 0;

    m_maxB = 1;
    m_maxS = 1;
}

QArea::~QArea()
{
    while (!m_bots.empty())
    {
        if(m_bots.back() != m_empty)
            delete m_bots.back();
        m_bots.pop_back();
    }
    delete m_empty;
}

void QArea::testMe()
{
    QImage img(512, 512, QImage::Format_RGB888);

    uint64_t t_max = 1;

    m_empty->m_rating = 0;

    for(size_t y = 0; y < 256; y++)
    for(size_t x = 0; x < 256; x++)
    {
        if(m_bots[x+(256*y)] != m_empty && m_bots[x+(256*y)]->m_age < m_iter)
        {
            m_bots[x+(256*y)]->m_age = m_iter;

            int ret = 0;
            int reg = 0;
            for(size_t i = 0; i < 256 && m_bots[x+(256*y)] != m_empty; i++)
            {
                ret += m_bots[x+(256*y)]->doStep(x,y,0,m_bots,m_empty);
                reg += m_bots[x+(256*y)]->m_reg[0];
            }

            int rating = m_bots[x+(256*y)]->m_rating;
            img.setPixel(x * 2,y * 2,qRgb(((255 * rating)/m_maxB), reg % 256, ret/256 % 255));
            img.setPixel(1 + x * 2, y * 2, qRgb(((255 * rating)/m_maxB),255,255));
            img.setPixel(x * 2, 1 + y * 2, qRgb(rating/255,255,255));
            img.setPixel(1 + x * 2, 1 + y * 2,qRgb(rating,0,0));

            if(m_bots[x+(256*y)] != m_empty)
            {
                if(rating > t_max)
                    t_max = rating;

                if(rating + 1 > 0 && rand() % (rating + 1) == 0)
                {
                    m_bots[x + (256 * y)]->setGen(rand(),rand());
                    m_bots[x+(256*y)]->m_rating++;
                }

                if(m_bestRating < m_bots[x+(256*y)]->m_rating)
                {
                    m_bestRating = m_bots[x+(256*y)]->m_rating;
                    std::memcpy(m_bestWord,m_bots[x+(256*y)]->m_word, 256 * sizeof(uint64_t));
                }

                if(rand() % m_iiiii == 0)
                {
                    std::memcpy(m_bots[x+(256*y)]->m_word, m_bestWord, 256 * sizeof(uint64_t));
                }


                if(rating < 10)
                {
                    delete m_bots[x + (256 * y)];
                    m_bots[x + (256 * y)] = m_empty;
                }

            }
        }
        else
        {
            img.setPixel(x * 2,y * 2,qRgb(0,0,0));
            img.setPixel(1 + x * 2, y * 2,qRgb(0,0,0));
            img.setPixel(x * 2, 1 + y * 2,qRgb(0,0,0));
            img.setPixel(1 + x * 2, 1 + y * 2,qRgb(0,0,0));
        }
    }

    m_maxB = t_max + 1;

    QCoreApplication::processEvents();
    emit myImg(QPixmap::fromImage(img));
    QTimer::singleShot(0, this, SLOT(testMe()));

//    qDebug() << m_iter++;
    m_iter++;

}
