#ifndef POINT_H
#define POINT_H

#include <QPoint>
#include <QString>
namespace Utils {

    class Point : public QPointF {
    public:
        Point();
        Point(qreal x, qreal y);
        Point(const QPoint& point);
        Point(const QPointF& point);

        Point operator/(qreal miseAEchelle) const;
        Point operator*(qreal miseAEchelle) const;
        Point operator-(const Point& point) const;
        Point operator+(const Point& point) const;
        const Point& operator+=(const Point& point);
        const Point& operator-=(const Point& point);
        const Point& operator/=(qreal miseAEchelle);
        const Point& operator*=(qreal miseAEchelle);
        qreal operator*(const Point &point) const;
        bool operator<(const Point& point) const;
        bool operator==(const Point& point) const;

        // Angle par rapport à l'origine
        qreal angle(const bool retablirEntre0et360 = false) const;
        static qreal retablirEntre0et360(const qreal valeur);
        static qreal retablirEntre0et180(const qreal valeur);

        qreal norme() const;
        void normaliser();

        qreal mult(const Point &point) const;
        qreal multcroisee(const Point& point) const;

        // Angle entre 2 vecteurs (radians)
        static qreal angle(const Point &point1, const Point &point2);
        static qreal angleSigne(const Point& point1, const Point& point2);
        static qreal angleEntreDeuxPoints(const Point &point1, const Point &point2);
    };
}

#endif // POINT_H
