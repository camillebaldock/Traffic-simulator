#ifndef TESTPLAN_H
#define TESTPLAN_H
#include <QObject>
#include <QtTest/QTest>
#include "plan.h"

class TestPlan: public QObject
{
    Q_OBJECT

    public:
        explicit TestPlan(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testPlan();
        void cleanupTestCase();
};

#endif // TESTPLAN_H
