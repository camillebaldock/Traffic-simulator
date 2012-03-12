#ifndef VEHICULE_H
#define VEHICULE_H

#include <QList>
#include <QTime>
#include <QString>

#include "point.h"
class Conducteur;

using namespace Utils;

class TypeVehicule
{
public:
  qreal m_Empattement;
  qreal m_ForceMoteur;
  qreal m_Masse;
  QString m_Nom;
  QString m_NomImage;

};

class Vehicule
{
public:
  enum TypeActionConducteur
  {
    ACCELERER,
    FREINER,
    TOURNER
  };

  struct ActionConducteur
  {
    TypeActionConducteur action;
    qreal valeur;
    QTime heure;
  };

  Vehicule(const QString &nom, TypeVehicule *type=0);
  void setAcceleration(const Point &valeur);
  Point acceleration();
  void setDirection(const qreal angle);
  void setDirection(const Point &valeur);
  Point direction();
  qreal distanceJusquaVitesse(const qreal vitesseKmh = 0.0);
  void setEmplacement(const Point &valeur);
  Point emplacement();
  void setEmpattement(const qreal valeur);
  qreal empattement();
  void forces(Point &engine, Point &frottements);
  void setForceMoteur(const qreal valeur);
  void setMasse(const qreal valeur);
  QString nom();
  TypeVehicule* type();
  void setType(TypeVehicule *type);
  void setVelocite(const Point &valeur);
  Point velocite();
  qreal vitesse( bool kmh = false );
  qreal tpsJusquaVitesse(const qreal vitesseKmh = 0.0);

  Conducteur* conducteur();
  void setConducteur(Conducteur* c);
  void accelerer(qreal valeur);
  void avancer();
  void freiner(qreal valeur);
  void tournervolant(qreal valeur);

private:

  void miseAJourAcceleration();
  void miseAJourDirection();
  void miseAJourEmplacement();
  void miseAJourForces();
  void miseAJourVelocite();

  Point m_Acceleration;
  qreal m_AccelerationMax;
  float m_AngleVolant;
  Point m_Direction;
  Point m_Emplacement;
  Point m_ForceFrottements;
  Point m_ForceMoteur;
  float m_Empattement;
  bool m_Freinage;
  float m_Masse;
  QString m_Nom;
  Point m_Velocite;

  Conducteur *m_Conducteur;
  TypeVehicule *m_Type;
};

#endif // VEHICULE_H
