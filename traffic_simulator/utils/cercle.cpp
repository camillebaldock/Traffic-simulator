#include "cercle.h"
#include "utils.h"

Utils::Cercle::Cercle()
: m_Centre(0.0, 0.0), m_Rayon(0.0) {
}

Utils::Cercle::Cercle(const Utils::Point &centre, qreal rayon)
: m_Centre(centre), m_Rayon(rayon) {
}

Utils::Cercle::Cercle(qreal x, qreal y, qreal rayon)
: m_Centre(x, y), m_Rayon(rayon) {
}

const Utils::Point& Utils::Cercle::centre() const {
    return m_Centre;
}

qreal Utils::Cercle::rayon() const {
    return m_Rayon;
}
