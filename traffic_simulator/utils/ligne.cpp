#include "ligne.h"
#include "utils.h"

Utils::Ligne::Ligne()
: m_YIntercept(0.0), m_XIntercept(0.0), m_Pente(0.0),
m_EstVertical(false), m_EstHorizontal(false) {
}

/**
  * Constructeur
  * Set verticalité, horizontalité et pente de la ligne
  * @param p1 Premier point
  * @param p2 Deuxième point
  */
Utils::Ligne::Ligne(const Utils::Point &p1, const Utils::Point &p2) {
    m_EstVertical = presqueEgal(p1.x() - p2.x(), 0.01);
    m_EstHorizontal = presqueEgal(p1.y() - p2.y(), 0.01);
    if (m_EstVertical) m_Pente = 0;
    else m_Pente = (p2.y() - p1.y()) / (p2.x() - p1.x());
    if (!m_EstHorizontal) {
        m_YIntercept = p1.y() - m_Pente * p1.x();
    } else {
        m_YIntercept = p1.y();
    }

    if (!m_EstVertical) {
        m_XIntercept = -m_YIntercept / m_Pente;
    } else {
        m_XIntercept = p1.x();
    }
}

Utils::Ligne::Ligne(qreal yIntercept, qreal pente)
: m_YIntercept(yIntercept), m_Pente(pente) {
}

bool Utils::Ligne::estHorizontal() const {
    return m_EstHorizontal;
}

bool Utils::Ligne::estVertical() const {
    return m_EstVertical;
}

qreal Utils::Ligne::pente() const {
    return m_Pente;
}

qreal Utils::Ligne::yIntercept() const {
    return m_YIntercept;
}

qreal Utils::Ligne::xIntercept() const {
    return m_XIntercept;
}

bool Utils::Ligne::estSur(const Utils::Point &p) const {
    return presqueEgal(m_Pente * p.x() + m_YIntercept, p.y());
}

bool Utils::Ligne::operator==(const Utils::Ligne& l) const {
    return presqueEgal(m_Pente, l.pente()) &&
            presqueEgal(m_YIntercept, l.yIntercept());
}
