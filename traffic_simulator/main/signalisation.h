#ifndef SIGNALISATION_H
#define SIGNALISATION_H

#include <QList>
#include "plan.h"

class Signalisation
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
      Connexion(const Plan::Route *m_Depart, const unsigned int m_VoieDepart,
                 const Plan::Route *m_Fin, const unsigned int m_VoieFin);
      const Plan::Route *m_Depart;
      unsigned int m_VoieDepart;
      const Plan::Route *m_Fin;
      unsigned int m_VoieFin;
    };

    typedef QList<Connexion*> ListeConnexions;

    class Etat
    {
    public:
      Etat(const QString &nom);
      ~Etat();
      QString nom() const;
      ListeConnexions getConnexions();
      void ajouterConnexion(Connexion *connexion);
      void setDureeVert(const qreal duree);
      qreal dureeVert() const;
      void setDureeOrange(const qreal duree);
      qreal dureeOrange() const;
      void setDureeRouge(const qreal duree);
      qreal dureeRouge() const;
      COULEUR_FEU couleurFeu(const Plan::Route *depart, const unsigned int voieDepart,
                             const Plan::Route *fin, const unsigned int voieFin) const;
      COULEUR_FEU couleurFeu() const;
      void setCouleurFeu(const COULEUR_FEU couleur);
      bool operator==(const Etat &etat) const;

    protected:
      QString m_Nom;
      ListeConnexions m_Connexions;
      qreal m_DureeVert;
      qreal m_DureeOrange;
      qreal m_DureeRouge;
      COULEUR_FEU m_CouleurActuelle;
    };

    Signalisation();
    ~Signalisation();
    void setIntersection(const Plan::Intersection *intersection);
    const Plan::Intersection* intersection() const;
    void ajouterEtat(Etat *etat);
    Etat* etatActuel() const;
    void avancer();

  protected:
    QList<Etat*> m_Etats;
    const Plan::Intersection *m_Intersection;
    int m_IdEtatActuel;
    qreal m_TpsDepuisDernierChangtEtat;
};

#endif // SIGNALISATION_H
