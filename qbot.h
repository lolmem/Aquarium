#ifndef BOT_H
#define BOT_H

#include <QObject>

QT_BEGIN_NAMESPACE
namespace bot { class QBot; }
QT_END_NAMESPACE

class QBot : public QObject
{
    Q_OBJECT

public:
    QBot(bool rand = true);
    ~QBot();

    uint64_t doStep(uint64_t x, uint64_t y, uint64_t in, std::vector<QBot*> &bots, QBot* empty);
    uint64_t m_rating;
    uint64_t m_answer;

    uint64_t m_word[256];

    void setGen(uint64_t where, uint64_t gen);

    uint64_t m_age;

    uint64_t m_reg[8];

    uint64_t m_genX;
    uint64_t m_genY;

private:
    uint64_t m_mem[256];
    uint64_t m_me[256];

    uint64_t m_last[256];

    uint64_t m_iter;


};
#endif // BOT_H
