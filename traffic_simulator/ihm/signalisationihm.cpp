#include "signalisationihm.h"
#include <QFont>
#include <QPen>
#include "utils.h"
#include "imagesignalisation.h"
#include "simulation.h"

/**
  * Constructeur
  */
SignalisationIHM::SignalisationIHM()
{}

/**
  * Initialise m_Intersection pour cet objet SignalisationIHM et affiche un feu rouge
  * @param intersection
  */
void SignalisationIHM::setIntersection(const Plan::Intersection *intersection)
{
  if (m_Intersection != intersection)
  {
    m_ImagesFeu.clear();

    Simulation *s= Simulation::instance();
    Plan::ListeRoutes routes  = s->m_Plan->getRoutes(intersection);

    foreach(Plan::Route *route, routes)
    {
      Plan::Route::Voie::Direction dir = route->getDirection(intersection);
      unsigned int nbVoies = route->nbVoies(dir);

      for (unsigned int i=0; i<nbVoies; i++)
      {
        bool resultatOK = true;
        Plan::Route::Voie voie = route->voie(dir, i, resultatOK);
        if (resultatOK)
        {
          QGraphicsPixmapItem *feuRouge(new QGraphicsPixmapItem(QPixmap(":/feu_rouge.png"),0,this->scene()));
          if (voie.m_Direction == Plan::Route::Voie::PREM_VERS_DEUX)
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
void SignalisationIHM::setImage(ImageSignalisation* image)
  {
    setIntersection(image->intersection());
    Signalisation::ListeConnexions connexions = image->etat().getConnexions();
  for (int i=0; i<connexions.size(); i++)
  {
    Signalisation::Connexion *connexion = connexions.at(i);
    if (connexion->m_Depart)
    {
      QString cle = connexion->m_Depart->nom() + QString::number(connexion->m_VoieDepart);
      QMap<QString, QGraphicsPixmapItem*>::iterator compteur = m_ImagesFeu.find(cle);

      if (compteur != m_ImagesFeu.end())
      {
        QGraphicsPixmapItem *pixmap = compteur.value();

        if (pixmap)
        {
          Signalisation::COULEUR_FEU couleur = image->etat().couleurFeu();
          switch (couleur)
          {
              case Signalisation::VERT: pixmap->setPixmap(QPixmap(":/feu_vert.png"));
              break;
              case Signalisation::ORANGE: pixmap->setPixmap(QPixmap(":/feu_orange.png"));
              break;
              case Signalisation::ROUGE: pixmap->setPixmap(QPixmap(":/feu_rouge.png"));
              break;
          }
        }
      }
    }
  }
}
