#include "utils.h"
#include <qmath.h>

bool Utils::presqueEgal(qreal float1, qreal float2, qreal epsilon)
{
  qreal result;
  if (float1 < float2) result = float2 - float1;
  else result = float1 - float2;
  bool res = result < epsilon;
  return res;
}

Utils::Point Utils::InterLigneLigne
(const Utils::Ligne &l1,
        const Utils::Ligne &l2,
        Utils::InfoIntersection &info) {
    if (!l1.estVertical() && !l2.estVertical()) {
        qreal x1 = 0, x2 = 1, x3 = 0, x4 = 1;
        qreal y1 = l1.pente() * x1 + l1.yIntercept(),
                y2 = l1.pente() * x2 + l1.yIntercept(),
                y3 = l2.pente() * x3 + l2.yIntercept(),
                y4 = l2.pente() * x4 + l2.yIntercept();

        qreal denom = (y4 - y3)*(x2 - x1)-(x4 - x3)*(y2 - y1),
                numa = (x4 - x3)*(y1 - y3)-(y4 - y3)*(x1 - x3),
                numb = (x2 - x1)*(y1 - y3)-(y2 - y1)*(x1 - x3);
        qreal ua = numa / denom;

        Utils::Point p(x1 + ua * (x2 - x1), y1 + ua * (y2 - y1));
        if (Utils::presqueEgal(denom, 0) &&
                Utils::presqueEgal(numa, 0) &&
                Utils::presqueEgal(numb, 0))
        {
            info = COINCIDENT;
        } else if (Utils::presqueEgal(denom, 0))
        {
            info = PARALLELE;
        } else {
            info = INTERSECTION;
        }
        return p;
    } else if (l1.estVertical() && !l2.estVertical()) {
        Utils::Point p(l1.xIntercept(), l2.pente() * l1.xIntercept() + l2.yIntercept());
        info = INTERSECTION;
        return p;
    } else if (!l1.estVertical() && l2.estVertical()) {
        Utils::Point p(l2.xIntercept(), l1.pente() * l2.xIntercept() + l1.yIntercept());
        info = INTERSECTION;
        return p;
    } else {
        if (Utils::presqueEgal(l1.xIntercept(), l2.xIntercept())) {
            info = COINCIDENT;
        } else {
            info = PAS_INTERSECTION;
        }
        return Utils::Point(0.0, 0.0);
    }
}

Utils::Point Utils::InterVecteurVecteur
(const Utils::Vecteur &r1,
        const Utils::Vecteur &r2,
        Utils::InfoIntersection &info) {
    Point p1b = r1.depart(),
            p1e = r1.depart() + (r1.direction() * 10),
            p2b = r2.depart(),
            p2e = r2.depart() + (r2.direction() * 10);
    Ligne l1(p1b, p1e),
            l2(p2b, p2e);
    Point lli = InterLigneLigne(l1, l2, info);
    if (info == INTERSECTION && r1.estSur(lli) && r2.estSur(lli))
        return lli;
    else {
        info = PAS_INTERSECTION;
        return Point();
    }
}

Utils::Point Utils::InterVecteurSegment (const Utils::Vecteur &r,
                                         const Utils::Segment &ls,
                                         Utils::InfoIntersection &info) {
    Point p1 = r.depart(),
            p2 = r.depart() + (r.direction() * 10);
    Ligne l1(p1, p2), l2(ls.depart(), ls.fin());
    Point lli = InterLigneLigne
            (l1, l2, info);
    if (info == INTERSECTION && r.estSur(lli) && ls.estSur(lli)) {
        return lli;
    } else {
        info = PAS_INTERSECTION;
        return Point();
    }
}

Utils::Point Utils::InterSegmentSegment
(const Utils::Segment &s1,
        const Utils::Segment &s2,
        Utils::InfoIntersection &info) {
    Ligne l1(s1.depart(), s1.fin()),
            l2(s2.depart(), s2.fin());
    Point p = InterLigneLigne(l1, l2, info);
    if (info == INTERSECTION && s1.estSur(p) && s2.estSur(p)) {
        return p;
    } else if (info == INTERSECTION) {
        info = PAS_INTERSECTION;
    }
    return Point();
}

//TODO: Cet algorithme est à optimiser !!
void Utils::InterVecteurRectangle(const Vecteur &v, const QRect &rect, Point(&pts)[2], InfoIntersection& info) {
    bool premierTrouve = false, deuxiemeTrouve = false;
    Point p1, p2, p;
    Segment s1(Point(rect.topLeft()), Point(rect.bottomLeft()));
    InfoIntersection inf;
    p = InterVecteurSegment(v, s1, inf);
    if (inf != PAS_INTERSECTION) {
        premierTrouve = true;
        info = INTERSECTION;
        p1 = p;
    }

    Segment s2(Point(rect.bottomLeft()), Point(rect.bottomRight()));
    p = InterVecteurSegment(v, s2, inf);
    if (inf != PAS_INTERSECTION) {
        if (!premierTrouve) {
            premierTrouve = true;
            p1 = p;
            info = INTERSECTION;
        } else {
            deuxiemeTrouve = true;
            p2 = p;
        }
    }

    if (premierTrouve && deuxiemeTrouve) {
        qreal d1 = (v.depart() - p1).norme();
        qreal d2 = (v.depart() - p2).norme();
        if (d2 > d1) {
            pts[0] = p1;
            pts[1] = p2;
            return;
        } else {
            pts[1] = p1;
            pts[0] = p2;
            return;
        }
    }

    Segment s3(Point(rect.bottomRight()), Point(rect.topRight()));
    p = InterVecteurSegment(v, s3, inf);
    if (inf != PAS_INTERSECTION) {
        if (!premierTrouve) {
            premierTrouve = true;
            p1 = p;
            info = INTERSECTION;
        } else {
            deuxiemeTrouve = true;
            p2 = p;
        }
    }

    if (premierTrouve && deuxiemeTrouve) {
        qreal d1 = (v.depart() - p1).norme();
        qreal d2 = (v.depart() - p2).norme();
        if (d2 > d1) {
            pts[0] = p1;
            pts[1] = p2;
            return;
        } else {
            pts[1] = p1;
            pts[0] = p2;
            return;
        }
    }

    Segment s4(Point(rect.bottomRight()), Point(rect.topRight()));
    p = InterVecteurSegment(v, s4, inf);
    if (inf != PAS_INTERSECTION) {
        if (!premierTrouve) {
            premierTrouve = true;
            p1 = p;
            info = INTERSECTION;
        } else {
            deuxiemeTrouve = true;
            p2 = p;
        }
    }

    if (premierTrouve && deuxiemeTrouve) {
        qreal d1 = (v.depart() - p1).norme();
        qreal d2 = (v.depart() - p2).norme();
        if (d2 > d1) {
            pts[0] = p1;
            pts[1] = p2;
            return;
        } else {
            pts[1] = p1;
            pts[0] = p2;
            return;
        }
    } else {
        pts[0] = p1;
        pts[1] = p2;
    }

}
