#include <QtGui/QApplication>
#include <QResource>
#include "trafficsimulator.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TrafficSimulator simulateur;
    simulateur.show();
    return a.exec();
}
