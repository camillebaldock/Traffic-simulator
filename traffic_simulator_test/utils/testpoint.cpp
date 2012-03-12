#include "testpoint.h"
#include "cmath"

TestPoint::TestPoint(QObject *parent) :
    QObject(parent)
{}

void TestPoint::initTestCase(){
    point1 = new Utils::Point(0,1);
    point2 = new Utils::Point(1,0);
    point3 = new Utils::Point(1,2);
    point4 = new Utils::Point(1/sqrt(5),2/sqrt(5));
}

void TestPoint::testAngle(){
    QCOMPARE(point1->angle(),90.0);
}

void TestPoint::testRetablirEntre0et360(){
    QCOMPARE(Utils::Point::retablirEntre0et360(375.0),15.0);
    QCOMPARE(Utils::Point::retablirEntre0et360(240.0),240.0);
    QCOMPARE(Utils::Point::retablirEntre0et360(-5.0),355.0);
}

void TestPoint::testRetablirEntre0et180(){
    QCOMPARE(Utils::Point::retablirEntre0et180(375.0),15.0);
    QCOMPARE(Utils::Point::retablirEntre0et180(40.0),40.0);
}

void TestPoint::testNorme(){
    QCOMPARE(point1->norme(),1.0);
    QCOMPARE(point3->norme(), sqrt(5.0));
}

void TestPoint::testNormaliser(){
    point3->normaliser();
    QCOMPARE(point3->norme(), 1.0);
}

void TestPoint::testMult(){
    QCOMPARE(point1->mult(*point2),0.0);
}

void TestPoint::testMultCroisee(){
    QCOMPARE(point1->multcroisee(*point2),-1.0);
}

void TestPoint::testAngleSigne(){
    QCOMPARE(Utils::Point::angleSigne(*point1,*point2),atan2(-1.0, 0.0));
}

void TestPoint::testAngleEntreDeuxPoints(){
    QCOMPARE(Utils::Point::angleEntreDeuxPoints(*point1, *point2), -45.0);
}

void TestPoint::cleanupTestCase(){
    delete point1;
    delete point2;
    delete point3;
    delete point4;
}
