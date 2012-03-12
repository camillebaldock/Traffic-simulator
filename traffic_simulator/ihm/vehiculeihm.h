#ifndef VEHICULEIHM_H
#define VEHICULEIHM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include "point.h"
#include "imagevehicule.h"

class VehiculeIHM : public QGraphicsPixmapItem
{
public:
  VehiculeIHM(const QPixmap &pixmap);
  void setImageVehicule(ImageVehicule* iv);
  void afficherVelocite(const bool afficher);
  void afficherForceMoteur(const bool afficher);
  void afficherFrottements(const bool afficher);

private:
  qreal m_Echelle;
  QGraphicsLineItem* m_VecteurVelocite;
  QGraphicsLineItem* m_VecteurForceMoteur;
  QGraphicsLineItem* m_VecteurForceFrottements;
  QGraphicsPolygonItem* m_Voie;
};

#endif // VEHICULEIHM_H
