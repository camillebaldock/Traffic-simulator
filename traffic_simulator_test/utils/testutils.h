#ifndef TESTUTILS_H
#define TESTUTILS_H
#include "utils.h"
#include <QObject>
#include <QtTest/QTest>

class TestUtils: public QObject
{
    Q_OBJECT

    public:
        explicit TestUtils(QObject *parent = 0);

    private:
        Utils::Point *point1;
        Utils::Point *point2;
        Utils::Point *point3;
        Utils::Point *point4;
        Utils::Point *point5;
        Utils::Point *point6;
        Utils::Ligne *ligne1;
        Utils::Ligne *ligne2;
        Utils::Ligne *ligne3;
        Utils::Vecteur *vecteur1;
        Utils::Vecteur *vecteur2;
        Utils::Vecteur *vecteur3;
        Utils::Segment *segment1;
        Utils::Segment *segment2;
        Utils::Segment *segment3;
        Utils::Segment *segment4;

    private slots:
        void initTestCase();
        void testPresqueEgal();
        void testInterLigneLigne();
        void testInterVecteurVecteur();
        void testInterSegmentSegment();
        void testInterVecteurRectangle();
        void cleanupTestCase();
};


#endif // TESTUTILS_H
