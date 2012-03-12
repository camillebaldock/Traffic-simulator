#ifndef TESTPOINT_H
#define TESTPOINT_H
#include "point.h"
#include <QObject>
#include <QtTest/QTest>

class TestPoint: public QObject
{
    Q_OBJECT

    public:
        explicit TestPoint(QObject *parent = 0);

    private:
        Utils::Point *point1;
        Utils::Point *point2;
        Utils::Point *point3;
        Utils::Point *point4;

    private slots:
        void initTestCase();
        void testAngle();
        void testRetablirEntre0et360();
        void testRetablirEntre0et180();
        void testNorme();
        void testNormaliser();
        void testMult();
        void testMultCroisee();
        void testAngleSigne();
        void testAngleEntreDeuxPoints();
        void cleanupTestCase();
};

#endif // TESTPOINT_H
