#ifndef TESTVECTEUR_H
#define TESTVECTEUR_H
#include "vecteur.h"
#include <QObject>
#include <QtTest/QTest>

class TestVecteur: public QObject
{
    Q_OBJECT

    public:
        explicit TestVecteur(QObject *parent = 0);

    private:

    private slots:
        void initTestCase();
        void testEstSur();
        void cleanupTestCase();
};


#endif // TESTVECTEUR_H
