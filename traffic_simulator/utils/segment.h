#ifndef SEGMENT_H
#define SEGMENT_H
#include <QLine>
#include "point.h"
namespace Utils {

class Segment {
    public:
        Segment();
        Segment(const Point& depart, const Point& fin);
        QLineF toQLineF() const;
        const Point& depart() const;
        Point& depart();
        const Point& fin() const;
        Point& fin();
        Segment versPerpendiculaireDepuisDepart(qreal decalage, qreal norme) const;
        Segment versPerpendiculaireDepuisFin(qreal decalage, qreal norme) const;
        Segment versDecalage(qreal decalage) const;
        virtual Point pointLePlusProche(const Point& p) const;
        virtual bool estSur(const Point& p) const;
        virtual bool operator==(const Segment& s) const;

    protected:
        Point m_Depart;
        Point m_Fin;
    };
}

#endif // SEGMENT_H
