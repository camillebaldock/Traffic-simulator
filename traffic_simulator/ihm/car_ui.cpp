#include "car_ui.h"
#include "utils.h"
#include <QPen>

/**
  * Constructeur
  */
CarUI::CarUI(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap)
{
  setZValue(Utils::COUCHE_VEHICULE);
  m_Scale = 0.1f;
  scale(m_Scale, m_Scale);
  translate(-pixmap.width()/2.0, -pixmap.height()/2.0);
  setTransformOriginPoint(pixmap.width()/2.0, pixmap.height()/2.0);
  // Vecteur velocite (jaune)
  m_VelocityVector = new QGraphicsLineItem(this);
  m_VelocityVector->setPen(QPen(Qt::yellow, 2.0f/m_Scale));
  m_VelocityVector->setZValue(Utils::COUCHE_ANNOTATIONS+1);
  // Vecteur force frottement (bleu)
  m_FrictionVector = new QGraphicsLineItem(this);
  m_FrictionVector->setPen(QPen(Qt::blue, 2.0f/m_Scale));
  m_FrictionVector->setZValue(Utils::COUCHE_ANNOTATIONS+2);
  // Vecteur force moteur (vert)
  m_MotorForceVector = new QGraphicsLineItem(this);
  m_MotorForceVector->setPen(QPen(Qt::green, 2.0f/m_Scale));
  m_MotorForceVector->setZValue(Utils::COUCHE_ANNOTATIONS+3);
}

/**
  * Affiche le vecteur vélocité pour le véhicule
  * @param afficher Afficher ou non
  */
void CarUI::displayVelocity(const bool afficher)
{
  if(m_VelocityVector)
    m_VelocityVector->setVisible(afficher);
}

/**
  * Affiche le vecteur frottements pour le véhicule
  * @param afficher Afficher ou non
  */
void CarUI::displayFriction(const bool afficher)
{
  if(m_FrictionVector)
    m_FrictionVector->setVisible(afficher);
}

/**
  * Affiche le vecteur force moteur pour le véhicule
  * @param afficher Afficher ou non
  */
void CarUI::displayMotorForce(const bool afficher)
{
  if(m_MotorForceVector)
    m_MotorForceVector->setVisible(afficher);
}

/**
  * Ajouter toutes les informations contenues dans cet object
  * Vehicule IHM à l'ImageVehicule image
  * @param image ImageVehicule à compléter
  */
void CarUI::setCarImage(ImageVehicule* image)
{
  if (!image)
    return;

  setPos(image->emplacement());
  setRotation(image->direction());

  if(m_VelocityVector)
    m_VelocityVector->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene(image->emplacement()+image->velocite())));
  Point moteur, frottements;
  image->forces(moteur, frottements);
  moteur = moteur * 0.01;
  frottements = frottements * 0.01;
  if(m_MotorForceVector)
  {
    m_MotorForceVector->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene((image->emplacement()+moteur))));
  }
  if(m_FrictionVector)
  {
    m_FrictionVector->setLine(
        QLineF(mapFromScene(image->emplacement()), mapFromScene(image->emplacement()+frottements)));
  }
}
