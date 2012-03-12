#include "segment.h"
#include "ligne.h"
#include "utils.h"

Utils::Segment::Segment() {
}

Utils::Segment::Segment(const Utils::Point& depart, const Utils::Point& fin)
: m_Depart(depart), m_Fin(fin) {
}

QLineF Utils::Segment::toQLineF() const {
    return QLineF(m_Depart, m_Fin);
}

const Utils::Point& Utils::Segment::depart() const {
    return m_Depart;
}

Utils::Point& Utils::Segment::depart() {
    return m_Depart;
}

const Utils::Point& Utils::Segment::fin() const {
    return m_Fin;
}

Utils::Point& Utils::Segment::fin() {
    return m_Fin;
}

bool Utils::Segment::estSur(const Utils::Point& p) const {
    Utils::Ligne l(m_Depart, m_Fin);
    qreal depart_x = m_Depart.x(), fin_x = m_Fin.x(),
            depart_y = m_Depart.y(), fin_y = m_Fin.y();
    if (!l.estVertical()) {
        if (presqueEgal(p.y(), p.x() * l.pente() + l.yIntercept()))
            if ((depart_x <= p.x() && p.x() <= fin_x) || (fin_x <= p.x() && p.x() <= depart_x))
                if ((depart_y <= p.y() && p.y() <= fin_y) || (fin_y <= p.y() && p.y() <= depart_y))
                    return true;
        return false;
    } else {
        if ((depart_y <= p.y() && p.y() <= fin_y) || (fin_y <= p.y() && p.y() <= depart_y))
            if (presqueEgal(m_Depart.x(), p.x()))
                return true;
        return false;
    }
}

Utils::Point Utils::Segment::pointLePlusProche(const Utils::Point &p) const {
    Utils::Point diff = p - m_Depart;
    Utils::Point direction = m_Fin - m_Depart;
    qreal dot1 = diff.mult(direction);
    if (dot1 <= 0.0f)
        return m_Depart;

    qreal dot2 = direction.mult(direction);
    if (dot2 <= dot1)
        return m_Fin;

    qreal t = dot1 / dot2;
    return m_Depart + (direction * t);
}

bool Utils::Segment::operator==
(const Utils::Segment& s) const {
    return (m_Depart == s.depart() && m_Fin == s.depart()) ||
            (m_Depart == s.fin() && m_Fin == s.fin());
}

Utils::Segment Utils::Segment::versPerpendiculaireDepuisDepart(qreal decalage, qreal norme) const {
    Point dir(m_Fin - m_Depart);
    dir.normaliser();
    Point perpDir(-dir.y(), dir.x());
    perpDir.normaliser();
    Point decalagePt(m_Depart + (dir * decalage));
    return Segment(decalagePt - (perpDir * norme / 2.0), decalagePt + (perpDir * norme / 2.0));
}

Utils::Segment Utils::Segment::versPerpendiculaireDepuisFin(qreal decalage, qreal norme) const {
    Point dir(m_Fin - m_Depart);
    dir.normaliser();
    Point perpDir(-dir.y(), dir.x());
    perpDir.normaliser();
    Point decalagePt(m_Fin + (dir * decalage));
    return Segment(decalagePt - (perpDir * norme / 2.0), decalagePt + (perpDir * norme / 2.0));
}

Utils::Segment Utils::Segment::versDecalage(qreal decalage) const {
    return Segment(versPerpendiculaireDepuisDepart(0, decalage * 2).fin(),
            versPerpendiculaireDepuisFin(0, decalage * 2).fin());
}
