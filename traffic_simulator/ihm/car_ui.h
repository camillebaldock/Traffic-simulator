#ifndef CARUI_H
#define CARUI_H

#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include "point.h"
#include "imagevehicule.h"

class CarUI : public QGraphicsPixmapItem
{
public:
  CarUI(const QPixmap &pixmap);
  void setCarImage(ImageVehicule* iv);
  void displayVelocity(const bool afficher);
  void displayMotorForce(const bool afficher);
  void displayFriction(const bool afficher);

private:
  qreal m_Scale;
  QGraphicsLineItem* m_VelocityVector;
  QGraphicsLineItem* m_MotorForceVector;
  QGraphicsLineItem* m_FrictionVector;
  QGraphicsPolygonItem* m_Lane;
};

#endif // CARUI_H
