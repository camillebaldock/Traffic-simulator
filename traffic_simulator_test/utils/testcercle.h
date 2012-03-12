#ifndef TESTCERCLE_H
#define TESTCERCLE_H
#include "cercle.h"
#include <QObject>
#include <QtTest/QTest>

class TestCercle: public QObject
{
    Q_OBJECT
    public:
        explicit TestCercle(QObject *parent = 0);

    private:
        Utils::Cercle *c1;
        Utils::Cercle *c2;

    private slots:
            void initTestCase();
            void testRayon();
            void cleanupTestCase();
};
#endif
