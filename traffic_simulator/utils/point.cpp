#include "point.h"
#include <cmath>
#include "utils.h"

Utils::Point::Point() {
}

Utils::Point::Point(qreal x, qreal y)
: QPointF(x, y) {
}

Utils::Point::Point(const QPoint &p)
: QPointF(p) {
}

Utils::Point::Point(const QPointF &p)
: QPointF(p) {
}

Utils::Point Utils::Point::operator/(qreal miseAEchelle) const {
    return Point(x() / miseAEchelle, y() / miseAEchelle);
}

Utils::Point Utils::Point::operator*(qreal miseAEchelle) const {
    return Point(x() * miseAEchelle, y() * miseAEchelle);
}

Utils::Point Utils::Point::operator-(const Utils::Point& point) const {
    return Point(x() - point.x(), y() - point.y());
}

Utils::Point Utils::Point::operator+(const Utils::Point& point) const {
    return Point(x() + point.x(), y() + point.y());
}

const Utils::Point& Utils::Point::operator+=(const Utils::Point& point) {
    setX(x() + point.x());
    setY(y() + point.y());
    return *this;
}

const Utils::Point& Utils::Point::operator-=(const Utils::Point& point) {
    setX(x() - point.x());
    setY(y() - point.y());
    return *this;
}

const Utils::Point& Utils::Point::operator/=(qreal miseAEchelle) {
    if (!presqueEgal(miseAEchelle, 0, 0.001)) {
        setX(x() / miseAEchelle);
        setY(y() / miseAEchelle);
    }
    return *this;
}

const Utils::Point& Utils::Point::operator*=(qreal miseAEchelle) {
    setX(x() * miseAEchelle);
    setY(y() * miseAEchelle);
    return *this;
}

qreal Utils::Point::operator*(const Utils::Point &point) const {
    return mult(point);
}

bool Utils::Point::operator<(const Utils::Point & p) const {
    return norme() < p.norme();
}

bool Utils::Point::operator ==(const Utils::Point& p) const {
    return Utils::presqueEgal(x(), p.x()) && Utils::presqueEgal(y(), p.y());
}

qreal Utils::Point::norme() const {
    return sqrt(x() * x() + y() * y());
}

qreal Utils::Point::mult(const Utils::Point &point) const {
    return x() * point.x() + y() * point.y();
}

qreal Utils::Point::multcroisee(const Point &point) const {
    return x() * point.y() - y() * point.x();
}

/**
  * Donne la valeur de l'angle par rapport à l'origine de ce point en degrés
  * @param retablirEntre0et360 Si vrai, l'angle est entre 0 et 360, sinon l'angle est rétabli entre 0 et 180
  */
qreal Utils::Point::angle(const bool retablirEntre0et360) const {
    qreal ret = (qreal) (atan2(y(), x())*(180.0 / M_PI));
    if (retablirEntre0et360)
        Point::retablirEntre0et360(ret);
    else
        Point::retablirEntre0et180(ret);
    return ret;
}
/**
  * Rétablit la valeur de l'angle entre 0 et 360
  * @param valeur Angle en degrés
  */
qreal Utils::Point::retablirEntre0et360(const qreal valeur) {
    qreal ret = valeur;
    while (ret >= 360.0f) ret -= 360.0f;
    while (ret < 0.0f) ret += 360.0f;
    return ret;
}

/**
  * Rétablit la valeur de l'angle entre 0 et 180
  * @param valeur Angle en degrés
  */
qreal Utils::Point::retablirEntre0et180(const qreal valeur) {
    qreal ret = valeur;
    while (ret >= 180.0f) ret -= 360.0f;
    while (ret < -180.0f) ret += 360.0f;
    return ret;
}

qreal Utils::Point::angle(const Point &point1, const Point &point2) {
    return acos((point1 * point2) / (point1.norme() * point2.norme()));
}

qreal Utils::Point::angleSigne(const Point &point1, const Point &point2) {
    return atan2(point1.multcroisee(point2), point1.mult(point2));
}

qreal Utils::Point::angleEntreDeuxPoints(const Point &point1, const Point &point2) {
    Utils::Point p = point2 - point1;
    return p.angle();
}

/**
  * Ramener la norme du point à 1
  */
void Utils::Point::normaliser() {
    qreal mag = norme();
    if (mag == 0)
        return;
    setX(x() / mag);
    setY(y() / mag);
}
