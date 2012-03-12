#ifndef TESTSIMULATEURTRAFFIC_H
#define TESTSIMULATEURTRAFFIC_H
#include <QObject>
#include <QtTest/QTest>
#include "simulateurtraffic.h"

class TestSimulateurTraffic: public QObject
{
    Q_OBJECT

    public:
        explicit TestSimulateurTraffic(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void cleanupTestCase();
};

#endif // TESTSIMULATEURTRAFFIC_H
