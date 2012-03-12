#ifndef TESTCONDUCTEUR_H
#define TESTCONDUCTEUR_H
#include <QObject>
#include <QtTest/QTest>
#include "conducteur.h"

class TestConducteur: public QObject
{
    Q_OBJECT

    public:
        explicit TestConducteur(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testAllerVers();
        void testConduire();
        void testPrevoirCollisions();
        void testVerifierVoie();
        void testVerifierFeux();
        void testModifierCoordonnees();
        void testAvancer();
        void cleanupTestCase();
};

#endif // TESTCONDUCTEUR_H
