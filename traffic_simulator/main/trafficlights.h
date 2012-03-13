#ifndef SIGNALISATION_H
#define SIGNALISATION_H

#include <QList>
#include "map.h"

class TrafficLights
{
  public:

    enum COULEUR_FEU {
      ROUGE,
      ORANGE,
      VERT
    };

    class Connexion
    {
    public:
      Connexion(const Map::Road *m_Depart, const unsigned int m_VoieDepart,
                 const Map::Road *m_Fin, const unsigned int m_VoieFin);
      const Map::Road *m_Depart;
      unsigned int m_VoieDepart;
      const Map::Road *m_Fin;
      unsigned int m_VoieFin;
    };

    typedef QList<Connexion*> ListeConnexions;

    class State
    {
    public:
      State(const QString &nom);
      ~State();
      QString nom() const;
      ListeConnexions getConnexions();
      void ajouterConnexion(Connexion *connexion);
      void setDureeVert(const qreal duree);
      qreal dureeVert() const;
      void setDureeOrange(const qreal duree);
      qreal dureeOrange() const;
      void setDureeRouge(const qreal duree);
      qreal dureeRouge() const;
      COULEUR_FEU couleurFeu(const Map::Road *depart, const unsigned int voieDepart,
                             const Map::Road *fin, const unsigned int voieFin) const;
      COULEUR_FEU couleurFeu() const;
      void setCouleurFeu(const COULEUR_FEU couleur);
      bool operator==(const State &etat) const;

    protected:
      QString m_Nom;
      ListeConnexions m_Connexions;
      qreal m_DureeVert;
      qreal m_DureeOrange;
      qreal m_DureeRouge;
      COULEUR_FEU m_CouleurActuelle;
    };

    TrafficLights();
    ~TrafficLights();
    void setIntersection(const Map::Intersection *intersection);
    const Map::Intersection* intersection() const;
    void ajouterEtat(State *etat);
    State* etatActuel() const;
    void avancer();

  protected:
    QList<State*> m_Etats;
    const Map::Intersection *m_Intersection;
    int m_IdEtatActuel;
    qreal m_TpsDepuisDernierChangtEtat;
};

#endif // SIGNALISATION_H
