#include "routeihm.h"
#include <QPen>
#include "point.h"
#include "segment.h"
#include "utils.h"

/**
  * Constructeur, couleur noire pour le fond de la route
  */
RouteIHM::RouteIHM(QGraphicsItem *parent)
  : QGraphicsPathItem(parent),
    m_VoiesPremVersDeux(0),
    m_VoiesDeuxVersPrem(0),
    m_LargeurRoute(0)
{
  setZValue(Utils::COUCHE_ROUTE);
  setPen(QPen(Qt::black));
  setBrush(Qt::black);
}

/**
  * Dessin des différents éléments de la route (bordures, lignes de sérpation entre les voies
  */
void RouteIHM::dessinerRoute()
{
  //Créer les 3 segments qui vont délimiter la route (milieu et les deux bords)
  Utils::Segment segmentMilieu(m_Premier, m_Deuxieme),
                 decalageNegatif(segmentMilieu.versDecalage(-m_LargeurRoute/2)),
                 decalagePositif(segmentMilieu.versDecalage(m_LargeurRoute/2));

  //Définition du QPainterPath qui va contenir tous les dessins suivants
  QPainterPath path;
  path.moveTo(decalageNegatif.depart().x(), decalageNegatif.depart().y());
  path.lineTo(decalageNegatif.fin().x(), decalageNegatif.fin().y());
  path.lineTo(decalagePositif.fin().x(), decalagePositif.fin().y());
  path.lineTo(decalagePositif.depart().x(), decalagePositif.depart().y());
  path.closeSubpath();
  setPath(path);

  qDeleteAll(childItems());

  //Tracer des lignes blanches pour les deux bords de la route
  QPen ligneBlanche(Qt::white);
  QGraphicsLineItem* negatif(new QGraphicsLineItem(this));
  negatif->setZValue(Utils::COUCHE_VOIE);
  negatif->setLine(decalageNegatif.toQLineF());
  negatif->setPen(ligneBlanche);  
  QGraphicsLineItem* positif(new QGraphicsLineItem(this));
  positif->setZValue(Utils::COUCHE_VOIE);
  positif->setLine(decalagePositif.toQLineF());
  positif->setPen(ligneBlanche);

  //Tracer les délimiteurs de voie
  unsigned int nbTotalVoies(m_VoiesPremVersDeux+m_VoiesDeuxVersPrem);
  if (nbTotalVoies)
  {
    unsigned int largeurVoie(m_LargeurRoute/nbTotalVoies);
    for (unsigned int i(  1); i<nbTotalVoies; ++i)
    {
      QGraphicsLineItem* division(new QGraphicsLineItem(this));
      division->setZValue(Utils::COUCHE_VOIE);
      Utils::Segment ligne(decalageNegatif.versDecalage(i*largeurVoie));
      division->setLine(ligne.toQLineF());
      if (i == m_VoiesPremVersDeux)
      {
        //Tracer la ligne jaune du milieu de la route
        QPen ligneJaune(Qt::yellow);
        division->setPen(ligneJaune);
      }
      else
      {
        //Tracer les lignes blanches pointillées qui séparent les voies
        QPen pointilleBlanc(Qt::DashLine);
        pointilleBlanc.setBrush(Qt::white);
        division->setPen(pointilleBlanc);
      }
    }
  }
}

/**
  * Modification du premier point de la route, puis la route est redessinée
  * @param premier Premier point de la route
  */
void RouteIHM::setPremier(const Utils::Point &premier)
{
  m_Premier = premier;
  dessinerRoute();
}

/**
  * Modification du deuxième point de la route, puis la route est redessinée
  * @param deuxieme Deuxieme point de la route
  */
void RouteIHM::setDeuxieme(const Utils::Point &deuxieme)
{
  m_Deuxieme = deuxieme;
  dessinerRoute();
}

/**
  * Modification du nombre de voies du premier point vers le deuxième, puis la route est redessinée
  * @param nb Nombre de voies du premier point vers le deuxième
  */
void RouteIHM::setVoiesPremVersDeux(unsigned int nb)
{
  m_VoiesPremVersDeux = nb;
  dessinerRoute();
}

/**
  * Modification du nombre de voies du deuxième point vers le premier, puis la route est redessinée
  * @param nb Nombre de voies du deuxième point vers le premier
  */
void RouteIHM::setVoiesDeuxVersPrem(unsigned int nb)
{
  m_VoiesDeuxVersPrem = nb;
  dessinerRoute();
}

/**
  * Modification de la largeur de la route, puis la route est redessinée
  * @param largeur Largeur de la route
  */
void RouteIHM::setLargeurRoute(unsigned int largeur)
{
  m_LargeurRoute = largeur;
  dessinerRoute();
}
