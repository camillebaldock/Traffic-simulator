#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "simulation.h"

namespace Ui {
    class TrafficSimulator;
}

class TrafficSimulator : public QMainWindow {
    Q_OBJECT

public:
    explicit TrafficSimulator(QWidget *parent = 0);
    ~TrafficSimulator();

private:
  void miseAJourIHM();
  Ui::TrafficSimulator *ui;
  Simulation *m_Simulation;
  QTimer *m_Horloge;
  bool m_SimTpsReel;
  bool m_EnCoursDeLecture;

public slots:
  void OnAfficherVelocite(bool afficher);
  void OnAfficherForceMoteur(bool afficher);
  void OnAfficherFrottements(bool afficher);
  void OnHorloge();
  void OnLectureArretSimulation();
  void OnOuvertureSimulation();
  void OnReglageVitesseSim(int vitesse);
  void OnZoomArriere();
  void OnZoomAvant();
};

#endif // TRAFFICSIMULATOR_H
