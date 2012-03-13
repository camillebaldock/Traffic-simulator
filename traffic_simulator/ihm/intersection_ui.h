#ifndef INTERSECTIONUI_H
#define INTERSECTIONUI_H
#include <QGraphicsPathItem>
#include "map.h"
#include "utils.h"

class IntersectionUI : public QGraphicsPathItem
{
public:
  IntersectionUI(QGraphicsItem* parent = 0);
  void addRoads(const Map::ListeRoutes& roads);
  void setNameIntersection(const QString& nom);
  void setCentreIntersection(const Utils::Point& centre);

private:
  void drawIntersection();
  QString m_Name;
  Utils::Point m_Centre;
  QList<Utils::Segment> m_Segments;
  QList<Utils::Point> m_Points;
};

#endif
