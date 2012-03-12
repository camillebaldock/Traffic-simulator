#include "testutils.h"
#include <QDebug>

TestUtils::TestUtils(QObject *parent) :
    QObject(parent)
{}

void TestUtils::initTestCase(){
    point1 = new Utils::Point(0.0, 1.0);
    point2 = new Utils::Point(-3.0, 0.0);
    point3 = new Utils::Point(2.0, 0.0);
    point4 = new Utils::Point(-1.0, 0.0);
    point5 = new Utils::Point(-1.0, 1.0);
    point6 = new Utils::Point(1.0, -1.0);
    ligne1 = new Utils::Ligne(1.0, -3.0);
    ligne2 = new Utils::Ligne(-4.0, 2.0);
    ligne3 = new Utils::Ligne(0.0, -3.0);
    vecteur1 = new Utils::Vecteur(*point1, *point2);
    vecteur2 = new Utils::Vecteur(*point1, *point3);
    vecteur3 = new Utils::Vecteur(*point3, *point2);
    segment1 = new Utils::Segment(*point1, *point2);
    segment2 = new Utils::Segment(*point3, *point4);
    segment3 = new Utils::Segment(*point1, *point3);
    segment4 = new Utils::Segment(*point2, *point4);
}

void TestUtils::testPresqueEgal(){
    QCOMPARE(Utils::presqueEgal(0.6,0.5,0.1), true);
    QCOMPARE(Utils::presqueEgal(0.6,0.5,0.01), false);
}

void TestUtils::testInterLigneLigne(){
    Utils::InfoIntersection info;
    Utils::InterLigneLigne(*ligne1, *ligne2, info);
    QCOMPARE(info, Utils::INTERSECTION);
    Utils::InterLigneLigne(*ligne1, *ligne3, info);
    QCOMPARE(info, Utils::PARALLELE);
    Utils::InterLigneLigne(*ligne1, *ligne1, info);
    QCOMPARE(info, Utils::COINCIDENT);
}

void TestUtils::testInterVecteurVecteur(){
    Utils::InfoIntersection info;
    Utils::InterVecteurVecteur(*vecteur1, *vecteur2, info);
    QCOMPARE(info, Utils::PAS_INTERSECTION);
    Utils::InterVecteurVecteur(*vecteur1, *vecteur3, info);
    QCOMPARE(info, Utils::INTERSECTION);
}

void TestUtils::testInterSegmentSegment(){
    Utils::InfoIntersection info;
    Utils::InterSegmentSegment(*segment1, *segment2, info);
    QCOMPARE(info, Utils::INTERSECTION);
    Utils::InterSegmentSegment(*segment3, *segment4, info);
    QCOMPARE(info, Utils::PAS_INTERSECTION);
}

void TestUtils::testInterVecteurRectangle(){
    QRect rectangle = QRect(point5->toPoint(), point6->toPoint());
    Utils::InfoIntersection info;
    Utils::Point pts[2];
    Utils::InterVecteurRectangle(*vecteur3, rectangle, pts, info);
    QCOMPARE(info, Utils::INTERSECTION);
    QCOMPARE(pts[0].angle(), point1->angle());
}

void TestUtils::cleanupTestCase(){
    delete point1;
    delete point2;
    delete point3;
    delete point4;
    delete ligne1;
    delete ligne2;
    delete ligne3;
    delete vecteur1;
    delete vecteur2;
    delete vecteur3;
    delete segment1;
    delete segment2;
    delete segment3;
    delete segment4;
}
