#include "testcercle.h"

TestCercle::TestCercle(QObject *parent) :
    QObject(parent)
{}

void TestCercle::initTestCase()
{
    c1 = new Utils::Cercle();
    c2 = new Utils::Cercle(0,0,1);
}

void TestCercle::testRayon()
{
    QCOMPARE(c1->rayon(), 0.0);
    QCOMPARE(c2->rayon(), 1.0);
}

void TestCercle::cleanupTestCase()
{
    delete c1;
    delete c2;
}
