#ifndef VECTEUR_H
#define VECTEUR_H
#include "point.h"

namespace Utils {

    class Vecteur {
    public:
        Vecteur();
        Vecteur(const Point& depart, const Point& dir);
        const Point& depart() const;
        Point& depart();
        const Point& direction() const;
        Point& direction();
        virtual bool estSur(const Point &p) const;
        virtual bool operator==(const Vecteur& v) const;

    protected:
        Point m_Depart;
        Point m_Direction;
    };
}

#endif // VECTEUR_H
