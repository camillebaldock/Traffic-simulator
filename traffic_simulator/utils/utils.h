#ifndef UTILS_H
#define UTILS_H

#include "point.h"
#include "ligne.h"
#include "vecteur.h"
#include "segment.h"
#include "cercle.h"
#include <QRect>

namespace Utils {

#define UNIT_PAR_METRE  3.0000f
#define METRE_PAR_UNIT  0.3333f
#define DISTANCE_FEU    3
#define MPS_A_KMH      3.6f
#define KMH_A_MPS      0.27778f

    enum Couche
    {
       COUCHE_PLAN,
       COUCHE_ROUTE,
       COUCHE_INTERSECTION,
       COUCHE_VOIE,
       COUCHE_VEHICULE,
       COUCHE_ANNOTATIONS
    };

    bool presqueEgal(qreal float1, qreal float2, qreal epsilon=0.1);
    enum InfoIntersection {PAS_INTERSECTION, INTERSECTION, PARALLELE, COINCIDENT};
    Point InterLigneLigne(const Ligne& l1, const Ligne& l2, InfoIntersection& info);
    Point InterVecteurVecteur(const Vecteur& v1, const Vecteur& v2, InfoIntersection& info);
    Point InterVecteurSegment(const Vecteur& v, const Segment& s, InfoIntersection& info);
    Point InterSegmentSegment(const Segment& s1, const Segment& s2, InfoIntersection& info);
    void InterVecteurRectangle(const Vecteur &v, const QRect &rect, Point(&p)[2], InfoIntersection& info);
}

#endif // UTILS_H
