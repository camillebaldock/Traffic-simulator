#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include <QList>
#include <QMap>
#include <QTime>
#include "gestionnaireimages.h"
#include "map.h"
#include "car.h"
#include "driver.h"
class QGraphicsItem;
class TrafficLights;

class Simulation : public QThread
{
public:

  static Simulation* instance();
  static bool supprimerInstance();
  virtual void executer();
  void ouvrirFichierXMLPlan(const QString &nomFichier);
  void effacerPlan();
  void ouvrirFichierXMLTypes(const QString &nomFichier);
  void ouvrirFichierXMLSimulation(const QString &nomFichier);
  QString ouvrirFichierXMLSignalisation(const QString &nomFichier);
  void rafraichirSimulation();

  void setFinSimulation(bool fin);
  bool finSimulation();
  void avancer();
  void ajouterVehicule(Car *v);
  Car* ajouterVehicule(const QString &nom, const QString &nom_TypeVehicule);
  Car* trouverVehicule(const QString &nom);
  void ajouterConducteur(Driver *c);
  Driver* ajouterConducteur(const QString &nom, const QString &nom_TypeConducteur);
  Driver* trouverConducteur(const QString &nom);
  static qreal m_PasSimulation;
  static QTime m_TpsSimulation;
  QList<CarType*> m_TypesVehicule;
  QList<DriverType*> m_TypesConducteur;
  QList<Car*> m_Vehicules;
  QList<Driver*> m_Drivers;
  QMap<const Map::Intersection*, TrafficLights*> m_Signalisations;
  Map *m_Plan;
  GestionnaireImages m_GestionnaireImages;

private:
  Simulation();
  ~Simulation();

  static Simulation *m_Instance;

  bool m_SimulationEnCours;
  bool m_FinSimulation;
  QString m_FichierSimulation;
  QString m_FichierPlan;
  QString m_FichierSignalisation;
  unsigned int m_NbTotalPas;
};

#endif
