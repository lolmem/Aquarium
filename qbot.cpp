#include "qbot.h"

QBot::QBot(bool r)
{
    for(size_t i = 0; i < 256  && r; i++)
        m_me[i] = static_cast<uint64_t>(rand() % 256);

    m_rating = 1;
}

QBot::~QBot()
{
}

uint64_t QBot::doStep(uint64_t x, uint64_t y, uint64_t in, std::vector<QBot *> &bots, QBot* empty)
{
    m_iter++;

    switch (m_me[m_iter % 256])
    {
    case 0:
        break;
    case 1:
        m_mem[m_reg[0] % 256] = in;
        break;
    case 2:
        m_mem[m_reg[1] % 256] = x;
        break;
    case 3:
        m_mem[m_reg[2] % 256] = y;
        break;
    case 5:
        m_mem[m_reg[3] % 256] = m_rating;
        break;
    case 6:
        m_answer = m_mem[m_reg[4] % 256];
        break;
    case 7:
        m_word[m_reg[5] % 256] = m_mem[m_reg[6] % 256];
        break;
    case 8:
        switch (m_reg[7] % 4) {
        case 0:
            m_mem[m_reg[6] % 256] = bots[(x + 1) % (256) + (256 * (y))]->m_word[m_reg[5] % 256];
            break;
        case 1:
            m_mem[m_reg[6] % 256] = bots[(x - 1) % (256) + (256 * (y))]->m_word[m_reg[5] % 256];
            break;
        case 2:
            m_mem[m_reg[6] % 256] = bots[x + (256 * ((y + 1) % (256)))]->m_word[m_reg[5] % 256];
            break;
        case 3:
            m_mem[m_reg[6] % 256] = bots[x + (256 * ((y - 1) % (256)))]->m_word[m_reg[5] % 256];
            break;
        }
        break;
    case 9:
        std::swap(m_reg[0],m_reg[1]);
        break;
    case 10:
        std::swap(m_reg[0],m_reg[2]);
        break;
    case 11:
        std::swap(m_reg[0],m_reg[3]);
        break;
    case 12:
        std::swap(m_reg[0],m_reg[4]);
        break;
    case 13:
        std::swap(m_reg[0],m_reg[5]);
        break;
    case 14:
        std::swap(m_reg[0],m_reg[6]);
        break;
    case 15:
        std::swap(m_reg[0],m_reg[7]);
        break;
    case 16:
        m_reg[0] = m_reg[1];
        break;
    case 17:
        m_reg[0] = m_reg[2];
        break;
    case 18:
        m_reg[0] = m_reg[3];
        break;
    case 19:
        m_reg[0] = m_reg[4];
        break;
    case 20:
        m_reg[0] = m_reg[5];
        break;
    case 21:
        m_reg[0] = m_reg[6];
        break;
    case 22:
        m_reg[0] = m_reg[7];
        break;
    case 23:
        m_reg[0] = 0;
        break;
    case 24:
        m_reg[0] = std::numeric_limits<uint64_t>::max();
        break;
    case 25:
        m_reg[0]++;
        break;
    case 26:
        m_reg[0]--;
        break;
    case 27:
        m_reg[0] += m_reg[1];
        break;
    case 28:
        m_reg[0] -= m_reg[1];
        break;
    case 29:
        m_reg[0] *= m_reg[1];
        break;
    case 30:
        m_reg[0] /= (m_reg[1] == 0? 1 : m_reg[1]);
        break;
    case 31:
        m_reg[0] %= (m_reg[1] == 0? 1 : m_reg[1]);
        break;
    case 32:
        m_reg[0] <<= m_reg[1];
        break;
    case 33:
        m_reg[0] >>= m_reg[1];
        break;
    case 34:
        m_reg[0] |= m_reg[1];
        break;
    case 35:
        m_reg[0] = ~m_reg[1];
        break;
    case 36:
        if(m_reg[1] > m_reg[2])
            m_iter++;
        break;
    case 37:
        m_iter += m_reg[3];
        break;
    case 38:
        m_iter -= m_reg[3];
        break;
    case 39:
        switch (m_reg[7] % 4)
        {
        case 0:
            if(bots[(x + 1) % (256) + (256 * (y))]->m_rating < m_rating)
            {
                bots[(x + 1) % (256) + (256 * (y))]->setGen(m_reg[3],m_reg[4]);
                bots[(x + 1) % (256) + (256 * (y))]->m_genX = x;
                bots[(x + 1) % (256) + (256 * (y))]->m_genY = y;
            }
            break;
        case 1:
            if(bots[(x - 1) % (256) + (256 * (y))]->m_rating < m_rating)
            {
                bots[(x - 1) % (256) + (256 * (y))]->setGen(m_reg[3],m_reg[4]);
                bots[(x - 1) % (256) + (256 * (y))]->m_genX = x;
                bots[(x - 1) % (256) + (256 * (y))]->m_genY = y;
            }
            break;
        case 2:
            if(bots[x + (256 * ((y + 1) % (256)))]->m_rating < m_rating)
            {
                bots[x + (256 * ((y + 1) % (256)))]->setGen(m_reg[3],m_reg[4]);
                bots[x + (256 * ((y + 1) % (256)))]->m_genX = x;
                bots[x + (256 * ((y + 1) % (256)))]->m_genY = y;
            }
            break;
        case 3:
            if(bots[x + (256 * ((y - 1) % (256)))]->m_rating < m_rating)
            {
                bots[x + (256 * ((y - 1) % (256)))]->setGen(m_reg[3],m_reg[4]);
                bots[x + (256 * ((y + 1) % (256)))]->m_genX = x;
                bots[x + (256 * ((y + 1) % (256)))]->m_genY = y;
            }
            break;
        }

        if(m_rating > 0)
            m_rating--;

        break;
    case 40:
        if(m_rating > 0)
        {
            m_rating--;
            switch (m_reg[7] % 4)
            {
            case 0:
                bots[(x + 1) % (256) + (256 * (y))]->m_rating++;
                break;
            case 1:
                bots[(x - 1) % (256) + (256 * (y))]->m_rating++;
                break;
            case 2:
                bots[x + (256 * ((y + 1) % (256)))]->m_rating++;
                break;
            case 3:
                bots[x + (256 * ((y - 1) % (256)))]->m_rating++;
                break;
            }
            break;
        }
    case 41:
        m_mem[m_reg[5] % 256] += m_me[m_reg[6] % 256];
        break;
    case 42:
        m_me[m_reg[5] % 256] += m_mem[m_reg[6] % 256];
        break;
    case 43:
        std::swap(m_mem[m_reg[7] % 256],m_reg[1]);
        break;
    case 44:
        std::swap(m_word[m_reg[7] % 256],m_reg[1]);
        break;
    case 46:
        if(bots[(x + 1) % (256) + (256 * (y))] == empty)
//        if(bots[(x + (256 * y))]->m_rating > bots[(x + 1) % (256) + (256 * (y))]->m_rating)
            std::swap(bots[(x + (256 * y))],bots[(x + 1) % (256) + (256 * (y))]);
        break;
    case 47:
        if(bots[(x - 1) % (256) + (256 * (y))] == empty)
//        if(bots[(x + (256 * y))]->m_rating > bots[(x - 1) % (256) + (256 * (y))]->m_rating)
            std::swap(bots[(x + (256 * y))],bots[(x - 1) % (256) + (256 * (y))]);
        break;
    case 48:
        if(bots[x + (256 * ((y + 1) % (256)))] == empty)
//        if(bots[(x + (256 * y))]->m_rating > bots[x + (256 * ((y + 1) % (256)))]->m_rating)
            std::swap(bots[(x + (256 * y))],bots[x + (256 * ((y + 1) % (256)))]);
        break;
    case 49:
//        if(bots[(x + (256 * y))]->m_rating > bots[x + (256 * ((y - 1) % (256)))]->m_rating)
        if(bots[x + (256 * ((y - 1) % (256)))] == empty)
            std::swap(bots[(x + (256 * y))],bots[x + (256 * ((y - 1) % (256)))]);
        break;
    case 50:
            switch (m_reg[7] % 4)
            {
            case 0:
                m_reg[5] = bots[(x + 1) % (256) + (256 * (y))]->m_rating;
                break;
            case 1:
                m_reg[5] = bots[(x - 1) % (256) + (256 * (y))]->m_rating;
                break;
            case 2:
                m_reg[5] = bots[x + (256 * ((y + 1) % (256)))]->m_rating;
                break;
            case 3:
                m_reg[5] = bots[x + (256 * ((y - 1) % (256)))]->m_rating;
                break;
            }
        break;
    case 51:
            if(m_rating > 2)
            {
                switch (m_reg[7] % 4)
                {
                case 0:
                    if(bots[((x + 1) % (256) + (256 * (y)))] == empty)
                    {
                        bots[(x + 1) % (256) + (256 * (y))] = new QBot(false);
                        bots[(x + 1) % (256) + (256 * (y))]->m_rating = m_rating/2;
                    }
                    break;
                case 1:
                    if(bots[(x - 1) % (256) + (256 * (y))] == empty)
                    {
                        bots[(x - 1) % (256) + (256 * (y))] = new QBot(false);
                        bots[(x - 1) % (256) + (256 * (y))]->m_rating = m_rating/2;
                    }
                    break;
                case 2:
                    if(bots[x + (256 * ((y + 1) % (256)))] == empty)
                    {
                        bots[x + (256 * ((y + 1) % (256)))] = new QBot(false);
                        bots[x + (256 * ((y + 1) % (256)))]->m_rating = m_rating/2;
                    }
                    break;
                case 3:
                    if(bots[x + (256 * ((y - 1) % (256)))] == empty)
                    {
                        bots[x + (256 * ((y - 1) % (256)))] = new QBot(false);
                        bots[x + (256 * ((y - 1) % (256)))]->m_rating = m_rating/2;
                    }
                    break;
                }
                m_rating = m_rating/2;
            }
        break;
    default:
        m_me[m_iter % 256] = 0;
        break;
    }

    return m_me[m_iter % 256];
}

void QBot::setGen(uint64_t where, uint64_t gen)
{
    m_me[where % 256] = gen % 256;
}
