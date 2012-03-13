#ifndef ROUTEUI_H
#define ROUTEUI_H
#include <QGraphicsPathItem>
#include "point.h"

class RoadUI : public QGraphicsPathItem
{
    public:
      RoadUI(QGraphicsItem* parent = 0);
      void setFirst(const Utils::Point& premier);
      void setSecond(const Utils::Point& deuxieme);
      void setLanesFirstToSecond(unsigned int nb);
      void setLanesSecondToFirst(unsigned int nb);
      void setRoadWidth(unsigned int largeur);

    protected:
      void drawRoad();
      Utils::Point m_Premier, m_Deuxieme;
      unsigned int m_LanesFirstToSecond, m_LanesSecondToFirst;
      int m_RoadWidth;
};

#endif
