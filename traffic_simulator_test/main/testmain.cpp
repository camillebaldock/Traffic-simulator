#include <QtTest/QtTest>
#include "testligne.h"
#include "testpoint.h"
#include "testsegment.h"
#include "testutils.h"
#include "testvecteur.h"
#include "testplan.h"
#include "testsignalisation.h"
#include "testconducteur.h"
#include "testsimulation.h"
#include "testvehicule.h"

int main()
{
    TestLigne testLigne;
    QTest::qExec(&testLigne);
    TestPoint testPoint;
    QTest::qExec(&testPoint);
    TestSegment testSegment;
    QTest::qExec(&testSegment);
    TestUtils testUtils;
    QTest::qExec(&testUtils);
    TestVecteur testVecteur;
    QTest::qExec(&testVecteur);
    TestConducteur testConducteur;
    QTest::qExec(&testConducteur);
    TestPlan testPlan;
    QTest::qExec(&testPlan);
    TestSignalisation testSignalisation;
    QTest::qExec(&testSignalisation);
    TestSimulation testSimulation;
    QTest::qExec(&testSimulation);
    TestVehicule testVehicule;
    QTest::qExec(&testVehicule);
    return 0;
}
