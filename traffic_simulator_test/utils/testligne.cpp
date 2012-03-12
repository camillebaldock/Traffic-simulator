#include "testligne.h"
#include <QDebug>

TestLigne::TestLigne(QObject *parent) :
    QObject(parent)
{}

void TestLigne::initTestCase()
{
    origine = new Utils::Point(0,0);
    point1 = new Utils::Point(0,1);
    point2 = new Utils::Point(1,0);
    ligneVerticale = new Utils::Ligne(*origine, *point1);
    ligneHorizontale = new Utils::Ligne(*origine, *point2);
}

void TestLigne::testEstVertical() {
    QCOMPARE(ligneVerticale->estVertical(), true);
    QCOMPARE(ligneHorizontale->estVertical(),false);
}

void TestLigne::testEstHorizontal(){
    QCOMPARE(ligneVerticale->estHorizontal(), false);
    QCOMPARE(ligneHorizontale->estHorizontal(),true);
}

void TestLigne::cleanupTestCase()
{
    delete ligneVerticale;
    delete ligneHorizontale;
    delete origine;
    delete point1;
    delete point2;
}
