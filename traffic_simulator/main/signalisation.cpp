#include "signalisation.h"
#include "simulation.h"

Signalisation::Connexion::Connexion(
  const Plan::Route *depart, const unsigned int voieDepart,
  const Plan::Route *fin, const unsigned int voieFin)
{
  this->m_Depart = depart;
  this->m_Fin = fin;
  this->m_VoieDepart = voieDepart;
  this->m_VoieFin= voieFin;
}

Signalisation::Etat::Etat(const QString &nom)
{
  m_Nom = nom;
  m_Connexions.clear();
  m_DureeVert = 0.0;
  m_DureeOrange = 0.0;
  m_DureeRouge = 0.0;
}

Signalisation::Etat::~Etat()
{
    m_Connexions.clear();
}

QString Signalisation::Etat::nom() const
{
  return m_Nom;
}

Signalisation::ListeConnexions Signalisation::Etat::getConnexions()
{
  return m_Connexions;
}

void Signalisation::Etat::setDureeVert(const qreal duree)
{
  m_DureeVert = duree;
}

qreal Signalisation::Etat::dureeVert() const
{
  return m_DureeVert;
}

void Signalisation::Etat::setDureeOrange(const qreal duree)
{
  m_DureeOrange = duree;
}

qreal Signalisation::Etat::dureeOrange() const
{
  return m_DureeOrange;
}

void Signalisation::Etat::setDureeRouge(const qreal duree)
{
  m_DureeRouge = duree;
}

qreal Signalisation::Etat::dureeRouge() const
{
  return m_DureeRouge;
}

void Signalisation::Etat::setCouleurFeu(const Signalisation::COULEUR_FEU couleur)
{
  m_CouleurActuelle = couleur;
}

Signalisation::COULEUR_FEU Signalisation::Etat::couleurFeu() const
{
  return m_CouleurActuelle;
}

Signalisation::COULEUR_FEU Signalisation::Etat::couleurFeu(
    const Plan::Route *depart, const unsigned int voieDepart,
    const Plan::Route *fin, const unsigned int voieFin) const
{
  for (int i=0; i<m_Connexions.size(); i++)
  {
    const Signalisation::Connexion *c = m_Connexions.at(i);
    if (c && c->m_Depart == depart && c->m_VoieDepart == voieDepart && c->m_Fin == fin && c->m_VoieFin == voieFin)
    {
      return m_CouleurActuelle;
    }
  }
  return ROUGE;
}

void Signalisation::Etat::ajouterConnexion(Connexion *connexion)
{
  m_Connexions.push_back(connexion);
}

bool Signalisation::Etat::operator==(const Etat &etat) const
{
  if (nom() == etat.nom())
    return true;
  else
    return false;
}

Signalisation::Signalisation()
{
  m_Intersection = NULL;
  m_Etats.clear();
  m_IdEtatActuel = 0;
  m_TpsDepuisDernierChangtEtat = 0.0;
}

Signalisation::~Signalisation()
{
  m_Etats.clear();
}

void Signalisation::setIntersection(const Plan::Intersection *intersection)
{
  m_Intersection = intersection;
}

const Plan::Intersection* Signalisation::intersection() const
{
  return m_Intersection;
}

void Signalisation::ajouterEtat(Signalisation::Etat *etat)
{
  if (etat)
  {
    foreach (Signalisation::Etat *e, m_Etats)
    {
      if (e && e->nom() == etat->nom())
      {
        return;
      }
    }
    m_Etats.push_back(etat);
  }
}

Signalisation::Etat* Signalisation::etatActuel() const
{
  return m_Etats.at(m_IdEtatActuel);
}

void Signalisation::avancer()
{
    m_TpsDepuisDernierChangtEtat += Simulation::m_PasSimulation;
    Etat *actuel = etatActuel();

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
