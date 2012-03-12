#ifndef CONDUCTEUR_H
#define CONDUCTEUR_H
#include <QString>
#include <QList>
#include "vehicule.h"
#include "plan.h"

using namespace Utils;

class TypeConducteur
{
public:
  TypeConducteur();
  QString m_Nom;
  qreal m_VitesseVirage;
  qreal m_VitesseToutDroit;
};

class Conducteur
{
public:
  enum TypeObjectif
  {
    COORDONNEES,
    OBSTACLE,
    VOIE
  };

  Conducteur(const QString &nom);
  QString nom();
  Point destination();

  void ajouterCoordonnees(const Point &p);
  void ajouterCoordonnees(const QString &nomIntersection);
  void avancer();
  bool allerVers(const Point &objectif, const TypeObjectif TypeObjectif=COORDONNEES);
  void modifierCoordonnees();
  bool prevoirCollisions(Point &collision);
  void utiliser(Vehicule *vehicule);
  bool verifierFeux(Point &coordonneesFeu);
  bool verifierVoie(Point &objectifVoie);

  bool m_ArretAuFeu;
  Point m_CoordonneesActuelles;
  Conducteur *m_Conducteur;
  bool m_CoordonneesModifiees;
  qreal m_DistanceJusquaObjectif;
  const Plan::Intersection *m_DerniereIntersection;
  unsigned int m_IdVoieActuelle;
  Point m_ObjectifActuel;
  qreal m_ObjectifDirection;
  qreal m_ObjectifVitesse;
  qreal m_ObjectifVitesseVirage;
  qreal m_PositionVolantPrecedente;
  const Plan::Route *m_RouteActuelle;
  Vehicule *m_Vehicule;
  qreal m_VitesseParDefaut;
  Plan::Route::Voie m_VoieActuelle;

private:
  void conduire(bool urgent);
  Point m_Destination;
  bool m_DestinationAtteinte;
  QString m_Nom;
  bool m_VirageBientot;
  qreal m_VitesseViragePrecedente;

  class Coordonnees
  {
  public:
    Coordonnees(const Plan::Intersection *intersection, const Point &emplacement);
    const Plan::Intersection *intersection;
    Point emplacement;
  };

  QList<Coordonnees> m_Chemin;
};

#endif // CONDUCTEUR_H
