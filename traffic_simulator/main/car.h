#ifndef CAR_H
#define CAR_H

#include <QList>
#include <QTime>
#include <QString>

#include "point.h"
class Driver;

using namespace Utils;

class CarType
{
public:
  qreal m_Empattement;
  qreal m_ForceMoteur;
  qreal m_Masse;
  QString m_Nom;
  QString m_NomImage;

};

class Car
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

  Car(const QString &nom, CarType *type=0);
  void setAcceleration(const Point &valeur);
  Point acceleration();
  void setDirection(const qreal angle);
  void setDirection(const Point &valeur);
  Point direction();
  qreal distanceToSpeed(const qreal vitesseKmh = 0.0);
  void setPosition(const Point &valeur);
  Point position();
  void setEmpattement(const qreal valeur);
  qreal empattement();
  void forces(Point &engine, Point &frottements);
  void setForceMoteur(const qreal valeur);
  void setWeight(const qreal valeur);
  QString nom();
  CarType* type();
  void setType(CarType *type);
  void setVelocity(const Point &valeur);
  Point velocity();
  qreal vitesse( bool kmh = false );
  qreal tpsJusquaVitesse(const qreal vitesseKmh = 0.0);

  Driver* driver();
  void setConducteur(Driver* c);
  void accelerate(qreal valeur);
  void avancer();
  void decelerate(qreal valeur);
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
  Point m_Position;
  Point m_ForceFrottements;
  Point m_ForceMoteur;
  float m_Empattement;
  bool m_Freinage;
  float m_Masse;
  QString m_Name;
  Point m_Velocity;

  Driver *m_Driver;
  CarType *m_Type;
};

#endif // CAR_H
