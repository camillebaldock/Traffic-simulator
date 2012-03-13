#include "trafficlights.h"
#include "simulation.h"

TrafficLights::Connexion::Connexion(
  const Map::Road *depart, const unsigned int voieDepart,
  const Map::Road *fin, const unsigned int voieFin)
{
  this->m_Depart = depart;
  this->m_Fin = fin;
  this->m_VoieDepart = voieDepart;
  this->m_VoieFin= voieFin;
}

TrafficLights::State::State(const QString &nom)
{
  m_Nom = nom;
  m_Connexions.clear();
  m_DureeVert = 0.0;
  m_DureeOrange = 0.0;
  m_DureeRouge = 0.0;
}

TrafficLights::State::~State()
{
    m_Connexions.clear();
}

QString TrafficLights::State::nom() const
{
  return m_Nom;
}

TrafficLights::ListeConnexions TrafficLights::State::getConnexions()
{
  return m_Connexions;
}

void TrafficLights::State::setDureeVert(const qreal duree)
{
  m_DureeVert = duree;
}

qreal TrafficLights::State::dureeVert() const
{
  return m_DureeVert;
}

void TrafficLights::State::setDureeOrange(const qreal duree)
{
  m_DureeOrange = duree;
}

qreal TrafficLights::State::dureeOrange() const
{
  return m_DureeOrange;
}

void TrafficLights::State::setDureeRouge(const qreal duree)
{
  m_DureeRouge = duree;
}

qreal TrafficLights::State::dureeRouge() const
{
  return m_DureeRouge;
}

void TrafficLights::State::setCouleurFeu(const TrafficLights::COULEUR_FEU couleur)
{
  m_CouleurActuelle = couleur;
}

TrafficLights::COULEUR_FEU TrafficLights::State::couleurFeu() const
{
  return m_CouleurActuelle;
}

TrafficLights::COULEUR_FEU TrafficLights::State::couleurFeu(
    const Map::Road *depart, const unsigned int voieDepart,
    const Map::Road *fin, const unsigned int voieFin) const
{
  for (int i=0; i<m_Connexions.size(); i++)
  {
    const TrafficLights::Connexion *c = m_Connexions.at(i);
    if (c && c->m_Depart == depart && c->m_VoieDepart == voieDepart && c->m_Fin == fin && c->m_VoieFin == voieFin)
    {
      return m_CouleurActuelle;
    }
  }
  return ROUGE;
}

void TrafficLights::State::ajouterConnexion(Connexion *connexion)
{
  m_Connexions.push_back(connexion);
}

bool TrafficLights::State::operator==(const State &etat) const
{
  if (nom() == etat.nom())
    return true;
  else
    return false;
}

TrafficLights::TrafficLights()
{
  m_Intersection = NULL;
  m_Etats.clear();
  m_IdEtatActuel = 0;
  m_TpsDepuisDernierChangtEtat = 0.0;
}

TrafficLights::~TrafficLights()
{
  m_Etats.clear();
}

void TrafficLights::setIntersection(const Map::Intersection *intersection)
{
  m_Intersection = intersection;
}

const Map::Intersection* TrafficLights::intersection() const
{
  return m_Intersection;
}

void TrafficLights::ajouterEtat(TrafficLights::State *etat)
{
  if (etat)
  {
    foreach (TrafficLights::State *e, m_Etats)
    {
      if (e && e->nom() == etat->nom())
      {
        return;
      }
    }
    m_Etats.push_back(etat);
  }
}

TrafficLights::State* TrafficLights::etatActuel() const
{
  return m_Etats.at(m_IdEtatActuel);
}

void TrafficLights::avancer()
{
    m_TpsDepuisDernierChangtEtat += Simulation::m_PasSimulation;
    State *actuel = etatActuel();

    if (m_TpsDepuisDernierChangtEtat > actuel->dureeVert())
    {
      if (m_TpsDepuisDernierChangtEtat > (actuel->dureeVert() + actuel->dureeOrange()))
      {
        actuel->setCouleurFeu(ROUGE);
        if (m_TpsDepuisDernierChangtEtat > (actuel->dureeVert() + actuel->dureeOrange()+ actuel->dureeRouge()))
        {
          m_TpsDepuisDernierChangtEtat = 0.0;
          m_IdEtatActuel++;
          if (m_IdEtatActuel >= m_Etats.size())
            m_IdEtatActuel = 0;
        }
      }
      else
      {
        actuel->setCouleurFeu(ORANGE);
      }
    }
    else
    {
      actuel->setCouleurFeu(VERT);
    }
}
