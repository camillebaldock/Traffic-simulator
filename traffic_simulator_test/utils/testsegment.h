#ifndef TESTSEGMENT_H
#define TESTSEGMENT_H
#include "segment.h"
#include <QObject>
#include <QtTest/QTest>

class TestSegment: public QObject
{
    Q_OBJECT

    public:
        explicit TestSegment(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testVersPerpendiculaireDepuisDepart();
        void testVersPerpendiculaireDepuisFin();
        void testVersDecalage();
        void testPointLePlusProche();
        void testEstSur();
        void cleanupTestCase();
};

#endif // TESTSEGMENT_H
