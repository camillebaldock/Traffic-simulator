#include <QtGui/QApplication>
#include <QResource>
#include "simulateurtraffic.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SimulateurTraffic simulateur;
    simulateur.show();
    return a.exec();
}
