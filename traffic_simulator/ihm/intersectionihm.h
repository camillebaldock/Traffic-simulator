#ifndef INTERSECTIONIHM_H
#define INTERSECTIONIHM_H
#include <QGraphicsPathItem>
#include "plan.h"
#include "utils.h"

class IntersectionIHM : public QGraphicsPathItem
{
public:
  IntersectionIHM(QGraphicsItem* parent = 0);
  void ajouterRoutes(const Plan::ListeRoutes& routes);
  void setNomIntersection(const QString& nom);
  void setCentreIntersection(const Utils::Point& centre);

private:
  void dessinerIntersection();
  QString m_Nom;
  Utils::Point m_Centre;
  QList<Utils::Segment> m_Segments;
  QList<Utils::Point> m_Points;
};

#endif
