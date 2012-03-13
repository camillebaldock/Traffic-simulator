#ifndef DRIVER_H
#define DRIVER_H
#include <QString>
#include <QList>
#include "car.h"
#include "map.h"

using namespace Utils;

class DriverType
{
public:
  DriverType();
  QString m_Name;
  qreal m_VitesseVirage;
  qreal m_VitesseToutDroit;
};

class Driver
{
public:
  enum TypeObjectif
  {
    COORDONNEES,
    OBSTACLE,
    VOIE
  };

  Driver(const QString &nom);
  QString nom();
  Point destination();

  void ajouterCoordonnees(const Point &p);
  void ajouterCoordonnees(const QString &nomIntersection);
  void avancer();
  bool allerVers(const Point &objectif, const TypeObjectif TypeObjectif=COORDONNEES);
  void modifierCoordonnees();
  bool prevoirCollisions(Point &collision);
  void utiliser(Car *vehicule);
  bool verifierFeux(Point &coordonneesFeu);
  bool verifierVoie(Point &objectifVoie);

  bool m_ArretAuFeu;
  Point m_CoordonneesActuelles;
  Driver *m_Driver;
  bool m_CoordonneesModifiees;
  qreal m_DistanceJusquaObjectif;
  const Map::Intersection *m_DerniereIntersection;
  unsigned int m_IdVoieActuelle;
  Point m_ObjectifActuel;
  qreal m_ObjectifDirection;
  qreal m_ObjectifVitesse;
  qreal m_ObjectifVitesseVirage;
  qreal m_PositionVolantPrecedente;
  const Map::Road *m_RouteActuelle;
  Car *m_Vehicule;
  qreal m_VitesseParDefaut;
  Map::Road::Voie m_VoieActuelle;

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
    Coordonnees(const Map::Intersection *intersection, const Point &emplacement);
    const Map::Intersection *intersection;
    Point emplacement;
  };

  QList<Coordonnees> m_Chemin;
};

#endif // CONDUCTEUR_H
