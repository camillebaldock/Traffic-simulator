#ifndef LIGNE_H
#define LIGNE_H
#include "point.h"

namespace Utils {

    class Ligne {
    public:
        Ligne();
        Ligne(const Utils::Point& p1, const Utils::Point& p2);
        Ligne(qreal yIntercept, qreal pente);
        qreal yIntercept() const;
        qreal xIntercept() const;
        qreal pente() const;
        bool estVertical() const;
        bool estHorizontal() const;
        virtual bool estSur(const Point& p) const;
        virtual bool operator==(const Ligne& l) const;

    protected:
        qreal m_YIntercept, m_XIntercept;
        qreal m_Pente;
        bool m_EstVertical, m_EstHorizontal;
    };
}

#endif // LIGNE_H
