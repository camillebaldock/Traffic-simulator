#include "vehiculeihm.h"
#include "utils.h"
#include <QPen>

/**
  * Constructeur
  */
VehiculeIHM::VehiculeIHM(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap)
{
  setZValue(Utils::COUCHE_VEHICULE);
  m_Echelle = 0.1f;
  scale(m_Echelle, m_Echelle);
  translate(-pixmap.width()/2.0, -pixmap.height()/2.0);
  setTransformOriginPoint(pixmap.width()/2.0, pixmap.height()/2.0);
  // Vecteur velocite (jaune)
  m_VecteurVelocite = new QGraphicsLineItem(this);
  m_VecteurVelocite->setPen(QPen(Qt::yellow, 2.0f/m_Echelle));
  m_VecteurVelocite->setZValue(Utils::COUCHE_ANNOTATIONS+1);
  // Vecteur force frottement (bleu)
  m_VecteurForceFrottements = new QGraphicsLineItem(this);
  m_VecteurForceFrottements->setPen(QPen(Qt::blue, 2.0f/m_Echelle));
  m_VecteurForceFrottements->setZValue(Utils::COUCHE_ANNOTATIONS+2);
  // Vecteur force moteur (vert)
  m_VecteurForceMoteur = new QGraphicsLineItem(this);
  m_VecteurForceMoteur->setPen(QPen(Qt::green, 2.0f/m_Echelle));
  m_VecteurForceMoteur->setZValue(Utils::COUCHE_ANNOTATIONS+3);
}

/**
  * Affiche le vecteur vélocité pour le véhicule
  * @param afficher Afficher ou non
  */
void VehiculeIHM::afficherVelocite(const bool afficher)
{
  if(m_VecteurVelocite)
    m_VecteurVelocite->setVisible(afficher);
}

/**
  * Affiche le vecteur frottements pour le véhicule
  * @param afficher Afficher ou non
  */
void VehiculeIHM::afficherFrottements(const bool afficher)
{
  if(m_VecteurForceFrottements)
    m_VecteurForceFrottements->setVisible(afficher);
}

/**
  * Affiche le vecteur force moteur pour le véhicule
  * @param afficher Afficher ou non
  */
void VehiculeIHM::afficherForceMoteur(const bool afficher)
{
  if(m_VecteurForceMoteur)
    m_VecteurForceMoteur->setVisible(afficher);
}

/**
  * Ajouter toutes les informations contenues dans cet object
  * Vehicule IHM à l'ImageVehicule image
  * @param image ImageVehicule à compléter
  */
void VehiculeIHM::setImageVehicule(ImageVehicule* image)
{
  if (!image)
    return;

  setPos(image->emplacement());
  setRotation(image->direction());

  if(m_VecteurVelocite)
    m_VecteurVelocite->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene(image->emplacement()+image->velocite())));
  Point moteur, frottements;
  image->forces(moteur, frottements);
  moteur = moteur * 0.01;
  frottements = frottements * 0.01;
  if(m_VecteurForceMoteur)
  {
    m_VecteurForceMoteur->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene((image->emplacement()+moteur))));
  }
  if(m_VecteurForceFrottements)
  {
    m_VecteurForceFrottements->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene(image->emplacement()+frottements)));
  }
}
