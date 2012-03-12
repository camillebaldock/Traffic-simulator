#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include <QList>
#include <QMap>
#include <QTime>
#include "gestionnaireimages.h"
#include "plan.h"
#include "vehicule.h"
#include "conducteur.h"
class QGraphicsItem;
class Signalisation;

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
  void ajouterVehicule(Vehicule *v);
  Vehicule* ajouterVehicule(const QString &nom, const QString &nom_TypeVehicule);
  Vehicule* trouverVehicule(const QString &nom);
  void ajouterConducteur(Conducteur *c);
  Conducteur* ajouterConducteur(const QString &nom, const QString &nom_TypeConducteur);
  Conducteur* trouverConducteur(const QString &nom);
  static qreal m_PasSimulation;
  static QTime m_TpsSimulation;
  QList<TypeVehicule*> m_TypesVehicule;
  QList<TypeConducteur*> m_TypesConducteur;
  QList<Vehicule*> m_Vehicules;
  QList<Conducteur*> m_Conducteurs;
  QMap<const Plan::Intersection*, Signalisation*> m_Signalisations;
  Plan *m_Plan;
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
