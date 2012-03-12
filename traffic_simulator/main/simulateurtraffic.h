#ifndef SIMULATEURTRAFFIC_H
#define SIMULATEURTRAFFIC_H
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "simulation.h"

namespace Ui {
    class SimulateurTraffic;
}

class SimulateurTraffic : public QMainWindow {
    Q_OBJECT

public:
    explicit SimulateurTraffic(QWidget *parent = 0);
    ~SimulateurTraffic();

private:
  void miseAJourIHM();
  Ui::SimulateurTraffic *ui;
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

#endif // SIMULATEURTRAFFIC_H
