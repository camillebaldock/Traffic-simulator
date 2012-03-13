#include "trafficlights_ui.h"
#include <QFont>
#include <QPen>
#include "utils.h"
#include "imagesignalisation.h"
#include "simulation.h"

/**
  * Constructeur
  */
TrafficLightsUI::TrafficLightsUI()
{}

/**
  * Initialise m_Intersection pour cet objet SignalisationIHM et affiche un feu rouge
  * @param intersection
  */
void TrafficLightsUI::setIntersection(const Map::Intersection *intersection)
{
  if (m_Intersection != intersection)
  {
    m_ImagesFeu.clear();

    Simulation *s= Simulation::instance();
    Map::ListeRoutes routes  = s->m_Plan->getRoutes(intersection);

    foreach(Map::Road *route, routes)
    {
      Map::Road::Voie::Direction dir = route->getDirection(intersection);
      unsigned int nbVoies = route->nbVoies(dir);

      for (unsigned int i=0; i<nbVoies; i++)
      {
        bool resultatOK = true;
        Map::Road::Voie voie = route->voie(dir, i, resultatOK);
        if (resultatOK)
        {
          QGraphicsPixmapItem *feuRouge(new QGraphicsPixmapItem(QPixmap(":/feu_rouge.png"),0,this->scene()));
          if (voie.m_Direction == Map::Road::Voie::PREM_VERS_DEUX)
            feuRouge->setPos(voie.m_Segment.depart());
          else
            feuRouge->setPos(voie.m_Segment.fin());
          feuRouge->setZValue(Utils::COUCHE_VOIE);
          feuRouge->scale(0.5, 0.5);
          feuRouge->translate(-feuRouge->pixmap().width()/2, -feuRouge->pixmap().height()/2);
          QString key = route->nom() + QString::number(i);
          m_ImagesFeu[key] = feuRouge;
        }
       }
    }
    m_Intersection = intersection;
  }
}

/**
  * Affiche un feu de couleur verte, orange ou rouge selon les paramètres de image
  * @param image Objet ImageSignalisation
  */
void TrafficLightsUI::setImage(ImageSignalisation* image)
  {
    setIntersection(image->intersection());
    TrafficLights::ListeConnexions connexions = image->etat().getConnexions();
  for (int i=0; i<connexions.size(); i++)
  {
    TrafficLights::Connexion *connexion = connexions.at(i);
    if (connexion->m_Depart)
    {
      QString cle = connexion->m_Depart->nom() + QString::number(connexion->m_VoieDepart);
      QMap<QString, QGraphicsPixmapItem*>::iterator compteur = m_ImagesFeu.find(cle);

      if (compteur != m_ImagesFeu.end())
      {
        QGraphicsPixmapItem *pixmap = compteur.value();

        if (pixmap)
        {
          TrafficLights::COULEUR_FEU couleur = image->etat().couleurFeu();
          switch (couleur)
          {
              case TrafficLights::VERT: pixmap->setPixmap(QPixmap(":/feu_vert.png"));
              break;
              case TrafficLights::ORANGE: pixmap->setPixmap(QPixmap(":/feu_orange.png"));
              break;
              case TrafficLights::ROUGE: pixmap->setPixmap(QPixmap(":/feu_rouge.png"));
              break;
          }
        }
      }
    }
  }
}
