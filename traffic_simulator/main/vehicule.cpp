#include <qmath.h>
#include "vehicule.h"
#include "simulation.h"
#include "utils.h"


using namespace Utils;

Vehicule::Vehicule(const QString &nom, TypeVehicule *type)
{
  m_Nom = nom;
  m_Type = type;
  m_Empattement = 3.5f;
  m_Conducteur = NULL;
  m_Freinage = false;
  setDirection(0.0f);
  setMasse(1000.0f);
  setForceMoteur(9800);
}

Point Vehicule::acceleration()
{
  return m_Acceleration;
}

void Vehicule::setAcceleration(const Point &valeur)
{
  m_Acceleration = valeur;
}

void Vehicule::setDirection(const qreal angle)
{
  qreal nouvelAngle=angle;
  Point::retablirEntre0et180(nouvelAngle);
  nouvelAngle *= (M_PI/180.0);
  m_Direction.setX(qCos(nouvelAngle));
  m_Direction.setY(qSin(nouvelAngle));
}

void Vehicule::setDirection(const Point &valeur)
{
  Point normalise = valeur;
  normalise.normaliser();
  m_Direction = normalise;
}

Point Vehicule::direction()
{
  return m_Direction;
}

void Vehicule::setEmpattement(const qreal valeur)
{
  m_Empattement = valeur;
}

qreal Vehicule::empattement()
{
  return m_Empattement;
}

void Vehicule::setEmplacement(const Point &valeur)
{
  m_Emplacement = valeur;
}

Point Vehicule::emplacement()
{
  return m_Emplacement;
}

void Vehicule::setForceMoteur(const qreal valeur)
{
  m_AccelerationMax = valeur;
}

void Vehicule::setMasse(const qreal valeur)
{
  m_Masse = valeur;
}

QString Vehicule::nom()
{
  return m_Nom;
}

void Vehicule::setType(TypeVehicule *type)
{
  m_Type = type;
}

TypeVehicule* Vehicule::type()
{
  return m_Type;
}

void Vehicule::setVelocite(const Point &valeur)
{
  if(valeur.norme() < .001)
    m_Velocite = Point(0,0);
  else
    m_Velocite = valeur;
}

Point Vehicule::velocite()
{
  return m_Velocite;
}

qreal Vehicule::vitesse(bool kmh)
{
  if(kmh)
    return (m_Velocite.norme()*MPS_A_KMH);
  else
    return m_Velocite.norme();
}

void Vehicule::forces(Point &moteur, Point &frottements)
{
  moteur = m_ForceMoteur;
  frottements = m_ForceFrottements;
}

void Vehicule::setConducteur(Conducteur *conducteur)
{
  m_Conducteur = conducteur;
}

Conducteur* Vehicule::conducteur()
{
  return m_Conducteur;
}

qreal Vehicule::tpsJusquaVitesse(const qreal vitesseKmh)
{
  qreal diffVitesse = (vitesse(true)-vitesseKmh) * KMH_A_MPS;
  return ( (diffVitesse / (m_AccelerationMax))*m_Masse );
}

qreal Vehicule::distanceJusquaVitesse(const qreal vitesseKmh)
{
  qreal secs = tpsJusquaVitesse(vitesseKmh);
  return ( 0.50 * m_Velocite.norme() * (secs-(Simulation::m_PasSimulation*3)) ) * UNIT_PAR_METRE;
}

// -1 = gauche, +1 = droite
void Vehicule::tournervolant(qreal valeur)
{
  if (valeur<-1.0)
    valeur = -1.0;
  else if (valeur>1.0)
    valeur = 1.0;

  m_AngleVolant = valeur;

}

// 0 = pas de frein, 1 = frein complètement enfoncé
void Vehicule::freiner(qreal valeur)
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
void Vehicule::accelerer(qreal valeur)
{
  if (valeur<0)
    valeur = 0;
  else if (valeur>1.0)
    valeur = 1.0;
  m_ForceMoteur = m_Direction * (valeur * m_AccelerationMax);
}

void Vehicule::avancer()
{
  miseAJourForces();
  miseAJourAcceleration();
  miseAJourVelocite();
  miseAJourDirection();
  miseAJourEmplacement();
}


void Vehicule::miseAJourAcceleration()
{
  Point force = m_ForceMoteur + m_ForceFrottements;
  setAcceleration((force / m_Masse));
}

void Vehicule::miseAJourDirection()
{
  float rayonVirage = m_Empattement / sin(m_AngleVolant * M_PI / 3);
  float vitesseAngulaire = (m_Velocite.norme()*UNIT_PAR_METRE) / (rayonVirage);
  setDirection(m_Direction.angle() + vitesseAngulaire * Simulation::m_PasSimulation * 180 / M_PI);
}

void Vehicule::miseAJourForces()
{
  if(m_Freinage)
    m_ForceFrottements = m_Direction * (-m_AccelerationMax);
  else
    m_ForceFrottements = Point();
}

void Vehicule::miseAJourEmplacement()
{
  setEmplacement(m_Emplacement + m_Velocite * UNIT_PAR_METRE * Simulation::m_PasSimulation);
}

void Vehicule::miseAJourVelocite()
{
  setVelocite((m_Direction * m_Velocite.norme()) + m_Acceleration * Simulation::m_PasSimulation);
  if (qAbs(m_Velocite.angle(true) - m_Direction.angle(true)) >= 90.0f)
    setVelocite(Point());
}
