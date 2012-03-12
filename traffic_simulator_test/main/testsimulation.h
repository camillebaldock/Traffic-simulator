#ifndef TESTSIMULATION_H
#define TESTSIMULATION_H
#include <QObject>
#include <QtTest/QTest>
#include "simulation.h"

class TestSimulation: public QObject
{
    Q_OBJECT

    public:
        explicit TestSimulation(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testOuvrirFichierXMLTypes();
        void testOuvrirFichierXMLSimulation();
        void testOuvrirFichierXMLSignalisation();
        void cleanupTestCase();
};

#endif // TESTSIMULATION_H
