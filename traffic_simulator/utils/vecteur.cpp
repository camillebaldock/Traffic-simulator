#include "vecteur.h"
#include "ligne.h"
#include "utils.h"

Utils::Vecteur::Vecteur()
: m_Depart(0.0, 0.0), m_Direction(0.0, 0.0) {
}

Utils::Vecteur::Vecteur(const Utils::Point &depart, const Utils::Point &dir)
: m_Depart(depart), m_Direction(dir) {
}

const Utils::Point& Utils::Vecteur::depart() const {
    return m_Depart;
}

Utils::Point& Utils::Vecteur::depart() {
    return m_Depart;
}

const Utils::Point& Utils::Vecteur::direction() const {
    return m_Direction;
}

Utils::Point& Utils::Vecteur::direction() {
    return m_Direction;
}

bool Utils::Vecteur::operator==(const Utils::Vecteur& v) const {
    return m_Direction == v.direction() && m_Depart == v.depart();
}

bool Utils::Vecteur::estSur(const Utils::Point& p) const {
    Utils::Ligne ligne(m_Depart, m_Depart + (m_Direction * 10));
    if (ligne.estVertical()) {
        return (presqueEgal(p.x(), ligne.xIntercept()) &&
                ((m_Direction.y() > 0 && p.y() >= m_Depart.y()) ||
                (m_Direction.y() < 0 && p.y() <= m_Depart.y())));
    } else {
        return (presqueEgal(p.y(), ligne.pente() * p.x() + ligne.yIntercept()) &&
                ((m_Direction.x() > 0 && p.x() >= m_Depart.x()) ||
                (m_Direction.x() < 0 && p.x() <= m_Depart.x())));
    }
}
