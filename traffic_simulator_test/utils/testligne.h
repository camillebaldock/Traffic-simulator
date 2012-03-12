#ifndef TESTLIGNE_H
#define TESTLIGNE_H
#include "ligne.h"
#include "point.h"
#include <QObject>
#include <QtTest/QTest>

class TestLigne: public QObject
{
    Q_OBJECT

    public:
        explicit TestLigne(QObject *parent = 0);

    private:
        Utils::Ligne *ligneVerticale;
        Utils::Ligne *ligneHorizontale;
        Utils::Point *origine;
        Utils::Point *point1;
        Utils::Point *point2;

    private slots:
        void initTestCase();
        void testEstVertical();
        void testEstHorizontal();
        void cleanupTestCase();
};
#endif
