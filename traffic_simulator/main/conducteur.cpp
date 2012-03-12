#include "conducteur.h"
#include "simulation.h"
#include "plan.h"
#include "signalisation.h"
#include "Utils.h"
#include <qmath.h>

using namespace Utils;

TypeConducteur::TypeConducteur(){}


Conducteur::Coordonnees::Coordonnees(const Plan::Intersection *intersection, const Point &emplacement)
  : intersection(intersection), emplacement(emplacement) {}


Conducteur::Conducteur(const QString &nom)
{
  m_ArretAuFeu = false;
  m_CoordonneesModifiees = false;
  m_DerniereIntersection = NULL;
  m_DestinationAtteinte = true;
  m_DistanceJusquaObjectif = 0;
  m_IdVoieActuelle = 0;
  m_Conducteur = NULL;
  m_Nom = nom;
  m_ObjectifDirection = 0;
  m_ObjectifVitesse = 0;
  m_ObjectifVitesseVirage = 25;
  m_PositionVolantPrecedente =0;
  m_RouteActuelle = NULL;
  m_VirageBientot = false;
  m_VitesseParDefaut = 35.0;
  m_VitesseViragePrecedente = 0.0;
}

QString Conducteur::nom()
{
  return m_Nom;
}

void Conducteur::utiliser(Vehicule *vehicule)
{
  m_Vehicule = vehicule;
  if (m_Vehicule)
    m_Vehicule->setConducteur(this);
}

Point Conducteur::destination()
{
  return (m_Chemin.isEmpty()) ? Point() : m_Chemin.last().emplacement;
}

void Conducteur::ajouterCoordonnees(const Point &p)
{
  m_Chemin.push_back(Coordonnees(NULL,p));
  m_Destination = p;
}

void Conducteur::ajouterCoordonnees(const QString &nomIntersection)
{
  Simulation *simu = Simulation::instance();
  const Plan::Intersection *i = simu->m_Plan->getIntersection(nomIntersection);
  if (i)
  {
    m_Chemin.push_back(Coordonnees(i, i->emplacement()));
    m_Destination = i->emplacement();
  }
}

bool Conducteur::allerVers(const Point &objectif, const TypeObjectif typeObjectif)
{
  if (!m_Vehicule || m_DestinationAtteinte)
   return false;

  bool ret = false;
  m_ObjectifActuel = objectif;
  m_DistanceJusquaObjectif = (m_ObjectifActuel - m_Vehicule->emplacement()).norme() * METRE_PAR_UNIT;
  m_ObjectifDirection = Point::angleEntreDeuxPoints(m_Vehicule->emplacement(), m_ObjectifActuel);
  qreal urgent = false;

  if (typeObjectif == COORDONNEES)
  {
    if (m_VitesseViragePrecedente > 0.0)
    {
      m_ObjectifVitesse = m_VitesseViragePrecedente;
    }
    else
    {
      // Recalculer la vitesse
      Point prochain;
      if (m_Chemin.size()==1)
      {
        m_VirageBientot = true;
      }
      else
      {
        prochain = m_Chemin.at(1).emplacement;
        qreal angle = Point::angleEntreDeuxPoints(m_ObjectifActuel, prochain);
        qreal diffAngle = qAbs(Point::retablirEntre0et180(angle - m_Vehicule->direction().angle()));
        m_VirageBientot = (diffAngle > 20.0);
      }

      qreal distanceJusquaVitesseVirageVoulue = m_Vehicule->distanceJusquaVitesse(m_ObjectifVitesseVirage);
      if (m_DistanceJusquaObjectif < (30.0*METRE_PAR_UNIT))
      {
        m_ObjectifVitesse = (m_VirageBientot) ? m_ObjectifVitesseVirage : m_VitesseParDefaut;
        m_VitesseViragePrecedente = (m_VirageBientot) ? m_ObjectifVitesseVirage : m_VitesseParDefaut;
      }
      else if (m_DistanceJusquaObjectif <= distanceJusquaVitesseVirageVoulue)
      {
        m_ObjectifVitesse = (m_VirageBientot) ? m_ObjectifVitesseVirage : m_VitesseParDefaut;
        m_VitesseViragePrecedente = (m_VirageBientot) ? m_ObjectifVitesseVirage : m_VitesseParDefaut;
      }
      else
      {
        m_ObjectifVitesse = m_VitesseParDefaut;
      }
    }
  }
  else if (typeObjectif == OBSTACLE)
  {
    qreal distanceJusquaArret = m_Vehicule->distanceJusquaVitesse(0.0);
    if (m_DistanceJusquaObjectif < (15.0*METRE_PAR_UNIT))
    {
      m_ObjectifVitesse = 0.0;
      urgent = true;
    }
    else if (m_DistanceJusquaObjectif <= distanceJusquaArret)
    {
      //Ralentir
      m_ObjectifVitesse = 5.0;
    }
    else
    {
      m_ObjectifVitesse = m_VitesseParDefaut;
    }
  }
  else if (typeObjectif == VOIE)
  {
    qreal diffAngle = qAbs(Point::retablirEntre0et180(m_ObjectifDirection - m_Vehicule->direction().angle()));
    m_ObjectifVitesse = (diffAngle > 20.0) ? m_ObjectifVitesseVirage : m_VitesseParDefaut;
  }
  conduire(urgent);
  return ret;
}

void Conducteur::conduire(bool urgent)
{if (m_Vehicule)
  {
    float vitesse = m_Vehicule->vitesse(true);
    float valeurAcceleration = 0.0, valeurFreinage = 0.0;
    float diffVitesse = 0.0f;
    diffVitesse = m_ObjectifVitesse - vitesse;

    if (diffVitesse < -3.0f)
    {
      //TODO
      //Les valeurs de 3 et 100 sont aléatoires, il faudrait trouver un moyen
      //de calculer l'urgence du freinage
      valeurAcceleration = 0.0;
      valeurFreinage = qAbs(diffVitesse * (urgent ? 100 : 3) / 100.0f);
    }
    else if (diffVitesse > 3.0f)
    {
      //TODO
      //Les valeurs de 3 et 100 sont aléatoires, il faudrait trouver un moyen
      //de calculer l'urgence de l'accélération
      valeurAcceleration = qAbs(diffVitesse * (urgent ? 100 : 3) / 100.0f);
      valeurFreinage = 0.0;
    }
    else if (m_ObjectifVitesse==0.0)
    {
      valeurAcceleration = 0.0;
      valeurFreinage = 1.0;
    }

    float diffAngle = m_ObjectifDirection - m_Vehicule->direction().angle();
    float valeurVolant = 0.0f;
    diffAngle = Point::retablirEntre0et180(diffAngle);
    valeurVolant = 2 * (diffAngle) / 180.0;
    qreal diffVolant=0;
    diffVolant = valeurVolant - m_PositionVolantPrecedente;
    if(diffVolant > .2)
      diffVolant = .2;
    else if(diffVolant < -.2)
      diffVolant = -.2;
    valeurVolant = m_PositionVolantPrecedente + diffVolant;

    if(valeurVolant > 1)
      valeurVolant = 1;
    else if(valeurVolant < -1)
      valeurVolant = -1;
    m_PositionVolantPrecedente = valeurVolant;

    m_Vehicule->accelerer(valeurAcceleration);
    m_Vehicule->freiner(valeurFreinage);
    m_Vehicule->tournervolant(valeurVolant);
  }
}

bool Conducteur::prevoirCollisions(Point &collision)
{
  Simulation *simu = Simulation::instance();
  Point pointCollision;
  bool collisionImminente = false;
  qreal plusCourteDistance=10000.0f;

  Point avantVehicule = m_Vehicule->emplacement()+(m_Vehicule->direction()*m_Vehicule->empattement());
  Vecteur v1(m_Vehicule->emplacement(), m_Vehicule->direction());
  Vecteur v2(avantVehicule, m_CoordonneesActuelles-avantVehicule);
  m_Conducteur = NULL;

  foreach (Conducteur *conducteur, simu->m_Conducteurs)
  {
    if (conducteur && conducteur != this)
    {
      Vehicule *v = conducteur->m_Vehicule;
      InfoIntersection info = PAS_INTERSECTION;

      QRect rect(0,0,20,20);
      rect.moveCenter(v->emplacement().toPoint());
      Point pts[2];

      InterVecteurRectangle(v2, rect, pts, info);
      if (info == INTERSECTION)
      {
        qreal distanceACollision = (avantVehicule-pts[0]).norme();
        if (distanceACollision <= 150.0)
        {
          if (distanceACollision < plusCourteDistance)
          {
            if (conducteur->m_Conducteur != this)
            {
              m_Conducteur = conducteur;
              collision = pts[0];
              plusCourteDistance = distanceACollision;
              collisionImminente = true;
            }
          }
        }
      }

      InterVecteurRectangle(v1, rect, pts, info);
      if (info == INTERSECTION)
      {
        qreal distanceACollision = (avantVehicule-pts[0]).norme();
        if (distanceACollision <= 150.0)
        {
          if (distanceACollision < plusCourteDistance)
          {
            if (conducteur->m_Conducteur != this)
            {
              m_Conducteur = conducteur;
              collision = pts[0];
              plusCourteDistance = distanceACollision;
              collisionImminente = true;
            }
          }
        }
      }

      Vecteur v3(v->emplacement(), v->direction());
      pointCollision = InterVecteurVecteur(v2, v3, info);
      if (info == INTERSECTION)
      {
        qreal maDistanceACollision = (avantVehicule-pointCollision).norme() * METRE_PAR_UNIT;
        qreal leurDistanceJusquaCollision = (v->emplacement()-pointCollision).norme()* METRE_PAR_UNIT;
        qreal maVitesse = m_Vehicule->vitesse(), leurVitesse = v->vitesse();
        qreal monTpsJusquaCollision=0.0, leurTpsJusquaCollision=0.0;
        qreal plusCourtTemps = 90000.0;
        monTpsJusquaCollision = (maVitesse > 0.0) ? maDistanceACollision/maVitesse : 90000.0;
        leurTpsJusquaCollision = (leurVitesse > 0.0) ? leurDistanceJusquaCollision/leurVitesse : 10000.0;
        qreal diffTemps = qAbs(monTpsJusquaCollision-leurTpsJusquaCollision);

        if (monTpsJusquaCollision <= 2 && diffTemps <= 2)
        {
          if (maDistanceACollision < plusCourteDistance)
          {
            if(diffTemps < plusCourtTemps)
            {
              if (conducteur->m_Conducteur != this && leurDistanceJusquaCollision < maDistanceACollision)
              {
                m_Conducteur = conducteur;
                collision = pointCollision;
                plusCourteDistance = maDistanceACollision;
                collisionImminente = true;
                plusCourtTemps = diffTemps;
              }
            }
          }
        }
      }
    }
  }
  return collisionImminente;
}

bool Conducteur::verifierVoie(Point &voieObjectif)
{
  voieObjectif = m_VoieActuelle.m_Segment.pointLePlusProche(m_Vehicule->emplacement());
  qreal dist = (voieObjectif-m_Vehicule->emplacement()).norme();
  if (dist >= LARGEUR_VOIE/2)
  {
    Point v = (m_CoordonneesActuelles-voieObjectif);
    v.normaliser();
    voieObjectif = voieObjectif + (v * 5.0);
    return true;
  }
  return false;
}

bool Conducteur::verifierFeux(Point &pointFeu)
{
  if (!m_RouteActuelle || m_Chemin.size()<2)
    return false;

  Simulation *simu = Simulation::instance();
  Plan *plan = simu->m_Plan;

  Signalisation *feux = simu->m_Signalisations.value(m_Chemin.at(0).intersection);
  if (feux)
  {
    Signalisation::COULEUR_FEU c = feux->etatActuel()->couleurFeu(
        m_RouteActuelle, m_IdVoieActuelle,
        plan->getRoute(m_Chemin.at(0).intersection, m_Chemin.at(1).intersection), m_IdVoieActuelle);
    if (c==Signalisation::ORANGE || c==Signalisation::ROUGE)
    {
      Point v = m_VoieActuelle.m_Segment.pointLePlusProche(m_Vehicule->emplacement())-m_CoordonneesActuelles;
      v.normaliser();
      pointFeu = m_CoordonneesActuelles;
      return true;
    }
  }
  return false;
}

void Conducteur::modifierCoordonnees()
{
  Simulation *simu = Simulation::instance();
  Plan *plan = simu->m_Plan;

  const Plan::Intersection *inter = m_Chemin.at(0).intersection;

  if (!inter)
  {
    m_CoordonneesActuelles = m_Chemin.at(0).emplacement;
    m_CoordonneesModifiees = true;
    m_DerniereIntersection = NULL;
    return;
  }

  if (!m_DerniereIntersection)
    m_RouteActuelle = plan->getRoute(m_Vehicule->emplacement());
  else
    m_RouteActuelle = plan->getRoute(m_DerniereIntersection, inter);

  if (!m_RouteActuelle)
    return;

  Plan::Route::Voie::Direction dir = m_RouteActuelle->getDirection(inter);
  m_IdVoieActuelle = 0;

  bool resultatOK = false;
  m_VoieActuelle = m_RouteActuelle->voie(dir, m_IdVoieActuelle, resultatOK);
  if (!resultatOK)
    return;

  if (dir == Plan::Route::Voie::PREM_VERS_DEUX)
    m_CoordonneesActuelles = m_VoieActuelle.m_Segment.depart();
  else
    m_CoordonneesActuelles = m_VoieActuelle.m_Segment.fin();

  Point v = m_VoieActuelle.m_Segment.pointLePlusProche(m_Vehicule->emplacement())-m_CoordonneesActuelles;
  v.normaliser();
  m_CoordonneesActuelles = m_CoordonneesActuelles + (v*5.0f);
  m_CoordonneesModifiees = true;
}

void Conducteur::avancer()
{
  m_DestinationAtteinte = m_Chemin.isEmpty();
  if (!m_DestinationAtteinte)
  {
    Point pointCollision;
    Point pointFeu;
    Point pointVoie;
    bool collisionImminente = false;
    bool pasDansLaVoie = false;
    bool signalisation = false;
    qreal distanceJusquaCollision = 999.0f;
    qreal distanceJusquaVoie = 999.0f;

    if (!m_CoordonneesModifiees)
      modifierCoordonnees();

    qreal distanceJusquaPoint = (m_CoordonneesActuelles - m_Vehicule->emplacement()).norme() * METRE_PAR_UNIT;
    if (distanceJusquaPoint <= DISTANCE_FEU && !m_ArretAuFeu)
    {
      m_DerniereIntersection = m_Chemin.at(0).intersection;
      m_Chemin.pop_front();
      m_CoordonneesModifiees = false;
      m_VitesseViragePrecedente = 0.0;
      m_VirageBientot = false;
      return;
    }

    if (prevoirCollisions(pointCollision))
    {
      collisionImminente = true;
      Point versVehicule = m_Vehicule->emplacement() - pointCollision;
      distanceJusquaCollision = versVehicule.norme();
      versVehicule.normaliser();
      if (distanceJusquaCollision >= 10.0f)
        pointCollision =  pointCollision + (versVehicule * 10.0f);
      else
        pointCollision = m_Vehicule->emplacement();
      distanceJusquaCollision = (m_Vehicule->emplacement() - pointCollision).norme();
    }

    if (m_Chemin.at(0).intersection && verifierVoie(pointVoie))
    {
      pasDansLaVoie = true;
      distanceJusquaVoie = (m_Vehicule->emplacement() - pointVoie).norme();
    }

    if (verifierFeux(pointFeu))
    {
      signalisation= true;
      m_ArretAuFeu = true;
    }
    else
      m_ArretAuFeu = false;

    if (collisionImminente && distanceJusquaCollision < distanceJusquaVoie && distanceJusquaCollision <= distanceJusquaPoint+10.0f)
      allerVers(pointCollision, OBSTACLE);
    else if (pasDansLaVoie && distanceJusquaVoie < distanceJusquaCollision)
      allerVers(pointVoie, VOIE);
    else if (signalisation)
      allerVers(pointFeu, OBSTACLE);
    else
      allerVers(m_CoordonneesActuelles, COORDONNEES);
  }
  else
  {
    m_ObjectifVitesse = 0.0;
    conduire(false);
  }
}
