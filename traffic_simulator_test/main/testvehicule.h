#ifndef TESTVEHICULE_H
#define TESTVEHICULE_H
#include <QObject>
#include <QtTest/QTest>
#include "vehicule.h"

class TestVehicule: public QObject
{
    Q_OBJECT

    public:
        explicit TestVehicule(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testAccelerer();
        void testAvancer();
        void testFreiner();
        void testTournervolant();
        void testMiseAJourAcceleration();
        void testMiseAJourDirection();
        void testMiseAJourEmplacement();
        void testMiseAJourForces();
        void testMiseAJourVelocite();

        void cleanupTestCase();
};

#endif // TESTVEHICULE_H
