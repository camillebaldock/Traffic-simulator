#ifndef TESTSIGNALISATION_H
#define TESTSIGNALISATION_H
#include <QObject>
#include <QtTest/QTest>
#include "signalisation.h"

class TestSignalisation: public QObject
{
    Q_OBJECT

    public:
        explicit TestSignalisation(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testAvancer();
        void cleanupTestCase();
};

#endif // TESTSIGNALISATION_H
