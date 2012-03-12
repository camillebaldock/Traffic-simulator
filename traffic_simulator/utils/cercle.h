#ifndef CERCLE_H
#define CERCLE_H
#include "point.h"

namespace Utils {

    class Cercle {
    public:
        Cercle();
        Cercle(const Utils::Point& centre, qreal rayon);
        Cercle(qreal x, qreal y, qreal rayon);
        const Point& centre() const;
        qreal rayon() const;

    protected:
        Utils::Point m_Centre;
        qreal m_Rayon;
    };
}

#endif // CERCLE_H
