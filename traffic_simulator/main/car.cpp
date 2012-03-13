#include <qmath.h>
#include "car.h"
#include "simulation.h"
#include "utils.h"


using namespace Utils;

Car::Car(const QString &nom, CarType *type)
{
  m_Name = nom;
  m_Type = type;
  m_Empattement = 3.5f;
  m_Driver = NULL;
  m_Freinage = false;
  setDirection(0.0f);
  setWeight(1000.0f);
  setForceMoteur(9800);
}

Point Car::acceleration()
{
  return m_Acceleration;
}

void Car::setAcceleration(const Point &valeur)
{
  m_Acceleration = valeur;
}

void Car::setDirection(const qreal angle)
{
  qreal nouvelAngle=angle;
  Point::retablirEntre0et180(nouvelAngle);
  nouvelAngle *= (M_PI/180.0);
  m_Direction.setX(qCos(nouvelAngle));
  m_Direction.setY(qSin(nouvelAngle));
}

void Car::setDirection(const Point &valeur)
{
  Point normalise = valeur;
  normalise.normaliser();
  m_Direction = normalise;
}

Point Car::direction()
{
  return m_Direction;
}

void Car::setEmpattement(const qreal valeur)
{
  m_Empattement = valeur;
}

qreal Car::empattement()
{
  return m_Empattement;
}

void Car::setPosition(const Point &valeur)
{
  m_Position = valeur;
}

Point Car::position()
{
  return m_Position;
}

void Car::setForceMoteur(const qreal valeur)
{
  m_AccelerationMax = valeur;
}

void Car::setWeight(const qreal valeur)
{
  m_Masse = valeur;
}

QString Car::nom()
{
  return m_Name;
}

void Car::setType(CarType *type)
{
  m_Type = type;
}

CarType* Car::type()
{
  return m_Type;
}

void Car::setVelocity(const Point &valeur)
{
  if(valeur.norme() < .001)
    m_Velocity = Point(0,0);
  else
    m_Velocity = valeur;
}

Point Car::velocity()
{
  return m_Velocity;
}

qreal Car::vitesse(bool kmh)
{
  if(kmh)
    return (m_Velocity.norme()*MPS_A_KMH);
  else
    return m_Velocity.norme();
}

void Car::forces(Point &moteur, Point &frottements)
{
  moteur = m_ForceMoteur;
  frottements = m_ForceFrottements;
}

void Car::setConducteur(Driver *conducteur)
{
  m_Driver = conducteur;
}

Driver* Car::driver()
{
  return m_Driver;
}

qreal Car::tpsJusquaVitesse(const qreal vitesseKmh)
{
  qreal diffVitesse = (vitesse(true)-vitesseKmh) * KMH_A_MPS;
  return ( (diffVitesse / (m_AccelerationMax))*m_Masse );
}

qreal Car::distanceToSpeed(const qreal vitesseKmh)
{
  qreal secs = distanceToSpeed(vitesseKmh);
  return ( 0.50 * m_Velocity.norme() * (secs-(Simulation::m_PasSimulation*3)) ) * UNIT_PAR_METRE;
}

// -1 = gauche, +1 = droite
void Car::tournervolant(qreal valeur)
{
  if (valeur<-1.0)
    valeur = -1.0;
  else if (valeur>1.0)
    valeur = 1.0;

  m_AngleVolant = valeur;

}

// 0 = pas de frein, 1 = frein complètement enfoncé
void Car::decelerate(qreal valeur)
{
  if (valeur<0.0f)
    valeur = 0.0f;
  else if (valeur>1.0f)
    valeur = 1.0f;
  m_Freinage = (valeur > 0.0f);
}

/**
  * 0 = pas d'accélération, 1 = accélérateur complètement appuyé
  */
void Car::accelerate(qreal valeur)
{
  if (valeur<0)
    valeur = 0;
  else if (valeur>1.0)
    valeur = 1.0;
  m_ForceMoteur = m_Direction * (valeur * m_AccelerationMax);
}

void Car::avancer()
{
  miseAJourForces();
  miseAJourAcceleration();
  miseAJourVelocite();
  miseAJourDirection();
  miseAJourEmplacement();
}


void Car::miseAJourAcceleration()
{
  Point force = m_ForceMoteur + m_ForceFrottements;
  setAcceleration((force / m_Masse));
}

void Car::miseAJourDirection()
{
  float rayonVirage = m_Empattement / sin(m_AngleVolant * M_PI / 3);
  float vitesseAngulaire = (m_Velocity.norme()*UNIT_PAR_METRE) / (rayonVirage);
  setDirection(m_Direction.angle() + vitesseAngulaire * Simulation::m_PasSimulation * 180 / M_PI);
}

void Car::miseAJourForces()
{
  if(m_Freinage)
    m_ForceFrottements = m_Direction * (-m_AccelerationMax);
  else
    m_ForceFrottements = Point();
}

void Car::miseAJourEmplacement()
{
  setPosition(m_Position + m_Velocity * UNIT_PAR_METRE * Simulation::m_PasSimulation);
}

void Car::miseAJourVelocite()
{
  setVelocity((m_Direction * m_Velocity.norme()) + m_Acceleration * Simulation::m_PasSimulation);
  if (qAbs(m_Velocity.angle(true) - m_Direction.angle(true)) >= 90.0f)
    setVelocity(Point());
}
